#include <VL53L0X.h>
#include "Sensores.h"
#include "_config.h"
#include <Wire.h>
VL53L0X Sensores::sensor1;
VL53L0X Sensores::sensor2;
VL53L0X Sensores::sensor3;
VL53L0X Sensores::sensor4;

void Sensores::init(){
  Wire.begin();
  Serial.println("Wire");
  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);
  pinMode(XSHUT3, OUTPUT);
  pinMode(XSHUT4, OUTPUT);
  

  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  digitalWrite(XSHUT3, LOW);
  digitalWrite(XSHUT4, LOW);
  Serial.println("XSHUT LOW");

  delay(10);
  //SENSOR 1
  pinMode(XSHUT1, INPUT);
  Serial.println("XSHUT 1 INPUT");
  delay(50);
  Sensores::sensor1.init(true);
  Serial.println("sensor 1 init");
  delay(20);
  Sensores::sensor1.setAddress((uint8_t)0x21);
  Serial.println("sensor 1 endereçado");

  //SENSOR 2
  pinMode(XSHUT2, INPUT);
  Serial.println("XSHUT 2 INPUT");
  delay(50);
  Sensores::sensor2.init(true);
  Serial.println("sensor 2 init");
  delay(20);
  Sensores::sensor2.setAddress((uint8_t)0x23);
  Serial.println("sensor 2 endereçado");

  //SENSOR 3
  pinMode(XSHUT3, INPUT);
  Serial.println("XSHUT 3 INPUT");
  delay(50);
  Sensores::sensor3.init(true);
  Serial.println("sensor 3 init");
  delay(20);
  Sensores::sensor3.setAddress((uint8_t)0x25);
  Serial.println("sensor 3 endereçado");

  //SENSOR 4
  pinMode(XSHUT4, INPUT);
  Serial.println("XSHUT 4 INPUT");
  delay(50);
  Sensores::sensor4.init(true);
  Serial.println("sensor 4 init");
  delay(20);
  Sensores::sensor4.setAddress((uint8_t)0x27);
  Serial.println("sensor 4 endereçado");
  
  Sensores::sensor1.setTimeout(100);
  Sensores::sensor2.setTimeout(100);
  Sensores::sensor3.setTimeout(100);
  Sensores::sensor4.setTimeout(100);

  Serial.println("Sensores de distância OK");
}

int Sensores::get_valor(VL53L0X sensor){
  return sensor.readRangeSingleMillimeters();
}
