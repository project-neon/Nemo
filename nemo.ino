#define PIN_BUTTON 4 

#define PIN_RED_RGB 8
#define PIN_GREEN_RGB 3
#define PIN_BLUE_RGB 9

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
