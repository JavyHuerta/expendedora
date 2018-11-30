#include <Wire.h>
#include <Stepper.h>

// Motor 1
int m1In1 = 4;
int m1In2 = 5;
int m1In3 = 6;
int m1In4 = 7;
Stepper motor1(2048,m1In1, m1In3, m1In2, m1In4);

//Motor 2
int m2In1 = 8;
int m2In2 = 9;
int m2In3 = 10;
int m2In4 = 11;
Stepper motor2(2048,m2In1, m2In3, m2In2, m2In4);


int x; // Variable para el evento
void setup()
{
  motor1.setSpeed(3);
  motor2.setSpeed(3);
  Wire.begin(1);
  Wire.onReceive(recibidoEvento); 
  Serial.begin(9600);
  MoverM1();
 
}


void loop()
{
 delay(2500);
 if(x==1){
  MoverM1();
  x=0;
  }

  if(x==2){
  MoverM2();
  x=0;
  }
 
}

void recibidoEvento(int recepcion)
  {
    while(Wire.available()) 
    {
      x = Wire.read(); 
    }

  }

  void MoverM1(){
    motor1.step(2048);
    digitalWrite(m1In1, LOW);
    digitalWrite(m1In2, LOW);
    digitalWrite(m1In3, LOW);
    digitalWrite(m1In4, LOW);
  }

  void MoverM2(){
    motor2.step(-2048);
    digitalWrite(m2In1, LOW);
    digitalWrite(m2In2, LOW);
    digitalWrite(m2In3, LOW);
    digitalWrite(m2In4, LOW);
  }
