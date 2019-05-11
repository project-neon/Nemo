#include <Motor.h>
#include <Sensores.h>
Move walk(3,4,5,9,7,8);
Sensores eyes;
#define pinBot                  A5

// pinos analogicos dos sensores Refletancia
#define SRF                    A6 
#define SRT                    A7 

// pinos dos leds
#define Led_Azul               2
#define Led_Vermelho           10 

int last = 0; // last é a ultima leitura do sensor pode ser frente ou tras

boolean direcao = true; // True -> frente| False -> tras indica qual foi a ultima direção que foi vista

boolean condicao = false; // indica se ele viu algo na frente ou na traseira

unsigned long tempo = 0;

boolean visao(){ // Uma função que retorna false se o robô não viu alguma coisa em qualquer um dos sensores
eyes.update();   // Uma função que retorna true se o robô viu alguma coisa em qualquer um dos sensores
if(eyes.getNor() != -1 || eyes.getLes() != -1 || eyes.getOes() != -1 || eyes.getSul() != -1)
  return false;
  else return true;
}

void sloth (boolean FrTr, int last){              // FrTr determina se o inimigo esta na frente ou atrás/ last é a ultima leitura do sensor IF
    if((last)>5){                                 // Essa função pode ser dividida em duas partes. A primeira seria para o caso o robô estiver no ponto cego longe dele 
      for(int i = 0; i < 3 ; i++){                // Ele repete a rotina três vezes 
          tempo = millis(); 
          while((millis()-tempo)<48){             // vira durante 48ms ( determinar o melhor tempo ) para direita procurando o adversário 
            if(visao()) return;                   // Se qualquer um dos sensores ver alguma coisa ele retorna e assim tomando a melhor atitude 
            walk.right(150);                      // vira para a direita
          }
          tempo = millis(); 
          while((millis()-tempo)<48){             // vira durante 48ms ( determinar o melhor tempo ) para esquerda procurando o adversário 
            if(visao()) return;                   // Se qualquer um dos sensores ver alguma coisa ele retorna e assim tomando a melhor atitude 
            walk.left(150);                       // vira para a esquerda
          }
  }
}
    else{
      while(visao()){                             // A segunda seria para o caso o robô estiver no ponto cego perto dele 
      FrTr ? walk.front(200) : walk.back(200);    // Onde o parâmetro FrTr determina se o adversário esta na frente ou atrás 
      Serial.println("Agora vou te matar");       // Dado que ambos os lados do robos podem atacar o inimigo
    }
    return;
    }
}
          
void setup() {
  // Config dos leds
  pinMode(Led_Azul, OUTPUT);
  pinMode(Led_Vermelho, OUTPUT);
  // Config dos sensores de refletância 
  pinMode(SRF, INPUT);
  pinMode(SRT, INPUT);
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

}

void loop() {
  walk.brake();
  digitalWrite(Led_Azul, LOW);
  while(!digitalRead(pinBot)){
    Serial.println("Wait");
    delay(10);
  }
  digitalWrite(Led_Azul, HIGH);
  delay(2000);
  
  while(!digitalRead(pinBot)){
    eyes.update();
    while( eyes.getNor() != -1){ // enquanto ele vê alguma 
      walk.front(200);           // coisa na frente dele
      last = eyes.getNor();      // ele vai para frente
      eyes.update();                   
      condicao = true;           // condicao indica se ele viu alguma coisa na frente
      direcao = true;
      Serial.println("vi frente");
      delay(10);
    }
    while(eyes.getSul() != -1 ){  // enquanto ele vê alguma
      walk.back(200);        // coisa na tras dele
      last = eyes.getSul();  // ele vai para tras
      eyes.update();           
      condicao = true;       // condicao indica se ele viu alguma coisa na frente
      direcao = false;       // direcao indica se ele viu na frente ou atras
      Serial.println("vi tras");
      delay(10);
    }
      if(condicao){ // Se ele entrou em um dos pontos cegos do Sensor IF
        sloth(direcao, last);
        condicao = !condicao;
      }
  eyes.update();
  if(eyes.getOes() != -1 && eyes.getNor() == -1 && eyes.getSul() == -1){
      walk.left(200);
      delay(195); // determinar valor pra girar certo
  }
  
  else if(eyes.getLes() != -1 && eyes.getNor() == -1 && eyes.getSul() == -1){
      walk.right(200);
      delay(195); // determinar valor pra girar certo
  }
  }
}
