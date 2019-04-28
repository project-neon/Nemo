/*#include "Motors.h"
#include "Sensores.h"
void setup(){
	Sensores::init();
	Serial.begin(9600);
	pinMode(Led_vermelho,OUTPUT);
}

void loop(){
	Sensores::update();
	for(int i = 0; i<4 ; i++){
		Serial.print("Sensor:");
		Serial.println(i);
		Serial.println(analogRead(i));
	}
	digitalWrite(Led_vermelho,HIGH);
	delay(1000);
		digitalWrite(Led_vermelho,LOW);
		delay(1000);

}*/