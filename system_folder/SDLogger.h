#include "SD_Logger.h"

SDLogger::SDLogger(int chipSelect) :
  csPin(chipSelect) {}

bool SDLogger::initialize() {
  if (!SD.begin(csPin)) {
    return false;
  }
  return true;
}

void SDLogger::logData(const String& data) {
  File file = SD.open("data.txt", FILE_WRITE);
  if (file) {
    file.println(data);
    file.close();
  } 
}
