# Hardware

## NodeMCU ESP8266

Main microcontroller for Wi-Fi connectivity, Firebase communication, GPS processing, and crash-sensor inputs.

## Arduino Uno

Secondary microcontroller used to collect date/time from the RTC module and temperature from the DHT11 sensor, then forward those values to the ESP8266.

## NEO-6M GPS

Provides latitude and longitude for the accident event.

## RTC module

Provides date and time values to the Arduino Uno.

## DHT11

Provides a temperature reading used as part of the prototype accident data.

## Collision sensors

Four sensors were associated with the vehicle's front, rear, left, and right sides so the prototype could record the detected impact side.

## Connectivity

A ZTE MF937 Wi-Fi router provided the prototype's internet connection. The thesis identified continuous internet availability as a limitation for remote locations.
