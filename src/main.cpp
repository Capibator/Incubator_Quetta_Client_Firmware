#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "mMenu.h"
#include "pinouts.h"
#include "AiEsp32RotaryEncoder.h"

// constants
#define ROTARY_ENCODER_STEPS 2
bool dir; 
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

struct encoder
{
  int clk;
  int data;
  int sw;
  unsigned long prevTimeEnc; // keeps track of encoder time.
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

void updateEncoder()
{
  static int prevVal = 0;  // Make prevVal static to retain its value between function calls
  int val;
  dir;

  if (rotaryEncoder.encoderChanged())
  {
    val = rotaryEncoder.readEncoder();

    // Check for changes in encoder value and determine direction
    if (val != prevVal)  // Only proceed if the value has changed
    {
      if(val == 100 || val == 0) return; 
      // Determine direction
      dir = (val > prevVal) ? true : false;  // dir is true if moving right

      // Print direction
      if (dir)
        Serial.println("left");
      else
        Serial.println("right");

      prevVal = val;  // Update prevVal with the new value
    }
  }

  if (rotaryEncoder.isEncoderButtonClicked())
  {
    Serial.println("button pressed");
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
  if (!Serial.available())
    return;
  char command = Serial.read();
}
