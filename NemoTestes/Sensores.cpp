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

  delay(2);
  //SENSOR 1
  pinMode(XSHUT1, INPUT);
  delay(2);
  Sensores::sensor1.init(true);
  delay(2);
  Sensores::sensor1.setAddress((uint8_t)0x21);

  //SENSOR 2
  delay(2);
  pinMode(XSHUT2, INPUT);
  delay(2);
  Sensores::sensor2.init(true);
  delay(2);
  Sensores::sensor2.setAddress((uint8_t)0x23);

  //SENSOR 3
  delay(2);
  pinMode(XSHUT3, INPUT);
  delay(2);
  Sensores::sensor3.init(true);
  delay(2);
  Sensores::sensor3.setAddress((uint8_t)0x25);

  //SENSOR 4
  delay(2);
  pinMode(XSHUT4, INPUT);
  delay(2);
  Sensores::sensor4.init(true);
  delay(2);
  Sensores::sensor4.setAddress((uint8_t)0x27);
  
  Sensores::sensor1.setTimeout(100);
  Sensores::sensor2.setTimeout(100);
  Sensores::sensor3.setTimeout(100);
  Sensores::sensor4.setTimeout(100);
}

int Sensores::get_valor(VL53L0X sensor){
  return sensor.readRangeSingleMillimeters();
}
