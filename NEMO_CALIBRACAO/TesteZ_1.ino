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
	if(Sensores::values[0]!=-1){
		Motors::driveTank(45,45);
	}
	else{
		Motors::stop();
	}
	delay(1000);
}