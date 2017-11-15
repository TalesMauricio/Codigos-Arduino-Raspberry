//Aqui vai tudo relacionado ao acionamento de cargas, medição e controle dos motores

//Funções para o sistema de controle de alimento
float lerCelula()
{
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
  float massa = -0.0016312*float(Count)+13984.113;
  
  return(massa);
  
}

