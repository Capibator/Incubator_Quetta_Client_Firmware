#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "mMenu.h"
#include "pinouts.h"
#include "AiEsp32RotaryEncoder.h"

// constants
#define ROTARY_ENCODER_STEPS 2
int dir;
#define IDLE 0
#define UP 1
#define DOWN 2
#define ENTER 3
#define BACK 4

#define longPressAfterMiliseconds  500  //how long čong press shoud be.

// INITIALIZETD
DHT dht(DHTPIN, DHTTYPE);
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);

// Structs
struct sensor
{
  float curTemp;
  float curHum;
  unsigned long curTime, prevTimeSens;
  const uint16_t updateTime = 2000;
};

// update the crucial sensor every 2 seconds.. well updates all sensors.
void UpdateSensor(sensor *sensor)
{
  if (sensor->curTime - sensor->prevTimeSens >= sensor->updateTime)
  {
    // update every 2 seconds.
    sensor->prevTimeSens = millis();
    sensor->curHum = dht.readHumidity();
    // Read temperature as Celsius (the default)
    sensor->curTemp = dht.readTemperature();
  }
}


void on_button_long_click() {
  Serial.print("button LONG press ");
  dir = BACK; 
}

void handle_rotary_button() {
  static unsigned long lastTimeButtonDown = 0;
  static bool wasButtonDown = false;

  bool isEncoderButtonDown = rotaryEncoder.isEncoderButtonDown();
  //isEncoderButtonDown = !isEncoderButtonDown; //uncomment this line if your button is reversed

  if (isEncoderButtonDown) {
    Serial.print("+");  //REMOVE THIS LINE IF YOU DONT WANT TO SEE
    if (!wasButtonDown) {
      //start measuring
      lastTimeButtonDown = millis();
    }
    //else we wait since button is still down
    wasButtonDown = true;
    return;
  }

  //button is up
  if (wasButtonDown) {
    Serial.println("");  //REMOVE THIS LINE IF YOU DONT WANT TO SEE
    //click happened, lets see if it was short click, long click or just too short
    if (millis() - lastTimeButtonDown >= longPressAfterMiliseconds) {
      on_button_long_click();
    }
  }
  wasButtonDown = false;
}

void updateEncoder()
{
  static int prevVal = 0; // Make prevVal static to retain its value between function calls
  int val;
  dir;


  if (rotaryEncoder.isEncoderButtonClicked())
  {
    
    dir = ENTER;
    Serial.println("button pressed");
  }


  if (rotaryEncoder.encoderChanged())
  {
    val = rotaryEncoder.readEncoder();

    // Check for changes in encoder value and determine direction
    if (val != prevVal) // Only proceed if the value has changed
    {
      if (val == 100 || val == 0)
        return;
      // Determine direction
      dir = (val > prevVal) ? UP : DOWN; //

      // Print direction
      if (dir == UP)
        Serial.println("UP");
      else
        Serial.println("DOWN");

      prevVal = val; // Update prevVal with the new value
    }
  }
}

void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder.readEncoder_ISR();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  menu.initialize(mainMenu);
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(0, 100, true); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)
}

void loop()
{
  updateEncoder();
  handle_rotary_button();
  processMenuCommand(menu, dir, UP, DOWN, ENTER, BACK);
  dir = IDLE; 
}
