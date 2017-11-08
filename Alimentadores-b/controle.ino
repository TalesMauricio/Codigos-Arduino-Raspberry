//Aqui vai tudo relacionado ao acionamento de cargas, medição e controle dos motores

void alimentaPeixes(float valorAlimento)
{
  digitalWrite(fuso, HIGH);
  while(lerCelula()<=valorAlimento) delay(100);
  digitalWrite(fuso, LOW);
}

