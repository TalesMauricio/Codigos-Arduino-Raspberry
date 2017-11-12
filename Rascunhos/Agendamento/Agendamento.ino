/*Este código não utiliza o rtc, fazendo com q o próprio arduino se encarregue de contar e formar a hora
  Mas é possivel utilizar o rtc através de uma implementação da biblioteca Timer*/
#include <TimeLib.h>
#include <TimeAlarms.h>

uint8_t Dia = 1;
AlarmId idAgendamento;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor

  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011

  // create the alarms, to trigger at specific times
  Alarm.alarmRepeat(23,59,59, incrementarDia);
  idAgendamento = Alarm.alarmRepeat(8,30,0, DespejarRacao);
 
}

void loop() {
  Alarm.delay(1000); // wait one second between clock display
}


void agendarDespejo() {
  Serial.println("Alarm: - turn lights on");
}

// functions to be called when an alarm triggers:
void DespejarRacao() {
  Serial.println("Jah deu a hora!");
  digitalClockDisplay();
}

void incrementarDia() {
  Dia = (Dia<30) ? Dia+1 : 1; //Uma função miguê só pra testar o conceito
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

