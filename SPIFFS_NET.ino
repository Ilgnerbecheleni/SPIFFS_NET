#include "FS.h"
#include "SPIFFS.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "Ilgner";
const char* senha = "0123456789";

const int led = 23;
bool ledState = false;

AsyncWebServer server (80);

void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);

pinMode(led,OUTPUT);

digitalWrite(led,LOW);


//inicializando o Wi-fi
WiFi.begin(ssid,senha);

while(WiFi.status() != WL_CONNECTED){
  delay(1000);
  Serial.println("Conectando ao Wi-fi");
}

Serial.println("Conectado ao Wi-fi");
Serial.print("Conectado ao IP");
Serial.println(WiFi.localIP());


//Inicializando a SPIFFs

if(!SPIFFS.begin(true)){
Serial.println("Problemas ao inicializar a SPIFFS");
  return;
}


server.on("/",HTTP_GET , [](AsyncWebServerRequest *request){
  request->send(SPIFFS, "/index.html", "text/html");
});

server.on("/style.css",HTTP_GET , [](AsyncWebServerRequest *request){
  request->send(SPIFFS, "/style.css", "text/css");
});


server.on("/toggleLED",HTTP_GET , [](AsyncWebServerRequest *request){
  
  ledState = !ledState;
  digitalWrite(led, ledState ? HIGH : LOW);
  
  request->send(200, "text/plain",ledState ? "on" : "off" );
});

server.begin();



}

void loop() {
  // put your main code here, to run repeatedly:

}
