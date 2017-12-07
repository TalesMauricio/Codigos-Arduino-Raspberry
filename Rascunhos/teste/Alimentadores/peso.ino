//Aqui vai tudo relacionado ao acionamento de cargas, medição e controle dos motores
/*
const int16_t h[] = {-920, -1133, -353, 2816, 9452, 19862, 33131,
                      47092, 58822, 65535, 65535, 58822, 47092,
                      33131, 19862, 9452, 2816, -353, -1133, -920};
#define hSoma 468608

//Funções para o sistema de controle de alimento
float obterPeso(float *bufferPeso)
{
  
  deslocarBuffer(bufferPeso);
  bufferPeso[0] = lerCelula();
  
  return filtraPeso(bufferPeso);
}

float filtraPeso(float *x)
{
    long y = 0;
    for(char n=0; n<20; n++)
        y += x[n]*h[n];
    
    return float(y/hSoma);
}

void deslocarBuffer(float *bufferPeso)
{
  for(char k=1; k<20; k++)
  {
    bufferPeso[k] = bufferPeso[k-1];
  }
}
*/

//float lerCelula()
unsigned long lerCelula()
{
  //long inic = millis();
  unsigned long Count = 0;
  digitalWrite(ADSK, LOW);
  
  while(digitalRead(ADDO));
  
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

  //Serial.print("tempo decorrido: ");
  //Serial.println(inic-millis());

  //return(massa)
  return(Count);
}

