/*

O código está quase pronto. Comentários em português para maior legibilidade!


*/ 


#include "_config.h"
#include "systemcontrol.h"
#include "motors.h"

bool achou = false;




void turndegrees(float angulo) {
    if(angulo < 0){
        Motors::driveTank(95, -95);
      }
  
      else{
        Motors::driveTank(95, -95);
      }
  
      //Serial.println("beyblade");
      int i = 0;
      while(i<420 && analogRead(PIN_IR_SENSOR) < 120){
        i++;
        delay(1);
      }
  
    Motors::stop();
}


void setup() {

  Motors::init();

  SystemControl::init();


  attachInterrupt(SystemControl::white, Motors::stop, LOW);

  Serial.begin(9600);

}


void loop() {


  while(!SystemControl::buttonStartStop(digitalRead(PIN_BUTTON))){
    
    Motors::stop();  

    digitalWrite(PIN_RED_RGB, HIGH);
    digitalWrite(PIN_GREEN_RGB, LOW);
    digitalWrite(PIN_BLUE_RGB, LOW);
    

    /* debuggar sensores

    controller.run();

    Serial.print("Infravermelho: ");
    Serial.println(SystemControl::infra_distance);
    
    Serial.print("Refletância 1: ");
    Serial.println(SystemControl::bright_read);
    
    Serial.print("Refletância 2: ");
    Serial.println(analogRead(PIN_REFL_SENSOR2));
    

    delay(500); */
    
  }


  while(SystemControl::buttonStartStop(digitalRead(PIN_BUTTON))) {

    //LOGICA DO ESQUEMA
    //Serial.println("TA NA HORA DO PAU");

    controller.run();

    //debugging
    //Motors::stop();
    //delay(3000);
    //Serial.print(" Leitura: ");
    //Serial.println(SystemControl::bright_read1);
    //delay(300);

    if(!SystemControl::white){


      ///* smart comment uncomment!

      if(SystemControl::rightWhite && SystemControl::leftWhite){

        Motors::driveTank(-100, -100);
        delay(400);
        turndegrees(180);
      }
      else if(SystemControl::rightWhite){
        Motors::driveTank(-100, -100);
        delay(400);
        turndegrees(180);
      }

      else if(SystemControl::leftWhite){
        Motors::driveTank(-100, -100);
        delay(400);
        turndegrees(-180);

      }


      //debug!
      //Serial.println("preto");
      //Serial.println(SystemControl::bright_read1);
      //Serial.println(SystemControl::bright_read2);
      //delay(100);
      
      }

      else{
        
        ///*
        if(SystemControl::infra_distance > 225){
  
            //Serial.print("estou te vendo! Leitura: ");
            //Serial.println(SystemControl::infra_distance);
              
              //achou = true;
      
              Motors::driveTank(100, 100);
  

              while(SystemControl::white && !digitalRead(PIN_BUTTON)){ //lock-on
              controller.run();
              
              Motors::driveTank(100, 100);
  
              }
          }

        else{ 
          

            /* 
            
            Motors::driveTank(80,-80);

            */
            //search
            achou = false;
            if (SystemControl::snek){
               Motors::driveTank(90,45);
            }
            else {
               Motors::driveTank(45,90);
            }

            //*/
            //Serial.print("estou CEGO! Leitura: ");
            //Serial.println(SystemControl::infra_distance);

          } 
      //*/ such smart comment-uncomment!
    }   

  }
  
  //esse é o fim da lógica principal, e o programa volta à esperar o input do botão...
  //o Motors:stop() chamado aqui não desliga os motores
  Motors::stop();
  delay(1000);
  delay(1);
  Motors::stop();


}