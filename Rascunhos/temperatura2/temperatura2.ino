#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
double temperatura;

void setup(void) 
{ 
 
 Serial.begin(115200);  
 sensors.begin(); 
} 
void loop(void) 
{  
 sensors.requestTemperatures(); // Send the command to get temperature readings  
 Serial.print(sensors.getTempCByIndex(0)); 
 temperatura = sensors.getTempCByIndex(0);

 Serial.print("               temperatura:"); 
 Serial.println(temperatura); 
 
 
   delay(1000); 
  } 
