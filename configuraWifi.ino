#include <ESP8266WiFi.h>

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
void processaPortaout(int porta,WiFiClient client,String URLValue)
{
static boolean LED_status = 0;
String cHTML;

    cHTML = "D";
    cHTML += String(porta);
    cHTML += "=";
    cHTML += String(porta);

        
        if (URLValue.indexOf(cHTML) > -1) { 
           LED_status = HIGH;
        } else {
           LED_status = LOW;
        }
        digitalWrite(porta, LED_status);
    
        
    cHTML = "<input type=\"checkbox\" name=\"D";
    cHTML += String(porta);
    cHTML += "\" value=\"";
    cHTML += String(porta);
    
    cHTML += "\"";
    //cHTML += "\" onclick=\"submit();\"";

    if (LED_status) { 
        cHTML += " checked ";
    }
    
    cHTML += ">Porta ";
    cHTML += "D";
    cHTML += String(porta);
    
    client.println(cHTML);
}

void processaPortain(int porta,WiFiClient client,String URLValue)
{
static boolean LED_status = 0;
String cHTML;

    cHTML = "D";
    cHTML += String(porta);
    cHTML += "=";
    cHTML += String(porta);

        
    LED_status = digitalRead(porta);
    
        
    cHTML = "<input type=\"checkbox\" name=\"D";
    cHTML += String(porta);
    cHTML += "\" value=\"";
    cHTML += String(porta);
    
    cHTML += "\"";
    //cHTML += "\" onclick=\"submit();\"";

    if (LED_status) { 
        cHTML += " checked ";
    }
    cHTML += " disabled ";
    
    cHTML += ">Porta ";
    cHTML += "D";
    cHTML += String(porta);
    
    client.println(cHTML);
}
void mensagem(WiFiClient client,String req){

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
                    

    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>Project Neon</title>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Ol&aacute;, esta p&aacute;gina est&aacute; sendo enviado pelo ESP8266!</h1>");
    client.println("<p>Essa p&aacute;gina ira controlar o nemo</p>");
    client.println("<h1>PORTAS EM FUN&Ccedil;&Atilde;O ANAL&Oacute;GICA</h1>");
    client.print("<p>Porta A");
    client.print(" - Valor: ");
    client.println( analogRead(A0) );
    client.println("</p>");          
    client.println("<h1>PORTAS EM FUN&Ccedil;&Atilde;O DIGITAL</h1>");
    client.println("<form method=\"get\">");
    processaPortaout(5 ,client ,req);
    client.println("<br/>");
    processaPortain(4 ,client ,req);
    client.println("<br/>");
    client.println("<br/>");
    client.println("<button type=\"submit\">Envia para o Arduino</button>");
    client.println("</form>");
    client.println("</body>");
    client.println("</html>");

}

String processareq(String req,WiFiClient client){
  req = req.substring(req.indexOf("/") + 1, req.indexOf("HTTP") - 1);
  Serial.println(req);
  return req;
  client.flush();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 

  configWifi();

  pinMode(D1,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(D2,INPUT);

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


  if (req.indexOf("BORA") != -1)
  {
    mensagem(client,req);
  }
    
  else {
    client.print("Invalid Request");
    client.flush();
    client.stop();
    return;
  }

  client.flush();

}
