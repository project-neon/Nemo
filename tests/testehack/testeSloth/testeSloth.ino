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

void sloth (boolean FrTr, int last){              // FrTr determina se o inimigo esta na frente ou atrás/ last é a ultima leitura do sensor IF
    if((last)>5){                                 // Essa função pode ser dividida em duas partes. A primeira seria para o caso o robô estiver no ponto cego longe dele 
    Serial.println("sloth");
      for(int i = 0; i < 3 ; i++){                // Ele repete a rotina três vezes 
          tempo = millis(); 
          while((millis()-tempo)<48){             // vira durante 48ms ( determinar o melhor tempo ) para direita procurando o adversário 
          controller.run();
            if(Sensores::visao()) return;                   // Se qualquer um dos sensores ver alguma coisa ele retorna e assim tomando a melhor atitude 
            Motors::driveTank(45,-45);                      // vira para a direita
          }
          tempo = millis(); 
          while((millis()-tempo)<48){             // vira durante 48ms ( determinar o melhor tempo ) para esquerda procurando o adversário 
          controller.run();
            if(Sensores::visao()) return;                   // Se qualquer um dos sensores ver alguma coisa ele retorna e assim tomando a melhor atitude 
            Motors::driveTank(45,-45);                       // vira para a esquerda
          }
  }
}
    else{
      while(Sensores::visao()){                             // A segunda seria para o caso o robô estiver no ponto cego perto dele 
      controller.run();
      FrTr ? Motors::driveTank(45,45) : Motors::driveTank(-45,-45);    // Onde o parâmetro FrTr determina se o adversário esta na frente ou atrás 
      Serial.println("Agora vou te matar");       // Dado que ambos os lados do robos podem atacar o inimigo
    }
    return;
    }
}

void falling(){ // função para quando o robô ver branco
  Motors::stop();
  delay(2);
  Serial.println("branco");
  tempo = millis(); 
  while((millis()-tempo)<50){
    Sensores::direcao ? Motors::driveTank(-45,-45) : Motors::driveTank(45,45);
  }
  
}

void setup() {
  Sensores::init();
	Motors::init();
  // Config dos leds
  pinMode(Led_Azul, OUTPUT);
  pinMode(Led_Vermelho, OUTPUT);
  // Config do botao
  pinMode(pinBot, INPUT);
  // Config dos pinos que estabelecem pinos de STBY
  pinMode(A4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(A4, HIGH);
  digitalWrite(6, HIGH);
  // Liga o led vermelho quando liga o robô
  digitalWrite(Led_Vermelho, HIGH);
  // PARA DEBUG
  Serial.begin(115200);

  attachInterrupt(Sensores::white, falling, LOW);

}

void loop() {
  Motors::stop();
  digitalWrite(Led_Azul, LOW);
  while(!digitalRead(pinBot)){
    Serial.println("Wait");
    delay(10);
  }
  

  digitalWrite(Led_Azul, HIGH);
  delay(2000);
  
  while(!digitalRead(pinBot)){
    controller.run();
    while( Sensores::values[0] != -1){ // enquanto ele vê alguma 
      Motors::driveTank(45,45);        // coisa na frente dele
      last = Sensores::values[0] ;     // ele vai para frente
      controller.run();                
      condicao = true;                 // condicao indica se ele viu alguma coisa na frente
      direcao = true;
      Serial.println("vi frente");
      delay(10);
    }
    /*
    while(Sensores::values[2] != -1 ){ // enquanto ele vê alguma
      Motors::driveTank(-45,-45);      // coisa na tras dele
      last = Sensores::values[2] ;     // ele vai para tras
      controller.run();      
      condicao = true;                 // condicao indica se ele viu alguma coisa na frente
      direcao = false;                 // direcao indica se ele viu na frente ou atras
      Serial.println("vi tras");
      delay(10);
    }*/
    
    /*
      if(condicao){ // Se ele entrou em um dos pontos cegos do Sensor IF
        sloth(direcao, last);
        condicao = !condicao;
      }
      */
  controller.run();
  if(Sensores::values[1] != -1 && Sensores::values[0] == -1 ){
      Motors::driveTank(-45,45);
      Serial.println("vi esquerda");
      delay(195); // determinar valor pra girar certo
  }
  
  else if(Sensores::values[3] != -1 && Sensores::values[0] == -1){
      Motors::driveTank(45,-45);
      Serial.println("vi direita");
      delay(195); // determinar valor pra girar certo
  }
  }
}
