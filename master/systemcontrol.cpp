
#include "systemcontrol.h"
#include "_config.h"
#include "motors.h"


ThreadController controller;


void threadColorSensors_run();
Thread threadColorSensors(threadColorSensors_run, 50);



void SystemControl::buttonStartStop(bool tipo){
    if (tipo == false){
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(3, LOW);

      //later: desligar motores
      
      
    }
    else{
      delay(500);
      digitalWrite(3, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    //COMEÇA PANCADA
    }
  }
 


void SystemControl::init(){

	Serial.begin(9600);
	delay(50);

	controller.add(&threadColorSensors);

}



void threadColorSensors_run(){

        
  int bright_read = analogRead(PIN_REFL_SENSOR);
        
}