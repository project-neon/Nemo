#include "_config.h"
#include "motors.cpp"

void setup(){

    Serial.begin(9600);
    Serial.println("Setup Start...  ");
    pinMode(Button1, INPUT);
    pinMode(Button2, INPUT);
    Serial.println("PODE APERTAR NESSA PARADA...  ");
    Motors::init();
    Serial.println("VRUM VRUM VRUUMMMMMM");
    delay(900);
}
void loop(){

    if (Button1 == HIGH) {
        motorstart(50);
        
}
    if (Button2 == HIGH){
        delay(20)
        Motors::stop();
        delay(20)
    }