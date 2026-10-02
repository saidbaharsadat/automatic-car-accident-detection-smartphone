/*
  Automatic Car Accident Detection and Notification with Smartphone
  Arduino Uno firmware excerpt reconstructed from the 2023 thesis.

  Role: read DHT11 temperature + RTC date/time and serialize the values as
  JSON for the NodeMCU ESP8266 over SoftwareSerial.
*/

#include <SoftwareSerial.h>
#include <DHT.h>
#include <virtuabotixRTC.h>
#include <ArduinoJson.h>

SoftwareSerial nodemcu(9, 10);
#define DHTPIN 2
DHT dht(DHTPIN, DHT11);

virtuabotixRTC myRTC(6, 7, 8);

void setup() {
  dht.begin();
  Serial.begin(9600);
  nodemcu.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  const float temp = dht.readTemperature();
  myRTC.updateTime();

  String date = String(myRTC.dayofmonth) + "/" + String(myRTC.month) + "/" + String(myRTC.year);
  String time = String(myRTC.hours) + ":" + String(myRTC.minutes) + ":" + String(myRTC.seconds);

  StaticJsonDocument<256> doc;
  doc["date"] = date;
  doc["time"] = time;
  doc["temperature"] = temp;
  serializeJson(doc, nodemcu);

  Serial.print("Date: ");
  Serial.println(date);
  Serial.print("Time: ");
  Serial.println(time);
  Serial.print("Temperature: ");
  Serial.println(temp);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}
