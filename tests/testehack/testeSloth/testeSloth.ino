// ultima programação feita 
#include "Motors.h"
#include "Sensores.h"
// pino botao
#define pinBot                  A5

// pinos dos leds
#define Led_Azul               2
#define Led_Vermelho           10 

int last = 0; // last é a ultima leitura do sensor pode ser frente ou tras

boolean direcao = true; // True -> frente| False -> tras indica qual foi a ultima direção que foi vista

boolean condicao = false; // indica se ele viu algo na frente ou na traseira

unsigned long tempo = 0;
int count = 0;
int velvirada = 60;
int velataque = 100;
void sloth (boolean FrTr, int last){              // FrTr determina se o inimigo esta na frente ou atrás/ last é a ultima leitura do sensor IF
  /*
    if((last)>5){                                 // Essa função pode ser dividida em duas partes. A primeira seria para o caso o robô estiver no ponto cego longe dele 
      for(int i = 0; i < 3 ; i++){                // Ele repete a rotina três vezes 
          tempo = millis(); 
          while((millis()-tempo)<48){             // vira durante 48ms ( determinar o melhor tempo ) para direita procurando o adversário 
          controller.run();
            if(Sensores::visao()) return;                   // Se qualquer um dos sensores ver alguma coisa ele retorna e assim tomando a melhor atitude 
            Motors::driveTank(velvirada,-velvirada);                      // vira para a direita
          }
          tempo = millis(); 
          while((millis()-tempo)<48){             // vira durante 48ms ( determinar o melhor tempo ) para esquerda procurando o adversário 
          controller.run();
            if(Sensores::visao()) return;                   // Se qualquer um dos sensores ver alguma coisa ele retorna e assim tomando a melhor atitude 
            Motors::driveTank(velvirada,-velvirada);                       // vira para a esquerda
          }
  }
}*/
    //else{
      while(Sensores::visao() && Sensores::white ){                             // A segunda seria para o caso o robô estiver no ponto cego perto dele 
      controller.run();
      if(Sensores::values[1] != -1 && Sensores::values[0] == -1  && Sensores::values[3] == -1 ){
        count++;
        if ( count > 8) return;
      }
      else count = 0;
      direcao ? Motors::driveTank(-velataque,-velataque) : Motors::driveTank(velataque,velataque);       // Onde o parâmetro FrTr determina se o adversário esta na frente ou atrás 
      direcao ? Serial.println("Na minha Frente"): Serial.println("na minha traseira");;       // Dado que ambos os lados do robos podem atacar o inimigo
      digitalWrite(Led_Azul, LOW);
    }
    return;
    //}
}

void setup() {
  Sensores::init();
	Motors::init();
  // Config dos leds
  pinMode(Led_Azul, OUTPUT);
  pinMode(13, OUTPUT);
  // Config do botao
  pinMode(pinBot, INPUT);
  // Config dos pinos que estabelecem pinos de STBY
  pinMode(A4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(A4, HIGH);
  digitalWrite(6, HIGH); // Lembrar que eu desliguei isso
  // Liga o led vermelho quando liga o robô
  digitalWrite(13, HIGH);
  Sensores::valor_preto_frente = analogRead(A6)- 500;
  Sensores::valor_preto_tras = analogRead(A7)- 200;
  // PARA DEBUG
  Serial.begin(115200);

  //attachInterrupt(Sensores::white,Motors::stop, LOW);

}

void loop() {
  delay(300);
  Motors::stop();
  digitalWrite(Led_Azul, LOW);
  while(!digitalRead(pinBot)){
    controller.run();
    Serial.println("Wait");
    if(Sensores::white) digitalWrite(Led_Azul, LOW);
    else digitalWrite(Led_Azul, HIGH);
    delay(10);
  }
  

  digitalWrite(Led_Azul, HIGH);
  tempo = millis();
  while ( millis() - tempo < 5000) Serial.println(millis() - tempo );
  
  while(!digitalRead(pinBot)){
  if(!Sensores::white){
    while(!Sensores::white){
    controller.run();
    Sensores::direcao ? Motors::driveTank(velataque,velataque) : Motors::driveTank(-velataque,-velataque); // true -> é o sensor frente / false -> é o sensor tras
    Serial.println("vi branco");
  }
    delay(200);
    Motors::driveTank(-90,90);
    delay(150);

  }
    controller.run();
    while( Sensores::values[0] != -1 && Sensores::white){ // enquanto ele vê alguma 
      Motors::driveTank(-velataque,-velataque);           // coisa na frente dele
      last = Sensores::values[0] ;     // ele vai para frente
      controller.run();                
      condicao = true;           // condicao indica se ele viu alguma coisa na frente
      direcao = true;
      digitalWrite(Led_Azul, HIGH);
      Serial.println("vi frente");
    }
    /*
    while(Sensores::values[3] != -1 && Sensores::white){  // enquanto ele vê alguma
      Motors::driveTank(velataque,velataque);        // coisa na tras dele
      last = Sensores::values[2] ; // ele vai para tras
      controller.run();      
      condicao = true;       // condicao indica se ele viu alguma coisa na frente
      direcao = false;       // direcao indica se ele viu na frente ou atras
      digitalWrite(Led_Azul, HIGH);
      Serial.println("vi tras");
      delay(10);
    }*/
      if(condicao){ // Se ele entrou em um dos pontos cegos do Sensor IF
        sloth(direcao, last);
        condicao = !condicao;
      }
      
  controller.run();
  if(Sensores::values[1] != -1 && Sensores::values[0] == -1 && Sensores::values[3] == -1 ){
    count++;
  }
  else count = 0;
  if(count == 8 ){
      Motors::driveTank(-velvirada,velvirada);
      Serial.println("vi esquerda");
      digitalWrite(Led_Azul, LOW);
  }
  if(Sensores::visao()) {
    Motors::driveTank(-velvirada,velvirada);
    Serial.println("Se esconde não!!!");
  }
  /*
  else if(Sensores::values[3] != -1 && Sensores::values[0] == -1 && Sensores::white){
      Motors::driveTank(velvirada,-velvirada);
      Serial.println("vi direita");
      delay(195); // determinar valor pra girar certo
  }*/
  }
}
