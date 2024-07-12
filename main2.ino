#include <Wire.h>
#include <DS3231.h>
#include <SD.h>
#include <SPI.h>
#include <TimeLib.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

const int chipSelect = 4;
int INTERVAL = 3;

uint8_t id;
int count = 1;
int admin = 1;
bool adminfinger = true;
bool relay = true;
void (*resetFunc)(void) = 0;

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial biometricenroll(2, 3);
const int relayPin1 = A0;
#else
#define biometricenroll Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&biometricenroll);

DS3231 myRTC;
bool century = false;
bool h12Flag;
bool pmFlag;
byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
bool alarmDy, alarmH12Flag, alarmPmFlag;

void setup()
{
	Wire.begin();
	Serial.begin(57600);
	delay(500);

	Serial.println(timeStatus() != timeSet ? F("Unable to sync with the RTC") : F("RTC has set the system time"));

	while (!Serial)
		;

	Serial.print(F("Initializing SD card..."));
	if (!SD.begin(chipSelect))
	{
		Serial.println(F("Card failed, or not present"));
		while (1)
			;
	}
	Serial.println(F("Card initialized."));
}

void processingCard()
{
	File dataFile = SD.open("profile.txt", FILE_WRITE);

	String output = F("2");
	output += century ? F("1") : F("0");
	output += String(myRTC.getYear(), DEC) + F(" ");
	output += String(myRTC.getMonth(century), DEC) + F(" ");
	output += String(myRTC.getDate(), DEC) + F(" ");
	output += String(myRTC.getDoW(), DEC) + F(" ");
	output += String(myRTC.getHour(h12Flag, pmFlag), DEC) + F(" ");
	output += String(myRTC.getMinute(), DEC) + F(" ");
	output += String(myRTC.getSecond(), DEC) + F(" ");

	if (h12Flag)
	{
		output += pmFlag ? F(" PM ") : F(" AM ");
	}
	else
	{
		output += F(" 24h ");
	}

	output += F("T=");
	output += String(myRTC.getTemperature(), 2);
	output += myRTC.oscillatorCheck() ? F(" O+") : F(" O-");

	Serial.println(output);
	String converted = String(output);
	if (dataFile)
	{
		dataFile.println(converted);
		dataFile.close();
	}
}

void loop()
{
	processingCard();

	delay(1000);
}