#include "SD_Logger.h"  // Include dependent headers first 

#ifndef SDLOGGER_H
#define SDLOGGER_H

// ... rest of your header content ...

#endif


SDLogger::SDLogger(int chipSelect) :
  csPin(chipSelect) {}

bool SDLogger::initialize() {
  if (!SD.begin(csPin)) {
    return false;
  }
  return true;
}

void SDLogger::logData(const String& data) {
  File file = SD.open("log.txt", FILE_WRITE);
  if (file) {
    file.println(data);
    file.close();
  } 
}
