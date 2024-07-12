#ifndef RTC_MANAGER_H
#define RTC_MANAGER_H

#include <DS3231.h> 
#include <TimeLib.h>

class RTCManager {
public:
  RTCManager();
  void setupRTC();
  String getFormattedTime(); 
  // ... (add methods to get/set alarms, temperature, etc.)

private:
  DS3231 rtc;
  bool century;
  bool h12Flag;
  bool pmFlag;
  // ... (other RTC-related variables)
};

#endif
