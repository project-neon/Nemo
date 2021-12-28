#include "_config.h"
#include <VL53L0X.h>

#ifndef SENSORES_H
#define SENSORES_H

class Sensores{
public:
	static VL53L0X sensor1;
	static VL53L0X sensor2;
  static VL53L0X sensor3;
  static VL53L0X sensor4;

	static void init();

	static int get_valor(VL53L0X sensor);

};

#endif
