#include "systemcontrol.h"
#include "_config.h"
#include "motors.h"


ThreadController controller;

 

int SystemControl::bright_read;
int SystemControl::button_state;
int SystemControl::infra_distance;

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
      Motors::stop();
  }
}

void SystemControl::init() {
  delay(50);

  controller.add(&threadColorSensors);
  controller.add(&threadInfraSensor);

}


void threadInfraSensor_run(){

  SystemControl::infra_distance = analogRead(PIN_IR_SENSOR);

}

void threadColorSensors_run(){
  
 SystemControl::bright_read = analogRead(PIN_REFL_SENSOR1);
} 


int SystemControl::getColorSensors(){

  return analogRead(PIN_REFL_SENSOR1);
        
}