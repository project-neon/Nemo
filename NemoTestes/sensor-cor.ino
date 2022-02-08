#define LED1 = 9;
#define LED2 = 10;    
#define sensor1 = A6;  
#define sensor2 = A7;

int cal = 150;

void setup(){
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(sensor1,INPUT);
    pinMode(sensor2,INPUT);
      
    digitalWrite(LED1,LOW); 
    digitalWrite(LED2,LOW); 

}

void loop() {

    int estado1 = digitalRead(sensor1); 
    int estado2 = digitalRead(sensor2);

    if (estado1 < cal) 
    {
        digitalWrite(LED1,HIGH); 
    } 
     else
     {
        digitalWrite(LED1,LOW); 
      }

    if (estado2 < cal) 
    {    
        digitalWrite(LED2,HIGH);
    }
    else
     {
        digitalWrite(LED2,LOW); 
      } 

}
