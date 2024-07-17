#include "RTCManager.h"

RTCManager::RTCManager() : century(false), h12Flag(false), pmFlag(false) {} 

void RTCManager::setupRTC() {
  rtc.begin();
  // ... (any RTC initialization)
}

String RTCManager::getFormattedTime() {
//TODO I need to make a value useing f(), to make the 
//time look like 12:00:00 instead of 12:00:00.0
	String time = String(rtc.getHours()) + ":" + String(rtc.getMinutes()) + ":" +
	String(rtc.getSeconds());
	return time;
}


// ... (implement other RTC-related methods)
