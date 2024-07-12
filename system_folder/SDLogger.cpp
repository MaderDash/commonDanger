#include <SPI.h>
#include <SD.h>

#define CS_PIN 10

// SD card logger class
class SDLogger {
 public:
  SDLogger(int chipSelect);
  bool initialize();
  void logData(const String& data);

 private:
  int csPin;
};

SDLogger::SDLogger(int chipSelect) : csPin(chipSelect) {}

bool SDLogger::initialize() {
  if (!SD.begin(csPin)) {
    return false; // Initialization failed
  }
  return true; 
}

void SDLogger::logData(const String& data) {
  File dataFile = SD.open("profile.txt", FILE_WRITE); 
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  } else {
    // Handle file opening error (e.g., log to Serial)
  }
}

void setup() {
  Serial.begin(9600);
  // Initialize SD card logger
  SDLogger logger(CS_PIN);
  if (!logger.initialize()) {
    Serial.println("Card failed, or not present");
    return;
  }
}

void loop() {
  // Example usage: Log a message every 5 seconds
  if (millis() % 5000 == 0) {
    SDLogger logger(CS_PIN);
    String message = "Time: " + String(millis() / 1000) + " seconds";
    logger.logData(message); 
  }
}
