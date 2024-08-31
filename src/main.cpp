#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "mMenu.h"
#include "pinouts.h"
#include "AiEsp32RotaryEncoder.h"

// constants
#define ROTARY_ENCODER_STEPS 2

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

void updateEncoder()
{
  if (rotaryEncoder.encoderChanged())
  {
    Serial.println(rotaryEncoder.encoderSteps);
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
  Serial.begin(9600);
  menu.initialize(mainMenu);
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(0, 1000, false); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder.setAcceleration(250);
}

void loop()
{
  updateEncoder(); 
  if (!Serial.available())
    return;
  char command = Serial.read();
  processMenuCommand(menu, command, UP, DOWN, ENTER, BACK);
}
