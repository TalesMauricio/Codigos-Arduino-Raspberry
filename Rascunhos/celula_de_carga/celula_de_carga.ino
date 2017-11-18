#define  ADDO  4  //DOUT
#define  ADSK  3  //SCK

#define motor 13


unsigned long convert;

void setup()
{
  Serial.begin(115200);
  pinMode(ADDO, INPUT_PULLUP);   
  pinMode(ADSK, OUTPUT);        
  pinMode(motor, OUTPUT);
   

} 

void loop()
{
  
  float quantidadeRacao = 10.0;
  lerCelula();
  //alimentaPeixes(quantidadeRacao);

  delay(500);
} 


unsigned long lerCelula()
{
  unsigned long Count = 0;
  unsigned char i;
  
  digitalWrite(ADSK, LOW);
  
  while(digitalRead(ADDO));
  
  for(i=0;i<24;i++)
  {
     digitalWrite(ADSK, HIGH);
     Count = Count << 1;
     digitalWrite(ADSK, LOW);
     if(digitalRead(ADDO)) Count++;
  
  } //end for
  
  digitalWrite(ADSK, HIGH);
  Count = Count^0x800000;
  digitalWrite(ADSK, LOW);

  float massa = -0.0016312*float(Count)+13984.113;
  
  Serial.print(Count);
  Serial.print("           ");
  Serial.println(massa);
  
  return(Count);
  
}

void alimentaPeixes(float valorAlimento)
{
  
  digitalWrite(motor, HIGH);
  while(lerCelula()<=valorAlimento) delay(1000);
  digitalWrite(motor, LOW);
  
}









