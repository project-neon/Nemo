/* 
 * Código para testar o acionamento de 2 motores
 * utilizando 3 sensores VL53L0X como acionadores
 */

//Bibliotecas externas
#include <ESP32Servo.h> //Comunicação com a ESC de cada motor
#include <VL53L0X.h>    //sensores de distância
#include <Wire.h>       //Auxiliar dos sensores
#include <IRremote.h>

//Bibliotecas internas
#include "_config.h"


//Cria os objetos para  cada ESC
Servo ESCL; //ESC que controla o motor da esquerda
Servo ESCR; //ESC que controla o motor da direita

//Cria os objetos para cada sensor
VL53L0X sensorFE;  //Sensor da frente esquerda
VL53L0X sensorFD;  //Sensor da frente direita
VL53L0X sensorTE;  //Sensor de trás esquerda
VL53L0X sensorTD;  //Sensor de trás direita

IRrecv irrecv(JCONTROLLER);
decode_results results;

int stage = 0;

String direction = ""; //Variável que indicará o sentido determinado pelos sensores
int strategy = 0; //Por enquanto, eu estou escrevendo no código, depois vai ser decidido de acordo com o controle do 
//0 = simples
//1 = meialua
//2 = meialua em s

/*
 * No momento em que a placa é alimentada, é necessário que o valor enviado aos ESC's seja o valor 0 (zero)
 * para que os ESC's não entrem em modo de configuração. 
 * Para isso, iniciamos o valor da flag em (-1), pois é um valor que só acontecerá no momento de inicialização.
 * Assim garantimos que no primeiro momento, o valor enviado aos ESC's será 0 (zero).
 */
int flag = 0; //Direita --> 0, Esquerda --> 1, Valor inicial --> -1

void setup(){
  
  Serial.begin(115200);
  
  //Iniciando o endereçamento dos sensores
  Wire.begin();
  
  pinMode(SDIST_FE, OUTPUT);
  pinMode(SDIST_FD, OUTPUT);
  pinMode(SDIST_TE, OUTPUT);
  pinMode(SDIST_TD, OUTPUT);
  digitalWrite(SDIST_FE, LOW);
  digitalWrite(SDIST_FD, LOW);
  digitalWrite(SDIST_TE, LOW);
  digitalWrite(SDIST_TD, LOW);
  
  pinMode(SDIST_FE, INPUT);
  sensorFE.init(true);
  sensorFE.setAddress((uint8_t)0x21); //endereço do sensor da esquerda

  pinMode(SDIST_FD, INPUT);
  sensorFD.init(true);
  sensorFD.setAddress((uint8_t)0x23); //endereço do sensor da frente

  pinMode(SDIST_TE, INPUT);
  sensorTE.init(true);
  sensorTE.setAddress((uint8_t)0x25); //endereço do sensor da direita

  pinMode(SDIST_TD, INPUT);
  sensorTD.init(true);
  sensorTD.setAddress((uint8_t)0x25); //endereço do sensor da direita

  sensorFE.setTimeout(100);
  sensorFD.setTimeout(100);
  sensorTE.setTimeout(100);
  sensorTD.setTimeout(100);
  
  //Configurando o sinal PWM que será enviado aos ESC's
  ESCL.setPeriodHertz(50);             // Estabelece a frequência do PWM (50Hz)
  ESCL.attach(MOTOR_L, 1000,2000);     // (Pino onde será enviado o sinal, largura de pulso mínima, largura de pulso máxima)
  ESCR.setPeriodHertz(50);              
  ESCR.attach(MOTOR_R, 1000,2000);     
  /*                                      
   * É necessário estabelecer uma faixa de largura de pulso para que o ESC
   * responda corretamente a variação do sinal analógico lido do potenciômetro
   * O valor da largura de pulso deve ser informado na escala de micro-segundos
   * No caso, a largura de pulso do PWM mínima é de 1000us e a máxima é de 2000us                                      
   */
}

