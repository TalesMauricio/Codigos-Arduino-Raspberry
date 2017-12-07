
/**** Pinos da célula de carga ****/
#define  ADSK  6  //SCK
#define  ADDO  7  //DOUT

float bufferPeso[127] = {0};
float tara = 0;

void setup() {
  Serial.begin(115200);
  //Célula de carga
  pinMode(ADDO, INPUT_PULLUP);   
  pinMode(ADSK, OUTPUT);

  tara = tirarTara(bufferPeso);
  Serial.print("tara: ");
  Serial.println(tara);
}


void loop() {
  obterPeso(bufferPeso);
  //delay(100);
  
}
