
#include "systemcontrol.h"
#include "_config.h"
#include "motors.h"


ThreadController controller;

int SystemControl::bright_read;

int SystemControl::button_state; 

bool SystemControl::begun = false;



 
void threadColorSensors_run();
Thread threadColorSensors(threadColorSensors_run, 500);

void threadButtonCheck_run();
Thread threadButton(threadButtonCheck_run, 1000);


void SystemControl::init(){

  Serial.begin(9600);
  delay(50);

  controller.add(&threadColorSensors);
  controller.add(&threadButton);


}


void threadColorSensors_run(){

      SystemControl::bright_read = analogRead(PIN_REFL_SENSOR);
}


void threadButtonCheck_run(){

  SystemControl::button_state = digitalRead(PIN_BUTTON);

}


void SystemControl::buttonStartStop(int butt_state){
    if (butt_state == LOW && begun == false){ //due to pull-down
      //standby
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(3, LOW);

      
    }
    else if (butt_state == HIGH && begun == false){
      begun = true;
      //match begun
      digitalWrite(9, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(3, LOW);
      
      delay(500);
      digitalWrite(3, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    //COMEÇA PANCADA
    }

    else if (butt_state == HIGH && begun == true){
      begun = false; 

      Serial.println("PARA TUDO");

      Motors::stop();
    }
  }
