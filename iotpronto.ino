#include <ESP8266WiFi.h>

#define qtdePinosDigitais  5
int pinosDigitais[qtdePinosDigitais ] = {0 ,4 ,2 ,12, 13};
byte modoDigitais[qtdePinosDigitais ] = {OUTPUT,OUTPUT,INPUT,OUTPUT,OUTPUT };

const char* ssid = "ProjectNeon";
const char* password = "12345678";
WiFiServer server(80);

void configWifi(){
  IPAddress staticIP(192, 168, 4, 2); 
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.mode(WIFI_AP);

  WiFi.softAP(ssid, password, 2, 0);
  WiFi.config(staticIP, gateway, subnet);

  server.begin();

  Serial.println("Server started"); 
  Serial.println(WiFi.softAPIP());
}
String processareq(String req,WiFiClient client){
  req = req.substring(req.indexOf("/") + 1, req.indexOf("HTTP") - 1);
  Serial.println(req);
  return req;
  client.flush();
}

void setup() {
  // put your setup code here, to run once:
  configWifi();

  for(int i = 0; i < qtdePinosDigitais; i++){
    pinMode(pinosDigitais[i],modoDigitais[i]);
  }
  Serial.begin(115200);
  }
void ligar(){
  Serial.println("debug");
  while(!digitalRead(D4)){
    Serial.println("ENTROU");
    digitalWrite(D3,HIGH);
    digitalWrite(D2,HIGH);
    delay(100);
    digitalWrite(D3,LOW);
    digitalWrite(D2,LOW);
    delay(500);
    Serial.println(digitalRead(D4));
  }
}
void mensagem(WiFiClient client,int i){
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>Project Neon</title>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Ol&aacute;, esta p&aacute;gina est&aacute; sendo enviado pelo ESP8266!</h1>");
    client.println("<p>Essa p&aacute;gina ira controlar o nemo</p>");
    client.println("<h1>PORTAS EM FUN&Ccedil;&Atilde;O DIGITAL</h1>");
    client.println("<p><a href=\"?com=START\"><button><b>START</b></button></a>");
    client.println("<p><a href=\"?com=DESLYGA\"><button><b>DESLYGA</b></button></a>");
    client.println("<p><a href=\"?com=LIGA\"><button><b>LIGA</b></button></a>");
    if(i==0){
      client.println("</body>");
      client.println("</html>");
      return;
    } 
    if(i==1){
      client.println("<h1>LIGADO</h1>");
      client.println("</body>");
      client.println("</html>");
      client.flush();
      ligar();
      client.println("<h1>PAROU</h1>");
      return;
    }
    else if(i==2){
      client.println("<h1>DESLYGADO</h1>");
      client.println("</body>");
      client.println("</html>");
      return;
    }
}
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }
  String req = processareq(client.readStringUntil('\r'),client);

  if (req.indexOf("LIGA") != -1){
    Serial.println("ligou");
    mensagem(client,1);
  }
  
  else if (req.indexOf("DESLYGA") != -1){
    for( int i = 0; i < qtdePinosDigitais; i++){
      digitalWrite(pinosDigitais[i],LOW);
  }
    Serial.println("Desligou");
    mensagem(client,2);
  }
  
  else if (req.indexOf("START") != -1)
  {
    mensagem(client,0);
  }
      
  else {
    client.print("Invalid Request");
    client.flush();
    client.stop();
    return;
  }

  client.flush();


}
