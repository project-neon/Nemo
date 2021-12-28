#include "_config.h"

#ifndef MOTORS_H
#define MOTORS_H


class Motors{
public:

  //Inicializa os pinos
  static void init();

  //Executa o teste dos motores
  static void driveTeste(float m1, float m2);

  //Desliga os motores
  static void stop();
};

#endif
