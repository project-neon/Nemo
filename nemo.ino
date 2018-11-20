//Motor A
#define PWMA 5 //Speed control
#define AIN1 10	 //Direction
#define AIN2 11 //Direction

//Motor B
#define PWMB 3 //Speed control
#define BIN1 A3 //Direction
#define BIN2 A2 //Direction

//all the rest
#define STBY 2

#define PIN_BUTTON 4

#define PIN_RED_RGB 8
#define PIN_GREEN_RGB 7
#define PIN_BLUE_RGB 9

#define PIN_REFL_SENSOR A0 







void buttonStartStop(bool tipo){
		if (tipo == false){
			digitalWrite(8, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(3, LOW); //desligar motores
			
		}
		else{
			digitalWrite(3, HIGH);
			digitalWrite(8, LOW);
			digitalWrite(9, LOW);
		//COMEÇA PANCADA
		}
	}


void setup() {
	pinMode(PIN_BUTTON, INPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(3, OUTPUT);
	Serial.begin(9600);

}


void loop() {
	buttonStartStop(false);
	while(!digitalRead(PIN_BUTTON)) {
	Serial.println(digitalRead(PIN_BUTTON));
	 }
	buttonStartStop(true);
	while(1) {
		Serial.println("nada!");
	 }

}
