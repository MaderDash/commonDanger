#include <SoftwareSerial.h>
#include "Adafruit_Fingerprint.h"
#include "FingerprintManager.h"
#include "RTCManager.h" // Add this include
#include "SDLogger.h"   // Add this include

extern RTCManager rtcManager; 
extern SDLogger sdLogger; 

FingerprintManager::FingerprintManager(SoftwareSerial& biometricSerial) : finger(biometricSerial) {} 

void FingerprintManager::setupFingerprint() {
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println(F("Found fingerprint sensor!"));
  } else {
    Serial.println(F("Did not find fingerprint sensor :("));
    while (1) {
      delay(1);
    }
  }
}
bool FingerprintManager::verifyFingerprint() {
  // ... (Your fingerprint verification logic) ... 

  if (fingerprint_verified) { 
    // Get current time from RTCManager
    String timestamp = rtcManager.getFormattedTime(); 

    // Create log string (you can add more info here)
    String logMessage = timestamp + " - Fingerprint Verified - User ID: " + String(user_id); 

    // Log to SD card using SDLogger
    sdLogger.logData(logMessage);

    // ... (rest of your actions, e.g., activate relay) ...

    return true;
  } else {
    // ... (Handle verification failure) ... 
    return false;
  }
} 