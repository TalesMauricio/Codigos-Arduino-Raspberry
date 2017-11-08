//Aqui vai tudo relacionado ao acionamento de cargas, medição e controle dos motores

void DespejarRacao()
{
  digitalWrite(fuso, HIGH);
  delay(100);
  digitalWrite(fuso, LOW);
}

void alimentaPeixes(float valorAlimento)
{
  digitalWrite(fuso, HIGH);
  while(lerCelula()<=valorAlimento) delay(100);
  digitalWrite(fuso, LOW);
}
