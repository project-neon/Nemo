
/*

This code is still RAW, a lot more has to be implemented and organized,
(getting each module a proper file and header, add more callbacks and etc)
we'll get to it!


*/ 
#include "_config.h"

#include "systemcontrol.h"
#include "motors.h"

//arduino calls below

int irdist;

void setup() {

	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_RED_RGB, OUTPUT);
	pinMode(PIN_GREEN_RGB, OUTPUT);
	pinMode(PIN_BLUE_RGB, OUTPUT);
	pinMode(PIN_REFL_SENSOR1, INPUT);
	pinMode(PIN_REFL_SENSOR2, INPUT);

	Motors::init();

	SystemControl::init();

	Serial.begin(9600);
}


void loop() {


	while(!SystemControl::buttonStartStop(digitalRead(PIN_BUTTON))){
		/*Serial.print("Infravermelho: ");
		Serial.println(analogRead(PIN_IR_SENSOR));
		*/
		Serial.print("Refletância 1: ");
		Serial.println(analogRead(PIN_REFL_SENSOR1));
		/*Serial.print("Refletância 2: ");
		Serial.println(analogRead(PIN_REFL_SENSOR2));
		*/
		delay(500);
		}


	while(SystemControl::buttonStartStop(digitalRead(PIN_BUTTON))) {
	

		//LOGICA DO ESQUEMA
		Serial.println("TA NA HORA DO PAU");

		controller.run();

		if(analogRead(PIN_REFL_SENSOR1) > 300){
			Serial.println("preto!");
		}
		else{
			Serial.println("sai da frente carai");
		}


	    Motors::move(1, 255, 1); //motor 1, full speed, left
	    Motors::move(2, 255, 1); //motor 2, full speed, left

		delay(1000); 		//go for 1 second
		Motors::stop(); 	//stop
		
		Motors::move(1, 128, 0); //motor 1, half speed, right
		Motors::move(2, 128, 0); //motor 2, half speed, right
		
		delay(1000);
		Motors::stop();
		delay(250);

	}
	delay(1000);
}