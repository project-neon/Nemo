

#include "_config.h"
#include "motors.h"
#include "systemcontrol.h"



void Motors::init(){

  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);


}


void Motors::move(int motor, int speed, int direction){ //vou tentar fazer um módulo que dirija os dois ao mesmo tempo
                                                        //que não seja uma cópia do vss...
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  Serial.println("Ligou o torretoni");
  digitalWrite(STBY, HIGH); //disable standby

  bool inPin1 = LOW;
  bool inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);
  }
  else{
  digitalWrite(BIN1, inPin1);
  digitalWrite(BIN2, inPin2);
  analogWrite(PWMB, speed);
  }
}

void Motors::stop(){

  analogWrite(PWMB, 0);
  analogWrite(PWMA, 0);


  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);

  //enable standby
  digitalWrite(STBY, LOW);

}