void estrategiaSimples() {
  if ((distFD < distMax && distFD < distFE) && (distTD >= distMax && distTE >= distMax)){
    speedL = 100;
    speedR = 30;
    direction = "FRENTE + DIR";
    flag = 0;
  } 
  else if(( distFE < distMax && distFE < distFD) && (distTD >= distMax && distTE >= distMax) ){
    speedL = 30;
    speedR = 100;
    direction = "FRENTE + ESQ";
    flag = 1;
  } 
  else if(distFE >= distMax && (distFD < distMax || flag == 0)&& (distTD >= distMax && distTE >= distMax)){
    speedL = 100;
    speedR = 0;
    direction = "FRENTE DIREITA";
    flag = 0;
  } else if(distFD >= distMax && (distFE < distMax || flag == 1)&& (distTD >= distMax && distTE >= distMax)){
    speedL = 0;
    speedR = 100;
    direction = "FRENTE ESQUERDA";
    flag = 1;
  } 
  else if(distFE < distMax && distFD < distMax){
    speedL = 100;
    speedR = 100;
    direction = "FRENTE";
  }   
  else if (distTD < distMax && (distTE < distMax) && distTE >= distMax){
    speedL = 100;
    speedR = 30;
    direction = "TRÁS + DIR";
    flag = 0;
  } 
  else if(( distTE < distMax && distTE < distTD) && (distFD >= distMax && distFE >= distMax) ){
    speedL = 30;
    speedR = 100;
    direction = "TRÁS + ESQ";
    flag = 1;
  } 
  else if(distTE >= distMax && (distTD < distMax || flag == 0)&& (distFD >= distMax && distFE >= distMax)){
    speedL = 100;
    speedR = 0;
    direction = "TRÁS DIREITA";
    flag = 0;
    
  } else if(distTD >= distMax && (distTE < distMax || flag == 1)&& (distFD >= distMax && distFE >= distMax)){
    speedL = 0;
    speedR = 100;
    direction = "TRÁS ESQUERDA";
    flag = 1;
  } 
  else if(distTE < distMax && distTD < distMax){
    if(flag==1){
      speedL = 0;
      speedR = 100;
      }
    else{
      speedL = 100;
      speedR = 0;
      }
    direction = "TRÁS";
  }   
  else{
    speedL = 0;
    speedR = 0;
    direction = "IMPOSSIVEL"; // Sensores da esquerda e direita detectando algo simultaneamente e o sensor da frente não
  }
}

//Condições dessa estratégia:
//O robô já começa virado e com uma certa distância da borda (a decidir pelos testes #TODO)
//O robô n pensa, só acelera em meia lua!
void meiaLua() {
  //TODO: testar o tempo que o robô demora pra percorrer metade da arena e qual a melhor vel
  for (int timer = 0; timer < 1000 * 1; timer++) {
    speedL = map(25, 0, 100, 0, 180);
    speedR = map(100, 0, 100, 0, 180);
    ESCL.write(speedL); 
    ESCR.write(speedR); 
  }
  flag = 1; //Considera que o inimigo deve estar na esquerda pois atacou pela direita
  strategy = 0; //Retorna pra estratégia padrão caso o ataque inicial não tenha dado certo
}

//Condições dessa estratégia:
//O robô comseça virado pro inimigo e dá uma voltinha pra poder fazer a meia lua
//O robô n pensa, só acelera em meia lua!
void meiaLuaEmS() {
  //TODO: testar o tempo que o robô demora pra percorrer metade da arena e qual a melhor vel
  for (int timer = 0; timer < 1000 * 0.25; timer++) {
    speedL = map(100, 0, 100, 0, 180);
    speedR = map(25, 0, 100, 0, 180);
    ESCL.write(speedL); 
    ESCR.write(speedR); 
  }
  for (int timer = 0; timer < 1000 * 0.75; timer++) {
    speedL = map(25, 0, 100, 0, 180);
    speedR = map(100, 0, 100, 0, 180);
    ESCL.write(speedL); 
    ESCR.write(speedR); 
  }
  flag = 1; //Considera que o inimigo deve estar na esquerda pois atacou pela direita
  strategy = 0; //Retorna pra estratégia padrão caso o ataque inicial não tenha dado certo
}

