#include <Wire.h>                  // Library for I2C communication
#include <DS3231.h>                // Library for RTC
#include <SD.h>                    // Library for SD card access
#include <SPI.h>                   // Library for SPI communication#include
#include <TimeLib.h>               // Library for timekeeping
#include <Adafruit_Fingerprint.h>  // BioMetric Reader
#include <SoftwareSerial.h>        // Library for assigning an adittional rx an tx ports
 
// begining Sd Data logger
const int chipSelect = 4;  // SD card chip select pin
int INTERVAL = 3;          // Interval for data logging (in seconds)
// I2C device found at address 0x57  //
// I2C device found at address 0x68  //
 
///////////////   Biometriclock ///////////////////
 
uint8_t id;
int count = 1;
int admin = 1;
bool adminfinger = true;
bool relay = true;
void(* resetFunc) (void) = 0;//declare reset function at address 0
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial biometricenroll(2, 3);  //is d1(yellow) d2(brown) 
const int relayPin1 = A0; // TODO: Change according to your board 14 = d5 for node and wont go high on reset
 
 
#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define biometricenroll Serial1
 
#endif
 
 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&biometricenroll);
 
 
 
DS3231 myRTC;             // Pins A4 & A5 
bool century = false;
bool h12Flag;
bool pmFlag;
byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
bool alarmDy, alarmH12Flag, alarmPmFlag;
 
void setup() {
  Wire.begin();         // Start the I2C interface
  Serial.begin(57600);  // Initialize serial communication with a baud rate of 57600
    delay(500);
 
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");  // Print error message if unable to sync with RTC
  else
    Serial.println("RTC has set the system time");  // Print success message if RTC has set the system time
  while (!Serial)
    ;
  {
    ;  // Wait for serial port to connect (needed for native USB port only)
  }
 
  ///////////  SD Card Set Up ///////////
  Serial.print("Initializing SD card...");
 
  // Check if the SD card is present and can be initialized
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");  // Print error message if SD card initialization fails
    while (1)
      ;
  }
  Serial.println("Card initialized.");  // Print success message if SD card is initialized successfully
}
 
 
void loop() {
 
  // open Data File on SD card //
  File dataFile = SD.open("profile.txt", FILE_WRITE);
 
  // send what's going on to the serial monitor.
 
  // Start with the year
  Serial.print("2");
  dataFile.print("2");
  if (century) {  // Won't need this for 89 years.
    Serial.print("1");
    dataFile.print("1");
  } else {
    Serial.print("0");
    dataFile.print("0");
  }
  Serial.print(myRTC.getYear(), DEC);
  Serial.print(' ');
  dataFile.print(myRTC.getYear(), DEC);
  dataFile.print(" ");
 
  // then the month
  Serial.print(myRTC.getMonth(century), DEC);
  //    Serial.print(myRTC.getMonth(), DEC);
  Serial.print(" ");
  dataFile.print(myRTC.getMonth(century), DEC);
  dataFile.print(" ");
 
  // then the date
  Serial.print(myRTC.getDate(), DEC);
  Serial.print(" ");
  dataFile.print(myRTC.getDate(), DEC);
  dataFile.print(" ");
 
  // and the day of the week
  Serial.print(myRTC.getDoW(), DEC);
  Serial.print(" ");
  dataFile.print(myRTC.getDoW(), DEC);
  dataFile.print(" ");
 
  // Finally the hour, minute, and second
  Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC);
  Serial.print(" ");
  dataFile.print(myRTC.getHour(h12Flag, pmFlag), DEC);
  dataFile.print(" ");
  Serial.print(myRTC.getMinute(), DEC);
  Serial.print(" ");
  dataFile.print(myRTC.getMinute(), DEC);
  dataFile.print(" ");
  Serial.print(myRTC.getSecond(), DEC);
  Serial.print(" ");
  dataFile.print(myRTC.getSecond(), DEC);
  dataFile.print(" ");
  // Add AM/PM indicator
  if (h12Flag) {
    if (pmFlag) {
      Serial.print(" PM ");
      dataFile.print(" PM ");
    } else {
      Serial.print(" AM ");
      dataFile.print(" AM ");
    }
  } else {
    Serial.print(" 24h ");
    dataFile.print(" 24h ");
  }
 
  // Display the temperature
  Serial.print("T=");
  Serial.print(myRTC.getTemperature(), 2);
  dataFile.print("T=");
  dataFile.print(myRTC.getTemperature(), 2);
 
  // Tell whether the time is likely to be valid //
  if (myRTC.oscillatorCheck()) {
    Serial.print(" O+");
    dataFile.print(" O+");
  } else {
    Serial.print(" O-");
    dataFile.print(" O-");
  }
 
 
  Serial.println();
  dataFile.print("\r\n");
  dataFile.close();
  delay(1000);
}