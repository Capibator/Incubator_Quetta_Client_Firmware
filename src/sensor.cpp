#include "sensor.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

DHT dht(DHTPIN, DHTTYPE);

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