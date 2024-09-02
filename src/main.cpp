#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "mMenu.h"
#include "pinouts.h"
#include "rotary.h"


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
  Serial.begin(115200);
  menu.initialize(mainMenu);
  initEncoder(); 

}

void loop()
{
  updateEncoder();
  handle_rotary_button();
  processMenuCommand(menu, dir, UP, DOWN, ENTER, BACK);
  dir = IDLE;
}
