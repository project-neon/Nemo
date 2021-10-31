#include <Wire.h>
#include <VL53L0X.h>
#include "_config.h"

VL53L0X sensor1, sensor2;

/*#define SHUT_1 0
#define SHUT_2 1
#define SHUT_3 2
#define SHUT_4 3*/

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    pinMode(SHUT_1, OUTPUT);
    pinMode(SHUT_2, OUTPUT);

    digitalWrite(SHUT_1, LOW);
    digitalWrite(SHUT_2, LOW);

    delay(10);

    digitalWrite(SHUT_1, HIGH)
    sensor1.setAddress(0x25);

    digitalWrite(SHUT_2, HIGH)
    sensor2.setAddress(0x27);
    
    pinMode(SHUT_1, INPUT);
 
    sensor1.init();
    sensor2.init();
    sensor1.setTimeout(600);
    sensor2.setTimeout(600);
    
    int distance1 = sensor1.readRangeSingleMillimeters();
    int distance2 = sensor2.readRangeSingleMillimeters();
    
}

void loop()
{

    Serial.print(distance1);
    Serial.print(" - ");
    Serial.println(distance2);
}
