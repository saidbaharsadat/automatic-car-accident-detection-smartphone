# Hadisa Mobile Application

The mobile application was implemented with Xamarin.Forms, XAML, and C#/.NET.

## Main screens

- Login
- Registration
- Home / active accident card
- Accident records
- Accident map
- Profile
- Password recovery
- About developer

## User roles

### Driver
Owns the in-vehicle device association and can maintain profile/emergency-contact information.

### Driver Relative
Uses the driver's identifier to receive relevant accident information.

### Traffic Police / Ambulance / Fire Fighter
Emergency-service roles can view accident operations and, in the original prototype workflow, deploy to an operation.

## Map workflow

The accident map shows the driver's accident position and can also show the positions/routes of deployed emergency-service users.

## Data services

- Firebase Authentication for login and registration
- Firebase Realtime Database for live accident events
- Cloud Firestore for user information and accident records
- Cloud Storage for profile images
