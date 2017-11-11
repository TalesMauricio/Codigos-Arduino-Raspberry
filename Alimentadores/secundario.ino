//Aqui vai tudo relacionado aos sensores secundários e a comunicação i2c com o outro módulo

void requisitarMedidas()
{
   Wire.requestFrom(8, sizeof(Dados));    // request 6 bytes from slave device #8

   if (Wire.available())// slave may send less than requested
     for(int k=0; k<sizeof(Dados); k++)
       dados.bytes[k] = Wire.read(); // receive a byte as character 
}

