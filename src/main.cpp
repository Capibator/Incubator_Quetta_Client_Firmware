#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "mMenu.h"
// constants
#define DHTPIN 2      // fill pin TODO:
#define DHTTYPE DHT22 // DHT 22 (AM2302)


// INITIALIZETD
DHT dht(DHTPIN, DHTTYPE);


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

void setup()
{
  // put your setup code here, to run once:
  menu.initialize(mainMenu);
}

void loop()
{
  if (!Serial.available())
    return;
  char command = Serial.read();
  processMenuCommand(menu, command, UP, DOWN, ENTER, BACK);
}
