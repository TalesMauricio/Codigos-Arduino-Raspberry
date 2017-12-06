#include <OneWire.h> //DS12B20
#include <Wire.h>
#include "dados.cpp"

#define pinTemp 8
#define pinPH   A1
#define pinTurb A2
#define pinCond A3
#define pinOxig A4

OneWire  ds(pinTemp);  //(a 4.7K resistor is necessary)
Dados_t dados;

void setup() {
  pinMode(8,OUTPUT);
  Serial.begin(115200);
  Wire.begin(8);                // join i2c bus with address #1
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
  
  dados.valor.temperatura = lerTemp();
  dados.valor.ph = analogRead(pinPH);
//  dados.valor.turbidez = analogRead(pinTurb);
//  dados.valor.condutividade = analogRead(pinCond);
//  dados.valor.oxigen = analogRead(pinOxig);

  Serial.print("  Temperature2 = ");
  Serial.print( (float)dados.valor.temperatura / 16.0 );
  Serial.println(" Celsius, ");
}

void requestEvent() { // function that executes whenever data is requested by master
  Wire.write(dados.bytes);
}

int16_t lerTemp(void) {
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  
  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return 255;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return 255;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  long inic = millis();
  while(millis()-inic  < 800);
  delay(750);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( byte i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);   
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
//  celsius = (float)raw / 16.0; 
//  Serial.print("  Temperature = ");
//  Serial.print(celsius);
//  Serial.println(" Celsius, "); 

  return raw;
}
