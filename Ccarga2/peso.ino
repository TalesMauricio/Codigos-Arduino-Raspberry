//Aqui vai tudo relacionado ao acionamento de cargas, medição e controle dos motores

const int8_t h[] = { -51, -10, -11, -12, -13, -13, -14, -14, -14, 
                      -14, -14, -14, -13, -13, -12, -10, -9, -7,
                      -4, -2, 1, 4, 8, 12, 16, 21, 26, 31, 37, 43,
                      50, 56, 63, 71, 78, 86, 94, 102, 110, 119,
                      127, 135, 144, 152, 161, 169, 177, 185, 192, 
                      200, 206, 213, 219, 225, 231, 235, 240, 244,
                      247, 250, 252, 253, 254, 255, 254, 253, 252, 
                      250, 247, 244, 240, 235, 231, 225, 219, 213, 
                      206, 200, 192, 185, 177, 169, 161, 152, 144, 
                      135, 127, 119, 110, 102, 94, 86, 78, 71, 63, 
                      56, 50, 43, 37, 31, 26, 21, 16, 12, 8, 4, 1, 
                      -2, -4, -7, -9, -10, -12, -13, -13, -14, -14,
                      -14, -14, -14, -14, -13, -13, -12, -11, -10, -51 };
#define hSoma 11205.0
#define len sizeof(h)/sizeof(h[0])

//Funções para o sistema de controle de alimento


float tirarTara(float *bufferPeso)
{
//  for(int n=0; n<100; n++){
//    bufferPeso[0] = lerCelula();
//    deslocarBuffer(bufferPeso);
//  }
  float y = 0;
    for(int n=0; n<100; n++)
      y += lerCelula();
  return (y/881300);
}

float obterPeso(float *bufferPeso)
{
  deslocarBuffer(bufferPeso);
  bufferPeso[0] = lerCelula();

  //float peso = filtraPeso(bufferPeso);
  float peso = 0.0042792*filtraPeso(bufferPeso);//+999.75;//
  //peso = peso<0 ? 0 : peso>10 ? 10 : peso;

  //Serial.print(F("Peso lido: "));
  Serial.println(peso);
  //Serial.println(F(" Kg"));
  
  //return peso;
  return peso;  //Valor de saída arbtrado para pular leitura da célula
}

float filtraPeso(float *x)
{
    float y = 0;
    for(int n=0; n<len; n++)
        y += x[n]*h[n];
    return -y/(hSoma);
}

void deslocarBuffer(float *bufferPeso)
{
  for(int k=1; k<len; k++)
  {
    bufferPeso[k] = bufferPeso[k-1];
  }
}


float lerCelula()
{
  long Count = 0;
  digitalWrite(ADSK, LOW);
  
  //delay(200);
  while(digitalRead(ADDO)); //Enquanto não tiver um sinal nessa porta, ele fica preso nesse loop

  for(int i=0;i<24;i++)
  {
     digitalWrite(ADSK, HIGH);
     Count = Count << 1;
     digitalWrite(ADSK, LOW);
     if(digitalRead(ADDO)) Count++;
  
  } //end for
  
  digitalWrite(ADSK, HIGH);
  Count = Count^0x800000;
  digitalWrite(ADSK, LOW);
  //Serial.println(( float)Count);

  return((float)Count);
}

