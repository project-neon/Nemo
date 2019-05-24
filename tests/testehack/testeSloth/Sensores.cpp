#include <Thread.h>
#include <ThreadController.h>

#include "Sensores.h"

ThreadController controller;

	int Sensores::Norte_min;
	int Sensores::Norte_max;
 	int Sensores::Oeste_min; 
	int Sensores::Oeste_max;
	int Sensores::Sul_min;
	int Sensores::Sul_max;
	int Sensores::Leste_min;
	int Sensores::Leste_max;
	int Sensores::values[4];
// [0]NORTE [1]OESTE [2]SUL [3]LESTE
  int Sensores::valor_preto;
	bool Sensores::white =true;
	bool Sensores::direcao;


//declaração das threads
void Sensores::threadColorSensors_run();
Thread threadColorSensors(Sensores::threadColorSensors_run, 50);

void Sensores::update();
Thread threadInfraSensor(Sensores::update, 25);

void Sensores::threadColorSensors_run(){
	if(analogRead(A6) < Sensores::valor_preto ){
		Sensores::white=0;
		//digitalRead(SRT) ? Sensores::direcao = true : Sensores::direcao = false;		
    Sensores::direcao = true;
	}
	else{
	  Sensores::white=1;
	}
}



void Sensores::init(){

	controller.add(&threadColorSensors);
  controller.add(&threadInfraSensor);
	
	pinMode(SRF, INPUT);
  pinMode(SRT, INPUT);


	pinMode(GPIO_sensores, OUTPUT);
	digitalWrite(GPIO_sensores,HIGH);
	pinMode(SensorNorte, INPUT);
	pinMode(SensorOeste, INPUT);
	pinMode(SensorSul, INPUT);
	pinMode(SensorLeste, INPUT);
	Sensores::Norte_min = EEPROM.read(0);
	Sensores::Norte_max = EEPROM.read(1); 
 	Sensores::Oeste_min = EEPROM.read(2); 
	Sensores::Oeste_max = EEPROM.read(3); 
	Sensores::Sul_min = EEPROM.read(4); 
	Sensores::Sul_max = EEPROM.read(5); 
	Sensores::Leste_min = EEPROM.read(6); 
	Sensores::Leste_max = EEPROM.read(7);
}

boolean Sensores::visao(){ // Uma função que retorna false se o robô não viu alguma coisa em qualquer um dos sensores
// Uma função que retorna true se o robô viu alguma coisa em qualquer um dos sensores
if(Sensores::values[0] != -1 || Sensores::values[1] != -1 || Sensores::values[3] != -1)
  return false;
  else return true;
}
void Sensores::update(){
	
//Valor_min aproximadamente 110
//Valos_max aproximadamente 20
	int valorNorte = analogRead(SensorNorte)/4;

		if(valorNorte<=Sensores::Norte_min && valorNorte>=Sensores::Norte_max)
		{
			//Serial.print("O valor de norte é");
			//Serial.println(valorNorte);
			Sensores::values[0]	= map(valorNorte,Sensores::Norte_max,Sensores::Norte_min,4,40);
		}
		else
		{
			Sensores::values[0] = -1;
		}
	int valorOeste = analogRead(SensorOeste)/4;
		if(valorOeste<=Sensores::Oeste_min && valorOeste>=Sensores::Oeste_max)
		{
			//Serial.print("O valor de oeste é");
			//Serial.println(valorOeste);
			Sensores::values[1] = map(valorOeste,Sensores::Oeste_min,Sensores::Oeste_max,40,4);
		}
		else
		{
			Sensores::values[1] = -1;
		}
	int valorSul = analogRead(SensorSul)/4;
		if(valorSul<=Sensores::Sul_min && valorSul>=Sensores::Sul_max)
		{
			Sensores::values[2] = map(valorSul,Sensores::Sul_min,Sensores::Sul_max,40,4);
		}
		else
		{
			Sensores::values[2] = -1;
		}
	int valorLeste = analogRead(SensorLeste)/4;
		if(valorLeste<=Sensores::Leste_min && valorLeste>=Sensores::Leste_max)
		{
			Sensores::values[3] = map(valorLeste,Sensores::Leste_min,Sensores::Leste_max,40,4);
		}
		else
		{
			Sensores::values[3] = -1;
		}
	
}
