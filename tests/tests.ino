/*


//Motor A
#define PWMA 6 //Speed control
#define AIN1 10 //Direction
#define AIN2 11 //Direction

//Motor B
#define PWMB 5 //Speed control
#define BIN1 13 //Direction
#define BIN2 12 //Direction

#define STBY 2

#define PIN_BUTTON 4 

#define PIN_RED_RGB 8
#define PIN_GREEN_RGB 3
#define PIN_BLUE_RGB 9

void setup() {

  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop(){
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, 120);
}*/
