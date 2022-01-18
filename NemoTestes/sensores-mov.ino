#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor, sensor2;

#define XSHUT1 A0
#define XSHUT2 A1

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, INPUT);


  digitalWrite(XSHUT1, LOW);
  delay(2);

  sensor2.setAddress(0x32);


  pinMode(XSHUT1, INPUT);

  sensor.init();
  sensor2.init();
  sensor.setTimeout(500);
  sensor2.setTimeout(500);
}

void loop()
{

  int dist1 = sensor.readRangeSingleMillimeters();
  int dist2 = sensor2.readRangeSingleMillimeters();
 
  Serial.print(dist1);
  Serial.print(" - ");
  Serial.println(dist2);
}
