//Control Wifi Led
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "A15";
const char* password = "Valery123";

WebServer server (80);
const int ledPin = 2;

void inicio (){

  /*Servidor tiene argumento llamado led1 - Valor del argumento "led1" igual a - "on"*/
  if (server.hasArg("led1") && server.arg ("led1") == "on"){
    digitalWrite(ledPin, HIGH);
  }

  else if (server.hasArg("led1") && server.arg ("led1") == "off"){
    digitalWrite(ledPin, LOW);
  }

  //Página HTML
  String html = "<html><body>";
  html += " <title>Control LED ESP32</title>";
  html += "<h1>Control del LED</h1>";
  html += "<form method = 'get'>";
  html += "<button type = 'submit' name = 'led1' value = 'on' >Encender</button>";
  html += "<button type = 'submit' name = 'led1' value = 'off' >Apagar</button>";
  html += "</body></html>";

  server.send(200, "text/html", html); //Enviar página HTML
}

void setup() {
 pinMode(ledPin, OUTPUT);

 Serial.begin (115200); //Velocidad
 Serial.println ("Conectando...");
 Serial.println(ssid);

 WiFi.mode(WIFI_STA);//Modo estación
 WiFi.begin(ssid, password);
 Serial.println("");

 while (WiFi.status() != WL_CONNECTED){ //Espera a conectarse
  delay (500);
  Serial.print(".");
 }
 Serial.println ("");
 Serial.println ("Wifi conectado a");
 Serial.println (ssid);
 Serial.println ("Dirección IP asignada por el router: ");
 Serial.println (WiFi.localIP()); //IP dada por el router

 server.on ("/", inicio); //Llamar función
 server.begin();
}

void loop() {
 server.handleClient ();
}
