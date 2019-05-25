#ifndef SENSORES_H
#define SENSORES_H
#include "_config.h"
#include <Thread.h>
#include <ThreadController.h>
#include <EEPROM.h>

extern ThreadController controller; 

class Sensores{
public:
  static int valor_preto_tras;
  static int valor_preto_frente;
	static int values[4];
	static int Norte_min;
	static int Norte_max;
	static int Oeste_min;
	static int Oeste_max;
	static int Sul_min;
	static int Sul_max;
	static int Leste_min;
	static int Leste_max;
	
 	static bool white;
	static bool direcao;

//inicializa os sensores, ligando-os e puxando os valores de
//calibração da EEPROM
	static void init();
	//Armazena valores de 4 a 20 no array de values[Norte,Oeste,Sul,Leste]
	//Se o valor estiver fora do valor esperado o valor armazenado é NULL
	static void update();
	static boolean visao();
  static void threadColorSensors_run();
};
#endif
