#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
#include <SD.h>
#include "RTClib.h"

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
const int chipSelect = 10;
File tempLog;
RTC_DS1307 RTC;

LiquidCrystal lcd(6, 7, 8, 9, 11, 12);

void setup() { 
  Serial.begin(9600);
   while (!Serial) {
    ; 
  lcd.begin(16, 2);
  //         ----------------  
  lcd.print("Current temp (F)");
   sensors.begin();
   }

Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    while (1);
  }
  Serial.println("Initialization done.");

tempLog = SD.open("templog.txt", FILE_WRITE);  
if (! tempLog) {
  Serial.println("Error opening templog.txt");
  while(1);
}
char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      tempLog = SD.open(filename, FILE_WRITE);
      break;  // leave the loop!
    }

  Serial.print("Writing to: ");
  Serial.println(filename);
  tempLog.println("Data Logging File");
  tempLog.println("Date,Temp(F)");
  } 
} 

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempFByIndex(0);
  lcd.setCursor(6, 1);
  lcd.print(temperature);
  Serial.println(temperature);
  //-----------------------------------------------------------

String dataString = "";

//date time stuff-------------------------------------------

DateTime now = RTC.now();
  // log time
// tempLog.print(now.unixtime()); // seconds since 1/1/1970
//  tempLog.print(", ");
  tempLog.print('"');
  tempLog.print(now.year(), DEC);
  tempLog.print("/");
  tempLog.print(now.month(), DEC);
  tempLog.print("/");
  tempLog.print(now.day(), DEC);
  tempLog.print(" ");
  tempLog.print(now.hour(), DEC);
  tempLog.print(":");
  tempLog.print(now.minute(), DEC);
  tempLog.print(":");
  tempLog.print(now.second(), DEC);
  tempLog.print('"');

  tempLog.print(",");
  tempLog.print(temperature);
  tempLog.print(",");
  delay(500);

tempLog.println(dataString);
tempLog.flush();

}
