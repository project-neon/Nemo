
#include "systemcontrol.h"
#include "_config.h"
#include "motors.h"


ThreadController controller;


void threadColorSensors_run();
Thread threadColorSensors(threadColorSensors_run, 100);


void threadInfraSensor_run();
Thread threadInfraSensor(threadInfraSensor_run, 1000);



bool SystemControl::buttonStartStop(bool button_press){
  if (button_press){  
    if (button_state == 0){
	    button_state++;
      delay(500);
      digitalWrite(PIN_GREEN_RGB, HIGH);
      digitalWrite(PIN_RED_RGB, LOW);
      digitalWrite(PIN_BLUE_RGB, LOW);
      //COMEÇA PANCADA

      return true;
    }
    else{
		button_state = 0;
      digitalWrite(PIN_RED_RGB, HIGH);
      digitalWrite(PIN_BLUE_RGB, LOW);
      digitalWrite(PIN_RED_RGB, LOW);

      //later: desligar motores
        
      return false;
    }
  }
  else {
    if(button_state == 1)
      return true;
    else
      return false;
  }
}
 


void SystemControl::init(){

	delay(50);

	controller.add(&threadColorSensors);
  controller.add(&threadInfraSensor);

  button_state = 0;

}


void threadInfraSensor_run(){

  int infraDistance = analogRead(PIN_IR_SENSOR);

}



void threadColorSensors_run(){
  
  int bright_read = analogRead(PIN_REFL_SENSOR1);
} 


int SystemControl::getColorSensors(){

  return analogRead(PIN_REFL_SENSOR1);
        
}