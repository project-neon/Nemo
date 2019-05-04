#include "Motors.h"
#include "Sensores.h"
void setup(){
	Sensores::init();
	Motors::init();
	Serial.begin(9600);
}
void loop(){
	Sensores::update();
	//Serial.println(Sensores::values[0]);
	//FRENTE
	if(Sensores::values[0]!=-1){
		Motors::driveTank(45,45);
	}
	//DIREITA
	else if(Sensores::values[1]!=-1){
		while(Sensores::values[0]==-1){
		Motors::driveTank(-45,45);
		Sensores::update();
		}	
	}
	//ESQUERDA
	else if(Sensores::values[3]!=-1){
		while(Sensores::values[0]==-1){
		Motors::driveTank(45,-45);
		Sensores::update();
		}
	}
	//TRASEIRA
	else if(Sensores::values[2]!=-1){
		while(Sensores::values[0]==-1){
		Motors::driveTank(-45,-45);
		Sensores::update();
		}
	}
	else{
		Motors::stop();
	}
	delay(1000);
}