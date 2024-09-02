#ifndef SENSOR_H 
#define SENSOR_H 
#include "pinouts.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

// INITIALIZETD
extern DHT dht;

// Structs
struct sensor
{
  float curTemp;
  float curHum;
  unsigned long curTime, prevTimeSens;
  const uint16_t updateTime = 2000;
};

// update the crucial sensor every 2 seconds.. well updates all sensors.
void UpdateSensor(sensor *sensor);



#endif