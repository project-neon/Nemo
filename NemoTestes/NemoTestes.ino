#include <IRremote.h>
#include "_config.h"
#include "motors.h"
#include "Sensores.h"
#include <VL53L0X.h>
#include <stdlib.h>

float armazena_valor = 0;

IRrecv irrecv(RECV_PIN);  
decode_results results;

void setup() {
  // put your setup code here, to run once:

  irrecv.enableIRIn(); //inicia o receptor
}

void loop() {
  // put your main code here, to run repeatedly:

}
