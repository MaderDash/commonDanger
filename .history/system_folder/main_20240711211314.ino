#include <Wire.h> 
#include "RTCManager.h"
#include "SDLogger.h"
#include "FingerprintManager.h" 

// ... (global constants, pin definitions)

// Create instances of your classes
RTCManager rtcManager;
SDLogger sdLogger(chipSelect); 
SoftwareSerial biometricenroll(2, 3);
FingerprintManager fingerprintManager(biometricenroll); 

void setup() {
  Serial.begin(57600);
  // ... 

  rtcManager.setupRTC();
  if (!sdLogger.initialize()) {
    // Handle SD
  }
}

void loop() {
  // ... 
}
