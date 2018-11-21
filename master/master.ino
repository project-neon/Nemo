/*

O código está quase pronto. Comentários em português para maior legibilidade!


*/ 

#include "_config.h"

#include "systemcontrol.h"
#include "motors.h"


void setup() {

	Motors::init();

	SystemControl::init();

	
	Serial.begin(9600);
}


void loop() {


	while(!SystemControl::buttonStartStop(digitalRead(PIN_BUTTON))){
		
		Motors::stop();  /*sendo sincero, eu não sei se isto deveria estar aqui, visto que
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

		if(SystemControl::bright_read > 300){
			Serial.println("preto!");
		}
		else{
			Serial.println("sai da frente carai");
		}

		if(SystemControl::infra_distance > 450){
			Serial.print("Infravermelho: ");
			Serial.println(SystemControl::infra_distance);

		}


	    Motors::move(1, 80, 1); //motor 1, 80 para testes
	    Motors::move(2, 80, 1); //motor 2, 80 para testes

		delay(250);

	}
	
	//esse é o fim da lógica principal, e o programa volta à esperar o input do botão...
	//o Motors:stop() chamado aqui não desliga os motores
	Motors::stop();
	delay(1000);
	delay(1);
	Motors::stop();

}