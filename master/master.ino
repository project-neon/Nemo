/*

O código está quase pronto. Comentários em português para maior legibilidade!

*/ 

#include "_config.h"
#include "systemcontrol.h"
#include "motors.h"

bool achou = false;


void turn180degrees() {

	Motors::move(1, 80, 1); 
	Motors::move(0, 80, 0);

	Serial.println("beyblade");


	Motors::stop();
	delay(2000);
}


void setup() {

	Motors::init();

	SystemControl::init();

	Serial.begin(9600);

}


void loop() {


	while(!SystemControl::buttonStartStop(digitalRead(PIN_BUTTON))){
		
		Motors::stop();  
							/*sendo sincero, eu não sei se isto deveria estar aqui, visto que
						   chamar isto sempre dentro do while talvez não seja tão eficiente...
						   porém, os motores não desligavam após pressionar o butão novamente, ;d */

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
		///*
		if(SystemControl::bright_read1 > 400 && SystemControl::bright_read2 > 400){
			
			//Motors::move(1, 120, 1);
			//Motors::move(2, 120, 1);


			//debug!
			Serial.println("preto");
			Serial.println(SystemControl::bright_read1);
			Serial.println(SystemControl::bright_read2);
			delay(100);

			/*if(SystemControl::infra_distance > 200){

				Serial.print("estou te vendo! Leitura: ");
				Serial.println(SystemControl::infra_distance);
				
				achou = true;
	
				Motors::move(1, 80, 1);
				Motors::move(2, 80, 1);

			while(SystemControl::infra_distance > 200 && achou == true){
				controller.run();

				Motors::move(1, 80, 1);
				Motors::move(2, 80, 1);

				}

			}

			
			else{ 

				//search
				achou = false;
				Serial.print("estou CEGO! Leitura: ");
				Serial.println(SystemControl::infra_distance);
				Motors::move(1, 80, 1);
				Motors::move(2, 80, 0);
			} 

			*/
		}
		
		else if(SystemControl::bright_read1 < 400 || SystemControl::bright_read2 < 400){

			Serial.println("branco!");
			Serial.println(SystemControl::bright_read1);
			Serial.println(SystemControl::bright_read2);

			/*
			Motors::move(1, 80, 0);
			Motors::move(2, 80, 0);
			
			Serial.println(SystemControl::bright_read2);
			Serial.println(SystemControl::bright_read1);

			turn180degrees();
		*/
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

	}
	
	//esse é o fim da lógica principal, e o programa volta à esperar o input do botão...
	//o Motors:stop() chamado aqui não desliga os motores
	Motors::stop();
	delay(1000);
	delay(1);
	Motors::stop();

}