int branco_treshold = 500; //valor arbitrário de calibragem

void loop() {

  if (irrecv.decode(&results)) {  
    
    float value;
    //String 
    value = (results.value);
    Serial.print("Valor lido : ");  
//  Serial.println(results.value, DEC);  
    Serial.println(results.value, HEX);

    //bloco de lógica para acionamento/desacionamento do robô via controle IR
    if (value == 0x9716BE3F) { //Verifica se a tecla 1 foi acionada 
      stage=1;
      Serial.println("Estagio 1");
    }
    else if (value == 0x3D9AE3F7 && stage == 1) { //Verifica se a tecla 2 foi acionada  
      stage=2;
      Serial.println("Estagio 2");
    }
    else if (value ==  0x6182021B && stage == 2) { //Verifica se a tecla 3 foi acionada  
      stage=3;
      Serial.println("Estagio 3");
    }
    else if (stage==3 && (value == 0x9716BE3F  || value == 0x3D9AE3F7)){
      stage = 0;
    }
    irrecv.resume(); //Le o proximo valor
  } 

  //bloco de progressão de estágio
  
  if (stage==1) {  
    
//    digitalWrite(PIN_REDLED, HIGH);
    delay(5);
//    digitalWrite(PIN_REDLED, LOW);
    delay(5);
    
    Serial.println("Estágio 1");

    //Armazena os valores lidos nas respectivas variáveis
    distFE = sensorFE.readRangeSingleMillimeters();
    distFD = sensorFD.readRangeSingleMillimeters();
    distTE = sensorTE.readRangeSingleMillimeters();  
    distTD = sensorTD.readRangeSingleMillimeters();  
  }  

  else if (stage==2){  
    
    //digitalWrite(PIN_REDLED, HIGH);

   //Tomadas de decisão
  //Os valores aqui utilizados servem apenas para um teste de tomada de decisão
  //O número "200" é um número aleatório apenas para o teste

  //TODO: Alterar pra começar verificando as distC/L/R
  if(flag == -1 && distFE > 5000 && distFD > 5000 && distTE > 5000 && distTD > 5000 ){
    speedL = 0;
    speedR = 0;
    direction = "COND. INICIAL";
  }
  
    switch(strategy) {
    case 0:
      estrategiaSimples();
      break;
    case 1:
      meiaLua();
      break;
    case 2:
      meiaLuaEmS();
      break;
     default:
      estrategiaSimples();
      break;
  }
 
  // Mostra o valor que será enviado às ESCS
  Serial.print(speedL);
  Serial.print("\t");
  Serial.print(speedR); 
  Serial.print("\t\t");
  
  // Mostra o valor de cada sensor na tela e a decisão escolhida
  Serial.print("FD: ");
  Serial.print(distFD);
  Serial.print("\t");
  Serial.print("C: ");
  Serial.print((distFD+distFE)/2);
  Serial.print("\t");
  Serial.print("FE: ");
  Serial.print(distFE);
  Serial.print("\t\t");
  Serial.print("TD: ");
  Serial.print(distTD);
  Serial.print("\t");
  Serial.print("C: ");
  Serial.print((distTD+distTE)/2);
  Serial.print("TE: ");
  Serial.print(distTE);
  Serial.print("\t\t");
  Serial.println(direction);

  // Converte os valores de 0 a 100 para os valores lidos pelos ESC's que vão de 0 a 180
  speedL = map(speedL, 0, 100, 0, 180);
  speedR = map(speedR, 0, 100, 0, 180);
  
  // Envia o valor para as ESCs
  ESCL.write(speedL); 
  ESCR.write(speedR); 
      
  }
    
  else if (stage==3) {   
    Serial.println("S T O P");
    //digitalWrite(PIN_REDLED, HIGH);
    //Motors::stop();
  }  


}
