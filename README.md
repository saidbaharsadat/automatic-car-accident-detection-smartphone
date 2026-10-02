# Automatic Car Accident Detection and Notification with Smartphone

**Bachelor's Thesis Project (2023)**  
**Author:** Said Bahar Sadat  
**Supervisor:** Engr. Mohammad Saber Niazy  
**Institution:** Faculty of Computer Science, Khurasan University, Jalalabad  

This repository documents the prototype developed for my bachelor's thesis, **Automatic Car Accident Detection and Notification with Smartphone**. The project combines an in-vehicle IoT module, a cross-platform mobile application, and Firebase cloud services to detect a collision, collect accident information, and notify registered users and emergency-service roles with the accident location.

> **Repository status:** archival / portfolio documentation of the original 2022-2023 prototype. The firmware and application files included here are reconstructed and sanitized from code excerpts contained in the final thesis. They should not be treated as a complete dump of the original development workspace.

## Project idea

The prototype was designed around three connected parts:

1. **IoT module** installed in a vehicle to detect a collision and collect sensor data.
2. **Hadisa mobile application** to receive accident events, show driver information, display the accident on a map, and coordinate response roles.
3. **Firebase backend** to exchange live accident data, authenticate users, store profiles, and keep accident records.

## Main capabilities

- Detect a collision using four crash/collision sensors positioned for front, rear, left, and right impact detection.
- Read GPS coordinates from a NEO-6M GPS module.
- Read date/time from an RTC module and temperature from a DHT11 sensor.
- Send accident data from the ESP8266 to Firebase Realtime Database.
- Notify the mobile application when a new accident event appears.
- Display accident location and driver information on Google Maps.
- Support multiple user roles: Driver, Driver Relative, Traffic Police, Ambulance, and Fire Fighter.
- Store user information and accident history using Firebase Cloud Firestore.
- Store profile images using Firebase Cloud Storage.

## System architecture

```text
Crash sensors / GPS / RTC / DHT11
              |
              v
      Arduino Uno + ESP8266
              |
           Wi-Fi/4G
              |
              v
       Firebase Backend
       |      |       |
       |      |       +-- Cloud Storage
       |      +---------- Cloud Firestore
       +----------------- Realtime Database / Authentication
              |
              v
        Hadisa Mobile App
              |
      +-------+--------+----------------+
      |       |        |                |
    Driver  Relative  Police        Ambulance / Fire
```

A collision event contains fields such as date, time, latitude, longitude, detected side, and temperature. The mobile application listens for new accident data, raises an alarm, fetches the driver's stored information, and presents the event on the map.

## Hardware used

| Component | Role |
|---|---|
| NodeMCU ESP8266 | Main IoT microcontroller and Firebase/Wi-Fi communication |
| Arduino Uno | Secondary controller for RTC and DHT11 data acquisition |
| NEO-6M GPS | Vehicle location |
| RTC module | Date and time |
| DHT11 | Temperature measurement |
| 4x crash/collision sensors | Front, rear, left and right collision detection |
| ZTE MF937 Wi-Fi router | Internet connectivity for the prototype |
| Vehicle battery + converters | Prototype power source |

## Software stack

- **Mobile:** Xamarin.Forms, XAML, C#/.NET
- **Cloud:** Firebase Realtime Database, Cloud Firestore, Authentication, Cloud Storage
- **Maps:** Google Maps / Xamarin.Forms Google Maps integration
- **Firmware:** Arduino C/C++
- **Data format:** JSON
- **Development environment:** Visual Studio and Arduino tooling

## Repository structure

```text
.
├── README.md
├── CITATION.cff
├── .gitignore
├── docs/
│   ├── system-architecture.md
│   ├── hardware.md
│   ├── mobile-application.md
│   ├── testing-and-results.md
│   └── thesis-publication-note.md
├── firmware/
│   ├── nodemcu_esp8266/
│   │   └── nodemcu_esp8266.ino
│   └── arduino_uno/
│       └── arduino_uno.ino
├── app-excerpts/
│   ├── README.md
│   └── FirebaseRTBService.cs
└── config/
    └── secrets.example.h
```

## Event flow

1. A crash sensor is activated by impact.
2. The ESP8266 identifies the side of the collision.
3. GPS coordinates are read from the NEO-6M module.
4. Date, time, and temperature values are received from the Arduino Uno.
5. The collected data is serialized and sent to Firebase Realtime Database.
6. The Hadisa app's background/foreground service detects the new event.
7. The app raises an alarm, retrieves the driver's profile, and displays the accident on a map.
8. Emergency-service users can view/deploy to the accident operation and the completed event can be retained as an accident record.

## Security note

The original thesis contains development credentials embedded in code screenshots and listings. Those values are **not** included in this repository. Configuration must be supplied locally through ignored files such as `secrets.h` and platform-specific Firebase configuration files.

If the original credentials are still active, they should be rotated before any thesis PDF or historical source archive is made public.

## Limitations of the original prototype

The prototype depended on internet connectivity between the in-vehicle ESP8266 and Firebase. The thesis identified loss of connectivity in remote areas as an important limitation and discussed alternative communication links as future work.

The project was an academic prototype and was **not** designed, certified, or validated as a production automotive safety system.

## Thesis

The final thesis was submitted in May 2023 for the partial fulfillment of the BS Computer Science degree at Khurasan University. The original PDF is intentionally not included in this repository until embedded credentials and other sensitive development information are redacted.

## Author

**Said Bahar Sadat**  
Bachelor of Computer Science, Khurasan University  

## Acknowledgment

Supervised by **Engr. Mohammad Saber Niazy**.
