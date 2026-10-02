/*
  Automatic Car Accident Detection and Notification with Smartphone
  NodeMCU ESP8266 firmware excerpt reconstructed from the 2023 thesis.

  Security change:
  - Original hard-coded credentials are intentionally removed.
  - Create a local secrets.h based on ../../config/secrets.example.h.

  This file documents the core prototype flow and is not presented as a
  complete reproduction of the original development workspace.
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include "secrets.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

TinyGPSPlus gps;
SoftwareSerial gpsSerial(D2, D3);
SoftwareSerial arduinoSerial(D6, D5);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

static const int GPS_BAUD = 9600;
static const int LED_PIN = D0;

String uid;
String databasePath;
String accidentDate;
String accidentTime;
String accidentSide;
String temperature;
String latitude;
String longitudeValue;

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(250);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void updateGps() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    latitude = String(gps.location.lat(), 6);
    longitudeValue = String(gps.location.lng(), 6);
  }
}

void readArduinoJson() {
  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, arduinoSerial) == DeserializationError::Ok) {
    if (!doc["date"].isNull()) accidentDate = doc["date"].as<String>();
    if (!doc["time"].isNull()) accidentTime = doc["time"].as<String>();
    if (!doc["temperature"].isNull()) temperature = doc["temperature"].as<String>();
  }
}

void sendAccident() {
  if (!Firebase.ready()) return;

  updateGps();
  readArduinoJson();

  FirebaseJson event;
  event.add("Date", accidentDate);
  event.add("Time", accidentTime);
  event.add("Latitude", latitude);
  event.add("Longtitude", longitudeValue); // field spelling retained from prototype
  event.add("Side", accidentSide);
  event.add("Tempreture", temperature);    // field spelling retained from prototype

  if (!Firebase.RTDB.setJSON(&fbdo, databasePath, &event)) {
    Serial.println(fbdo.errorReason());
  }
}

void handleCrashPin(uint8_t pin, const char* side) {
  if (digitalRead(pin) != HIGH) {
    accidentSide = side;
    sendAccident();
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);
  arduinoSerial.begin(9600);
  gpsSerial.begin(GPS_BAUD);

  pinMode(D1, INPUT); // front
  pinMode(D9, INPUT); // left (as documented in thesis prototype)
  pinMode(D7, INPUT); // right
  pinMode(D4, INPUT); // rear/back
  pinMode(LED_PIN, OUTPUT);

  initWiFi();

  config.api_key = FIREBASE_API_KEY;
  config.database_url = FIREBASE_DATABASE_URL;
  auth.user.email = FIREBASE_USER_EMAIL;
  auth.user.password = FIREBASE_USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;
  config.max_token_generation_retry = 5;

  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);

  while (auth.token.uid == "") {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }

  uid = auth.token.uid.c_str();
  databasePath = "/Acident Detected/" + uid; // original prototype path spelling
}

void loop() {
  updateGps();
  readArduinoJson();

  handleCrashPin(D4, "Back");
  handleCrashPin(D1, "Front");
  handleCrashPin(D9, "Left");
  handleCrashPin(D7, "Right");
}
