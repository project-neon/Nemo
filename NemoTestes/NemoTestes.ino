#include <IRremote.h>
#include "_config.h"
#include "motors.h"
#include "Sensores.h"
#include <VL53L0X.h>
#include <stdlib.h>

float armazena_valor = 0;
int cal = 150; //valor de referência para os sensores de borda

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
  Serial.println("Sensores OK");

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
void testeBordas(int ref){
  if (digitalRead(borda1) < ref){
    digitalWrite(LED1,HIGH);
    delay(1500);
    digitalWrite(LED1,LOW);
    delay(1500); 
  } 
  else{
    digitalWrite(LED1,LOW); 
  }

  if (digitalRead(borda2) < ref){    
    digitalWrite(LED1,HIGH);
    delay(500);
    digitalWrite(LED1,LOW);
    delay(500); 
    digitalWrite(LED1,HIGH);
    delay(500);
    digitalWrite(LED1,LOW);
    delay(1500); 
  }
  else{
    digitalWrite(LED1,LOW); 
  }
}

void testeSeletor(){
  //função para mostrar na tela o estado de cada botão e o valor em decimal respectivo da combinação dos botões
  //ordem dos botões:

  //B1    B2    B3

  //variáveis para armazenar os valores dos botões
  bool b1 = digitalRead(B1);
  bool b2 = digitalRead(B2);
  bool b3 = digitalRead(B3);

  Serial.print(b1);
  Serial.print(b2);
  Serial.print(b3);
  Serial.print(" = ");
  Serial.println((2^(b1*2))*b1+(2^(b2*1))*b2+1*b3);

//Tabela de conversão
//  0 0 0 = 0
//  0 0 1 = 1
//  0 1 0 = 2
//  0 1 1 = 3
//  1 0 0 = 4
//  1 0 1 = 5
//  1 1 0 = 6
//  1 1 1 = 7
}

void loop() {
  // put your main code here, to run repeatedly:

//  estrategiaSimples(50);    //chama a função de Estratégia simples, o robô estará com 50% da potência
//  testeMotores(50);   //Testa os motores com 50% de potência 
//  testeSensores();    //Testa se todos os sensores estão funcionando
//  testeBordas(cal);   //Testa os sensores de borda, de acordo com o valor de referência "cal"
  
}
