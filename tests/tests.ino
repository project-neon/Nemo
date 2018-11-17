#include "_config.h"

#include "motors.h"
#include "systemcontrol.h"





void setup() {


  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_RED_RGB, OUTPUT);
  pinMode(PIN_GREEN_RGB, OUTPUT);
  pinMode(PIN_BLUE_RGB, OUTPUT);


  SystemControl::init();
  Motors::init();
  

  Serial.begin(9600);
}

void loop(){
        
        SystemControl::buttonStartStop(false);
        while(digitalRead(4);)

        controller.run();
        Serial.println(SystemControl::bright_read);

        if(SystemControl::bright_read > 300){ //possibly && !pushing ?

          //you're in the dohyo! do something!
          Serial.println("preto");
          Motors::move(1, 120, 1);
          Motors::move(2, 120, 1);
          //Behaviour::AttackMode(); //when it's done...

        }
        else{
          
          //it's white, turn around!
          Serial.println("branco!");
          Motors::move(1, 120, 0);
          Motors::move(2, 120, 0);
          //Behaviour::RetreatMode(); //when it's done...
        }

}
