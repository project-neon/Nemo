/*#define PIN_BUTTON 4 
#define STBY 2
//Motor A
#define PWMA 6 //Speed control
#define AIN1 10 //Direction
#define AIN2 11 //Direction

//Motor B
#define PWMB 5 //Speed control
#define BIN1 13 //Direction
#define BIN2 12 //Direction

#define PIN_RED_RGB 8
#define PIN_GREEN_RGB 3
#define PIN_BLUE_RGB 9
void setup() {

	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(3, OUTPUT);
	Serial.begin(9600);
}

void loop{
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, 120);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
        analogWrite(PWMB, 120);
}*/
