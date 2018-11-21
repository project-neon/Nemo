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



  
      digitalWrite(PIN_RED_RGB, HIGH);
      digitalWrite(PIN_GREEN_RGB, LOW);
      digitalWrite(PIN_BLUE_RGB, LOW);

      Motors::move(1, 100, 0);
      Motors::move(2, 100, 0);


      delay(1000);

    
      Serial.println("hello estou debbugando");
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, LOW);


      delay(1000);

      Motors::stop();


      delay(5000);

        /*controller.run();
        
        Serial.println(SystemControl::button_state);

        SystemControl::buttonStartStop(SystemControl::button_state);


        Serial.println(SystemControl::begun);





        /*SystemControl::buttonStartStop(SystemControl::button_state);

        while(SystemControl::button_state == LOW){
          Serial.println(SystemControl::button_state);
          delay(2000);
        }


        
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
        }*/

}
