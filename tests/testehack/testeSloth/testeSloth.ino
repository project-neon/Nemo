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

int last = 0;

boolean direcao = true; // True -> frente| False -> tras indica qual foi a ultima direção que foi vista

boolean condicao = false; // indica se ele viu algo na frente ou na traseira

unsigned long tempo = 0;

boolean visao(){
eyes.update();
if(eyes.getNor() != -1 || eyes.getLes() != -1 || eyes.getOes() != -1 || eyes.getSul() != -1)
  return false;
  else return true;
}

void sloth (boolean FrTr, int last){
    if((last)>5){
      for(int i = 0; i < 3 ; i++){
          tempo = millis(); 
          while((millis()-tempo)<48){
            if(visao()) return; 
            walk.right(150);         // vira para a direita
          }
          tempo = millis(); 
          while((millis()-tempo)<48){
            if(visao()) return; 
            walk.left(150);         // vira para a esquerda
          }
  }
}
    else{
      while(visao()){
      FrTr ? walk.front(200) : walk.back(200);
      Serial.println("Agora vou te matar");
    }
    return;
    }
}
          
void setup() {
  pinMode(Led_Azul, OUTPUT);
  pinMode(Led_Vermelho, OUTPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(pinBot, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(A4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(Led_Vermelho, HIGH);
  // PARA DEBUG
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
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
      last = eyes.getNor();      // coisa na frente dele
      walk.front(200);           // ele vai para frente
      condicao = true;
      direcao = true;
      Serial.println("vi frente");
      delay(10);
    }
    while(eyes.getSul() != -1 ){  // enquanto ele vê alguma
      last = eyes.getSul();       // coisa na tras dele
      walk.back(200);             // ele vai para tras
      condicao = true;
      direcao = false;
      Serial.println("vi tras");
      delay(10);
    }
      if(condicao){ // Se ele entrou em um dos pontos cegos do Sensor IF
        sloth(direcao, last);
        condicao = !condicao;
      }
      
  if(eyes.getOes() != -1 && eyes.getNor() == -1){
      walk.left(200);
      delay(195); // determinar valor pra girar certo
  }
  
  else if(eyes.getLes() != -1 && eyes.getNor() == -1){
      walk.right(200);
      delay(195); // determinar valor pra girar certo
  }
  }
}
