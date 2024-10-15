#ifndef FIREBASEHANDLER_H
#define FIREBASEHANLDER_H


#include <WiFi.h>
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

#define WIFI_SSID "Shoaib"
#define WIFI_PASSWORD "A0123456789"

#define DATABASE_URL "https://capibator-default-rtdb.firebaseio.com"

extern WiFiClientSecure ssl;
extern DefaultNetwork network;
extern AsyncClientClass client;
extern FirebaseApp app;
extern RealtimeDatabase Database;
extern AsyncResult result;
extern NoAuth noAuth;


void printError(int code, const String &msg);
void connectWifi(); 
void connectFirebase(); 
void pushSensorData(); 

#endif