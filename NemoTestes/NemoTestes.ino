#include <IRremote.h>
#include "_config.h"
#include "motors.h"
#include "Sensores.h"
#include <VL53L0X.h>
#include <stdlib.h>

float armazena_valor = 0;

IRrecv irrecv(RECV_PIN);  
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup start...");

  pinMode(LED1, OUTPUT);
  Serial.println("Led OK");

  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  Serial.println("Seletor OK");

  pinMode(borda1, INPUT);
  pinMode(borda2, INPUT);
  Serial.println("Sensores de borda OK");
  
  irrecv.enableIRIn();
  Serial.println("Sensor IR OK");

  Motors::init();
  Serial.println("Motors ON  ");

  Sensores::init();
  Serial.println("Sensores de distância iniciado...");

  Serial.println("Setup Finished...  ");
  delay(900);
}

//--------- FUNÇÕES PARA TESTES ----------//

//Pisca Led
void pisca(int frequencia,int piscagens){

  while(millis()%(piscagens*frequencia*2)!=0){
      if((millis()/frequencia)%2 == 0){
          digitalWrite(LED1,1);
      }
      else
          digitalWrite(LED1,0);
  }
      
  digitalWrite(LED1,0);
  
}


//Estratégia simples
void estrategiaSimples(int Power){
  
  //TESTE DE ESTRATÉGIA AQUI
  
}

//Teste dos Motores
void testeMotores(int Power){
  Motors::stop();
  Motors::driveTeste(Power,Power);
  delay(3000);
  Motors::driveTeste(-Power,Power);
  delay(3000);
  Motors::driveTeste(Power,-Power);
  delay(3000);
  Motors::driveTeste(-Power,-Power);
  delay(3000);
  Motors::stop();
  delay(20);
  return;
}

//Teste dos sensores de ditância
void testeSensores() {
  Serial.print("sensor 1: ");
  Serial.print(Sensores::get_valor(Sensores::sensor1));
  Serial.print("  sensor 2: ");
  Serial.print(Sensores::get_valor(Sensores::sensor2));
  Serial.print("  sensor 3: ");
  Serial.print(Sensores::get_valor(Sensores::sensor3));
  Serial.print("  sensor 4: ");
  Serial.println(Sensores::get_valor(Sensores::sensor4));
  return;
}

//Teste dos sensores de borda
void testeBordas(){
  if (digitalRead(borda1) == LOW){
    digitalWrite(LED1,HIGH);
    delay(1000);
    digitalWrite(LED1,LOW);
    delay(1000); 
  } 
  else{
    digitalWrite(LED1,LOW); 
  }

  if (digitalRead(borda2) == LOW){    
    digitalWrite(LED1,HIGH);
    delay(500);
    digitalWrite(LED1,LOW);
    delay(500); 
  }
  else{
    digitalWrite(LED1,LOW); 
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
