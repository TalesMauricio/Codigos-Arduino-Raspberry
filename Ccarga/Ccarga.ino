
/**** Pinos da célula de carga ****/
#define  ADSK  3  //SCK
#define  ADDO  4  //DOUT

void setup() {
  Serial.begin(115200);
  //Célula de carga
  pinMode(ADDO, INPUT_PULLUP);   
  pinMode(ADSK, OUTPUT);
}


void loop() {
  obterPeso();
  //delay(100);
  
}
