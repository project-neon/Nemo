
/*

This code is still RAW, a lot more has to be implemented and organized,
(getting each module a proper file and header, add more callbacks and etc)
we'll get to it!

*/



//Motor A
#define PWMA 6  //Speed control
#define AIN1 10 //Direction
#define AIN2 11 //Direction

//Motor B
#define PWMB 5  //Speed control
#define BIN1 13 //Direction
#define BIN2 12 //Direction

//all the rest
#define STBY 2

#define PIN_BUTTON 4

#define PIN_RED_RGB 8
#define PIN_GREEN_RGB 3
#define PIN_BLUE_RGB 9


//startup function

void buttonStartStop(bool tipo){
		if (tipo == false){
			digitalWrite(8, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(3, LOW); 
			//later: desligar motores
      
			
		}
		else{
			digitalWrite(3, HIGH);
			digitalWrite(8, LOW);
			digitalWrite(9, LOW);
		//COMEÇA PANCADA
		}
	}
 

//some action/debugging functions below

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

	Serial.println("Ligou o torretoni");
	digitalWrite(STBY, HIGH); //disable standby

	bool inPin1 = LOW;
	bool inPin2 = HIGH;

	if(direction == 1){
		inPin1 = HIGH;
		inPin2 = LOW;
	}

	if(motor == 1){
	digitalWrite(AIN1, inPin1);
	digitalWrite(AIN2, inPin2);
	analogWrite(PWMA, speed);
	}
	else{
	digitalWrite(BIN1, inPin1);
	digitalWrite(BIN2, inPin2);
	analogWrite(PWMB, speed);
	}
}

void stop(){
//enable standby
	digitalWrite(STBY, LOW);
}


//this is the "second" main loop, which begins after the buttons have been pressed
void inicia(){
	while(1) {
		Serial.println("Tamo no inicia");
    move(1, 255, 1); //motor 1, full speed, left
    move(2, 255, 1); //motor 2, full speed, left

delay(1000); //go for 1 second
stop(); 	//stop
delay(250); //hold for 250ms until move again

move(1, 128, 0); //motor 1, half speed, right
move(2, 128, 0); //motor 2, half speed, right

delay(1000);
stop();
delay(250);

	 }
}

//arduino calls below

void setup() {

	pinMode(STBY, OUTPUT);

	pinMode(PWMA, OUTPUT);
	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	
	pinMode(PWMB, OUTPUT);
	pinMode(BIN1, OUTPUT);
	pinMode(BIN2, OUTPUT);

	pinMode(PIN_BUTTON, INPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(3, OUTPUT);
	Serial.begin(9600);

}


void loop() {
	buttonStartStop(false);
	while(!digitalRead(PIN_BUTTON)) {
	Serial.println(!digitalRead(PIN_BUTTON));
	 }
   Serial.println("EH ELE QUE NOIZ QUE");
    Serial.println(digitalRead(PIN_BUTTON));

	buttonStartStop(true);
	inicia();

}
