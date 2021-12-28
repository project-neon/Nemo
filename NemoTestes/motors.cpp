#include "_config.h"
#include "motors.h"

//Inicializa os pinos
void Motors::init(){

    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY,HIGH);
}

//Desliga os motores
void Motors::stop(){
  
    digitalWrite(PWMA, LOW);
    digitalWrite(PWMB, LOW); 
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
}

//Executa o teste dos motores
void Motors::driveTeste(float m1, float m2){

    m1 = min(max(m1, -100), 100);
    m2 = min(max(m2, -100), 100);

    int powerOutA = m1 * (MOTOR_ABS_MAX / 100.0);
    int powerOutB = m2 * (MOTOR_ABS_MAX / 100.0);

    analogWrite(PWMA,powerOutA);
    analogWrite(PWMB,powerOutB);

    digitalWrite(AIN1, m1 > 0 ? LOW : HIGH);
    digitalWrite(AIN2, m1 > 0 ? HIGH : LOW);

    digitalWrite(BIN1, m2 > 0 ? LOW : HIGH);
    digitalWrite(BIN2, m2 > 0 ? HIGH : LOW);

}
