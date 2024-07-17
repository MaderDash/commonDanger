#include "RTCManager.h"

RTCManager::RTCManager() : century(false), h12Flag(false), pmFlag(false) {} 

void RTCManager::setupRTC() {
  rtc.begin();
  // Optionally set the RTC time here if needed 
}

String RTCManager::getFormattedTime() {
  // Get the current time from the RTC
  DateTime now = rtc.now(); 

  // Format the time as "YYYY-MM-DD HH:MM:SS"
  char timeString[20]; 
  sprintf(timeString, "%04d-%02d-%02d %02d:%02d:%02d", 
          now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  return String(timeString);
}

// ... (You can add methods for setting alarms, reading temperature, etc., if required) 
