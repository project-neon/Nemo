#include "systemcontrol.h"
#include "_config.h"
#include "motors.h"


ThreadController controller;


int SystemControl::bright_read1;
int SystemControl::bright_read2;
int SystemControl::button_state;
int SystemControl::infra_distance;
int SystemControl::firstReading1;
int SystemControl::firstReading2;

bool SystemControl::white;
bool SystemControl::snek = true;
bool SystemControl::leftWhite = false;
bool SystemControl::rightWhite = false;





//declaração das threads
void threadColorSensors_run();
Thread threadColorSensors(threadColorSensors_run, 50);

void threadInfraSensor_run();
Thread threadInfraSensor(threadInfraSensor_run, 25);

void threadSnekPattern_run();
Thread threadSnekPattern(threadSnekPattern_run, 1050);


//callback das threads


void threadInfraSensor_run(){
  SystemControl::infra_distance = analogRead(PIN_IR_SENSOR);
}

void threadColorSensors_run(){

 SystemControl::bright_read1 = analogRead(PIN_REFL_SENSOR1);
 SystemControl::bright_read2 = analogRead(PIN_REFL_SENSOR2);

 if(SystemControl::bright_read1 < SystemControl::firstReading1 || SystemControl::bright_read2 < SystemControl::firstReading2){
  SystemControl::white=0;
  }
  else{
    SystemControl::white=1;
  }


 if(SystemControl::bright_read1 < SystemControl::firstReading1){
    SystemControl::leftWhite=1;
  } 

else{
  SystemControl::leftWhite=0;
  }

 if(SystemControl::bright_read2 < SystemControl::firstReading2){
    SystemControl::rightWhite=1;
    SystemControl::snek=false;
  } 

else{
  SystemControl::rightWhite=0;
  }

}




void threadSnekPattern_run(){
  SystemControl::snek = !SystemControl::snek;
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
  controller.add(&threadSnekPattern);


}

//começa e inicia a lógica principal

bool SystemControl::buttonStartStop(bool button_press){
  
  if (button_press){  
    if (button_state == 0){
      digitalWrite(PIN_BLUE_RGB, HIGH);
      digitalWrite(PIN_RED_RGB, LOW);
      digitalWrite(PIN_GREEN_RGB, LOW);

      button_state++;
      
      delay(5000); //esperando a partida começar
      
      digitalWrite(PIN_GREEN_RGB, HIGH);
      digitalWrite(PIN_RED_RGB, LOW);
      digitalWrite(PIN_BLUE_RGB, LOW);

      firstReading1 = analogRead(PIN_REFL_SENSOR1) - 150;
      firstReading2 = analogRead(PIN_REFL_SENSOR2) - 150;
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