//Aqui vai tudo relacionado aos sensores secundários e a comunicação i2c com o outro módulo


void medirBateria()
{
  digitalWrite(enBatPin, HIGH);
  delay(1);
  nivelBateria = analogRead(leBatPin);
  digitalWrite(enBatPin, LOW);
}

void reqMedidasSec()
{
   Dados_t dado;
   Wire.requestFrom(8, sizeof(Dados_t));    // request 6 bytes from slave device #8

   if (Wire.available())
   {     // slave may send less than requested
     for(int k=0; k<sizeof(Dados_t); k++)
       dado.bytes[k] = Wire.read(); // receive a byte as character 
     dados = dado.valor;
   } else {
    dados = {0,0,0,0,0};
   }
   
   //dados = dado.valor;
}
