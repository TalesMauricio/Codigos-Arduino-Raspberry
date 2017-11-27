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
#define hSoma 11205
#define len sizeof(h)/sizeof(h[0])

float bufferPeso[len] = {0};

//Funções para o sistema de controle de alimento
float obterPeso()
{
  deslocarBuffer(bufferPeso);
  bufferPeso[0] = lerCelula();

  float peso = filtraPeso(bufferPeso);

//  Serial.print(F("Peso lido: "));
//  Serial.print(peso);
//  Serial.println(F(" Kg"));
  
  //return peso;
  return 12.0;  //Valor de saída arbtrado para pular leitura da célula
}

float filtraPeso(float *x)
{
    long y = 0;
    for(char n=0; n<len; n++)
        y += x[n]*h[n];
    
    return float(y/hSoma);
}

void deslocarBuffer(float *bufferPeso)
{
  for(char k=1; k<len; k++)
  {
    bufferPeso[k] = bufferPeso[k-1];
  }
}


float lerCelula()
{
  long inic = millis();
  unsigned long Count = 0;
  digitalWrite(ADSK, LOW);
  
  delay(500); //while(digitalRead(ADDO)); //Enquanto não tiver um sinal nessa porta, ele fica preso nesse loop

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
  Serial.println(Count);

  //Calibrar as células de carga
  //float massa = -0.0016312*float(Count)+13984.113;
  float massa = float(Count);

  return(massa);
}

