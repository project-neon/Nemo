// Definir quais são as portas 

int freq = 5000;
int resolution = 8;

// Led
#define Led_Verde 23 
#define Led_Azul 22 
#define Led_Vermelho 1 

// Motor Direito
#define BIN1 3   //Modo de operação 
#define BIN2  18 //Modo de operação 
#define PWMB 19  //Controle de Velocidade
#define MOTOR_A 0 // Define motor da direita com valor 1


//Motor Esquerdo 
#define AIN1 5  // Modo de operação 
#define AIN2 17 // Modo de operação 
#define PWMA 16 // Controle de Velocidade
#define MOTOR_B 1 //Define motor da direita com valor 2


void setup() {
  // CONFIGURACAO DOS PINOS USADOS
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);

  pinMode(Led_Verde , OUTPUT);
  pinMode(Led_Azul, OUTPUT);
  pinMode(Led_Vermelho, OUTPUT);

  // PARA DEBUG
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean inPin1;
  boolean inPin2;
  digitalWrite(Led_Verde , HIGH);
  digitalWrite(Led_Azul, LOW);
  digitalWrite(Led_Vermelho, LOW);
  
  inPin1 = LOW;
  inPin2 = HIGH;
  digitalWrite(AIN1, inPin1); // 0101
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA , 255);
  digitalWrite(BIN1, inPin1);
  digitalWrite(BIN2, inPin2);
  analogWrite(PWMB , 255);
  delay(2000);

  
  digitalWrite(Led_Verde , LOW); 
  digitalWrite(Led_Azul, HIGH);
  digitalWrite(Led_Vermelho, LOW);
  
  inPin1 = LOW;
  inPin2 = HIGH;
  digitalWrite(AIN1, inPin1); // 0110
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, 255);
  digitalWrite(BIN1, !inPin1);
  digitalWrite(BIN2, !inPin2);
  analogWrite(PWMB , 255);
  delay(2000);
  
  
  digitalWrite(Led_Verde , LOW);
  digitalWrite(Led_Azul, LOW);
  digitalWrite(Led_Vermelho, HIGH);
  
  inPin1 = HIGH;
  inPin2 = LOW;
  digitalWrite(AIN1, inPin1); // 1010
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA , 255);
  digitalWrite(BIN1, inPin1);
  digitalWrite(BIN2, inPin2);
  analogWrite(PWMB , 255);
  delay(2000);

  
  digitalWrite(Led_Verde , HIGH);
  digitalWrite(Led_Azul, HIGH);
  digitalWrite(Led_Vermelho, HIGH);
  
  inPin1 = HIGH;
  inPin2 = LOW;
  digitalWrite(AIN1, inPin1); // 1001
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA , 255);
  digitalWrite(BIN1, !inPin1);
  digitalWrite(BIN2, !inPin2);
  analogWrite(PWMB, 255);
  delay(2000);
  
}





/* Possibilidades para ter ideias das direções 

LOW  --> 0
HIGH --> 1

// 0101
  inPin1 = LOW;
  inPin2 = HIGH;
  digitalWrite(AIN1, inPin1); // 0101
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA , 255);
  digitalWrite(BIN1, inPin1);
  digitalWrite(BIN2, inPin2);
  analogWrite(PWMB , 255);

// 0110
  inPin1 = LOW;
  inPin2 = HIGH;
  digitalWrite(AIN1, inPin1); // 0110
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, 255);
  digitalWrite(BIN1, !inPin1);
  digitalWrite(BIN2, !inPin2);
  analogWrite(PWMB , 255);

// 1010
  inPin1 = HIGH;
  inPin2 = LOW;
  digitalWrite(AIN1, inPin1); // 1010
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA , 255);
  digitalWrite(BIN1, inPin1);
  digitalWrite(BIN2, inPin2);
  analogWrite(PWMB , 255);

// 1001
  inPin1 = HIGH;
  inPin2 = LOW;
  digitalWrite(AIN1, inPin1); // 1001
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA , 255);
  digitalWrite(BIN1, !inPin1);
  digitalWrite(BIN2, !inPin2);
  analogWrite(PWMB, 255);
*/
