#define LED1 9
#define LED2 10
#define Button1 11
#define Button2 12
#define Button3 13

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);

}

void loop () {
  if (digitalRead(Button1)==HIGH && digitalRead(Button2)==LOW && digitalRead(Button3)==LOW) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  else if (digitalRead(Button1)==LOW && digitalRead(Button2)==HIGH && digitalRead(Button3)==LOW){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }
  else if (digitalRead(Button1)==LOW && digitalRead(Button2)==LOW && digitalRead(Button3)==HIGH) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
  else if (digitalRead(Button1)==HIGH && digitalRead(Button2)==HIGH && digitalRead(Button3)==LOW){
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, HIGH);
    delay(1000);
    digitalWrite(LED1, LOW);
    delay(1000);
  }
  else if  (digitalRead(Button1)==HIGH && digitalRead(Button2)==LOW && digitalRead(Button3)==HIGH) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(1000);
    digitalWrite(LED2, LOW);
    delay(1000);
  }
  else {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
 }
}
