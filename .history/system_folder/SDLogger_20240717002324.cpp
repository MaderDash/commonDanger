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


