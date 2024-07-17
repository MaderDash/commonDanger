#include <SoftwareSerial.h>
#include "Adafruit_Fingerprint.h"
#include "FingerprintManager.h"

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