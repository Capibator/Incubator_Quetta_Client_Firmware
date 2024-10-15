#include "firebaseHandler.h"

String name; 
WiFiClientSecure ssl;
DefaultNetwork network;
AsyncClientClass client(ssl, getNetwork(network));
FirebaseApp app;
RealtimeDatabase Database;
AsyncResult result;
NoAuth noAuth;

void printError(int code, const String &msg)
{
    Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}


void connectWifi(){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }

    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}



void connectFirebase() {
    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

    ssl.setInsecure();

    // Initialize the authentication handler.
    initializeApp(client, app, getAuth(noAuth));

    // Binding the authentication handler with your Database class object.
    app.getApp<RealtimeDatabase>(Database);

    // Set your database URL
    Database.url(DATABASE_URL);

    // In sync functions, we have to set the operating result for the client that works with the function.
    client.setAsyncResult(result);
}

void pushSensorData(){

}

// void getSensorData(){

// }


// void getInitConfig(){

// }

// void getInitConfig(){

// }