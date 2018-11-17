
/*

This code is still RAW, a lot more has to be implemented and organized,
(getting each module a proper file and header, add more callbacks and etc)
we'll get to it!


*/ 
#include "_config.h"

#include "systemcontrol.h"
#include "motors.h"




//startup function




//this is the "second" main loop, which begins after the buttons have been pressed
void inicia(){
	while(1) {

	Serial.println("Tamo no inicia");
    Motors::move(1, 255, 1); //motor 1, full speed, left
    Motors::move(2, 255, 1); //motor 2, full speed, left

	delay(1000); //go for 1 second
	Motors::stop(); 	//stop
	
	Motors::move(1, 128, 0); //motor 1, half speed, right
	Motors::move(2, 128, 0); //motor 2, half speed, right
	
	delay(1000);
	Motors::stop();
	delay(250);


	controller.run();



	 }
}

//arduino calls below

void setup() {

	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_RED_RGB, OUTPUT);
	pinMode(PIN_GREEN_RGB, OUTPUT);
	pinMode(PIN_BLUE_RGB, OUTPUT);


	Motors::init();

	SystemControl::init();

	Serial.begin(9600);

}


void loop() {


	SystemControl::buttonStartStop(false);
	while(!digitalRead(PIN_BUTTON)) {
	Serial.println(!digitalRead(PIN_BUTTON));
	}

  	Serial.println("EH ELE QUE NOIZ QUE");
    Serial.println(digitalRead(PIN_BUTTON));

	SystemControl::buttonStartStop(true);
	inicia();

}