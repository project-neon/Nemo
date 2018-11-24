#include "systemcontrol.h"
#include "_config.h"
#include "motors.h"


ThreadController controller;


int SystemControl::bright_read1;
int SystemControl::bright_read2;
int SystemControl::button_state;
int SystemControl::infra_distance;

//declaração das threads
void threadColorSensors_run();
Thread threadColorSensors(threadColorSensors_run, 50);

void threadInfraSensor_run();
Thread threadInfraSensor(threadInfraSensor_run, 50);

//callback das threads
void threadInfraSensor_run(){
  SystemControl::infra_distance = analogRead(PIN_IR_SENSOR);

}

void threadColorSensors_run(){
 SystemControl::bright_read1 = analogRead(PIN_REFL_SENSOR1);
 SystemControl::bright_read2 = analogRead(PIN_REFL_SENSOR2);
} 


//
void SystemControl::init() {

  pinMode(PIN_BUTTON, INPUT);

  pinMode(PIN_RED_RGB, OUTPUT);
  pinMode(PIN_GREEN_RGB, OUTPUT);
  pinMode(PIN_BLUE_RGB, OUTPUT);
  
  pinMode(PIN_REFL_SENSOR1, INPUT);
  pinMode(PIN_REFL_SENSOR2, INPUT);


  controller.add(&threadColorSensors);
  controller.add(&threadInfraSensor);

}

//começa e inicia a lógica principal

bool SystemControl::buttonStartStop(bool button_press){
  if (button_press){  
    if (button_state == 0){
      digitalWrite(PIN_BLUE_RGB, HIGH);
      digitalWrite(PIN_RED_RGB, LOW);
      digitalWrite(PIN_GREEN_RGB, LOW);

      button_state++;
      
      delay(2000); //esperando a partida começar
      
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

      Motors::stop();
        
      return false;
    }
  }
  else {
    if(button_state == 1)
      return true;
    else{
      Motors::stop();
      return false;
    }
  }
}



int SystemControl::getColorSensors(){
  return analogRead(PIN_REFL_SENSOR1);
}