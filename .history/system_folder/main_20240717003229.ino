#include <Wire.h> 
#include "RTCManager.h"
#include "SDLogger.h"
#include "FingerprintManager.h" 

// SD card chip select pin
const int chipSelect = 4;  

// Interval for data logging (in seconds)
const int INTERVAL = 3;

// Create instances of your classes
RTCManager rtcManager;
SDLogger sdLogger(chipSelect); 
SoftwareSerial biometricenroll(2, 3);
FingerprintManager fingerprintManager(biometricenroll); 

void setup() {
  Serial.begin(57600);

  rtcManager.setupRTC();
  if (!sdLogger.initialize()) {
    // Handle SD card initialization error
    Serial.println("SD card initialization failed!"); 
  }

  fingerprintManager.setupFingerprint();
}

void loop() {
  // ... (your main loop logic)

  // Example: Log data every INTERVAL seconds
  if (millis() % (INTERVAL * 1000) == 0) {
    String time = rtcManager.getFormattedTime();
    sdLogger.logData("Time: " + time); 
  }
}
