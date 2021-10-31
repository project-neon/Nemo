#include <Wire.h>
#include <VL53L0X.h>
#include "_config.h"

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
    sensor2.setAddress(0x27);
    
    pinMode(SHUT_1, INPUT);
 
    sensor.init();
    sensor2.init();
    sensor.setTimeout(600);
    sensor2.setTimeout(600);
    
    //Talvez seja melhor iniciar as variáveis distance0 e distance1 aqui para elas não
    //ficarem sendo iniciadas toda a vez no loop
    
    //Esse próximo seria só uma recomendação, talvez trocar os nomes por:
    //distance0 --> distance1
    //distance1 --> distance2
    //Para ficar mais parecido ao sensor e sensor2
    //Embora talvez seja uma boa mudar também o "sensor" para
    //sensor --> sensor1
}

void loop()
{

    int distance0 = sensor.readRangeSingleMillimeters();
    int distance1 = sensor2.readRangeSingleMillimeters();
 
    Serial.print(distance0);
    Serial.print(" - ");
    Serial.println(distance1);
}
