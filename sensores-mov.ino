#include <Wire.h>
#include <VL53L0X.h>
#include <config.h>

VL53L0X sensor, sensor2;

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
    sensor.setAddress(0x25);

    digitalWrite(SHUT_2, HIGH)
    sensor.setAddress(0x27);
    
    pinMode(SHUT_1, INPUT);
 
    sensor.init();
    sensor2.init();
    sensor.setTimeout(600);
    sensor2.setTimeout(600);
}

void loop()
{

    int distance0 = sensor.readRangeSingleMillimeters();
    int distance1 = sensor2.readRangeSingleMillimeters();
 
    Serial.print(distance0);
    Serial.print(" - ");
    Serial.println(distance1);
}
