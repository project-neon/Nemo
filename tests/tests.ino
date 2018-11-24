/*

O código está quase pronto. Comentários em português para maior legibilidade!


*/ 

#include "_config.h"
#include "systemcontrol.h"
#include "motors.h"

bool achou = false;


void turn180degrees() {

  Motors::driveTank(95, -95);

  //Serial.println("beyblade");

  delay(420);

  Motors::stop();

}


void turn90degrees() {

  Motors::driveTank(75, -75);

  //Serial.println("beyblade");

  delay(220);

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
    //turn180degrees();
    //Motors::stop();
    //delay(3000);
    
    if(!SystemControl::white){
      //Serial.println("branco!");
      //Serial.println(SystemControl::bright_read1);
      //Serial.println(SystemControl::bright_read2);

      
      Motors::driveTank(-100, -100);
     
      delay(200);

      //Serial.println(SystemControl::bright_read2);
      //Serial.println(SystemControl::bright_read1);

      turn180degrees();

      //Motors::move(1, 120, 1);
      //Motors::move(2, 120, 1);


      //debug!
      //Serial.println("preto");
      //Serial.println(SystemControl::bright_read1);
      //Serial.println(SystemControl::bright_read2);
      //delay(100);
      }
      else{
        if(SystemControl::infra_distance > 200)
        {
  
            //Serial.print("estou te vendo! Leitura: ");
            //Serial.println(SystemControl::infra_distance);
              
              //achou = true;
      
              Motors::driveTank(100, 100);
  

              while(SystemControl::infra_distance > 200 && SystemControl::white){
              controller.run();
              
              Motors::driveTank(100, 100);
  
              }
          }

        else if(SystemControl::white){ 
  
            //search
            achou = false;
            if (SystemControl::snek){
               Motors::driveTank(100,60);
            }
            else {
               Motors::driveTank(60,100);

            }
            //Serial.print("estou CEGO! Leitura: ");
            //Serial.println(SystemControl::infra_distance);
 

          } 

      }

    }   
    //*/


    /* MOTORS DEBUG

      Motors::move(1, 80, 1); //motor 1, 80 para testes
      Motors::move(2, 80, 1); //motor 2, 80 para testes
      LOG("First");
    delay(1000);
    

    Motors::stop();

    delay(2000); 

    LOG("Second");
    Motors::move(1, 80, 0);
    Motors::move(2, 80, 0);

    delay(1000);

    Motors::stop();
  
    delay(2000) 
    */

  
  
  //esse é o fim da lógica principal, e o programa volta à esperar o input do botão...
  //o Motors:stop() chamado aqui não desliga os motores
  Motors::stop();
  delay(1000);
  delay(1);
  Motors::stop();

}
