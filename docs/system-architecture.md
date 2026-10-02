# System Architecture

The original prototype consisted of three main subsystems: an in-vehicle IoT module, a Firebase backend, and the Hadisa mobile application.

## 1. IoT module

The NodeMCU ESP8266 acted as the main controller responsible for connectivity, GPS data handling, collision-side detection, and publishing the accident event to Firebase Realtime Database.

An Arduino Uno was used as a secondary controller for the RTC and DHT11 sensor. It serialized date, time, and temperature values as JSON and sent them to the ESP8266 over serial communication.

Four crash sensors represented front, rear, left, and right impact locations.

## 2. Firebase backend

The project used several Firebase services:

- **Realtime Database:** live bridge between the IoT module and the mobile application.
- **Authentication:** account registration and login.
- **Cloud Firestore:** user information and accident records.
- **Cloud Storage:** user profile images.

## 3. Hadisa mobile application

The Xamarin.Forms application provided authentication, registration, profile management, accident notifications, accident records, and a map-based accident view.

A background/foreground service listened for incoming accident data so that an event could be surfaced even when the app was not actively open.

## Accident event model

The thesis prototype transmitted fields including:

- Date
- Time
- Latitude
- Longitude
- Collision side
- Temperature

The mobile app then combined this live event with stored driver information before displaying it to users.
