#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor, sensor2;

#define SHUT_1 0
#define SHUT_2 1
#define SHUT_3 2
#define SHUT_4 3

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    pinMode(SHUT_1, OUTPUT);
    pinMode(SHUT_2, OUTPUT;

    digitalWrite(SHUT_1, LOW);
    digitalWrite(SHUT_2, LOW);

    delay(10);

    digitalWrite(SHUT_1, HIGH)
    

    sensor2.setAddress(0x32);

    
    pinMode(SHUT_1, INPUT);
  // É possível alterar o endereço do sensor 1 apenas com o código abaixo
  // Como o sensor 2 já está com endereço diferente, não é necessário desligá-lo,
  // pois ele não interferirá na comunicação
  //sensor.setAdress(0x31);
 
  // Inicializa sensores
  sensor.init();
  sensor2.init();
  sensor.setTimeout(500);
  sensor2.setTimeout(500);
}

void loop()
{
  // Mede a distância dos dois sensores
  int dist1 = sensor.readRangeSingleMillimeters();
  int dist2 = sensor2.readRangeSingleMillimeters();
 
  Serial.print(dist1);
  Serial.print(" - ");
  Serial.println(dist2);
}