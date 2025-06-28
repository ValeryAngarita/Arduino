//Control Wifi Led
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "A15";
const char* password = "Valery123";

WebServer server (80);

const int OUT1 = 25;//Derecha
const int OUT2 = 26;//Derecha
const int OUT3 = 27;//Izquierda
const int OUT4 = 14;//Izquierda

void controlMotores(String dir) {
  if (dir == "up") {
    digitalWrite(OUT1, 1);
    digitalWrite(OUT2, 0);
    digitalWrite(OUT3, 1);
    digitalWrite(OUT4, 0);
  }
  else if (dir == "down") {
    digitalWrite(OUT1, 0);
    digitalWrite(OUT2, 1);
    digitalWrite(OUT3, 0);
    digitalWrite(OUT4, 1);
  }
  else if (dir == "left") {
    digitalWrite(OUT1, 0);
    digitalWrite(OUT2, 1);
    digitalWrite(OUT3, 1);
    digitalWrite(OUT4, 0);
  }
  else if (dir == "right") {
    digitalWrite(OUT1, 1);
    digitalWrite(OUT2, 0);
    digitalWrite(OUT3, 0);
    digitalWrite(OUT4, 1);
  }
  else if (dir == "stop") {
    digitalWrite(OUT1, 0);
    digitalWrite(OUT2, 0);
    digitalWrite(OUT3, 0);
    digitalWrite(OUT4, 0);
  }
}

  // HTML incrustado
  const char* htmlPage = R"rawliteral(
  <!DOCTYPE html>
  <html lang="es">
  <head>
    <meta charset="UTF-8">
    <title>Carrito</title>
    <style>
      body {
        background-color: #FADADD;
        font-family: 'Segoe UI', sans-serif;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        height: 100vh;
        margin: 0;
      }
      .remote {
        display: grid;
        grid-template-columns: repeat(3, 80px);
        grid-template-rows: repeat(3, 80px);
        gap: 10px;
        background: #fff;
        padding: 25px;
        border-radius: 20px;
        border: 2px solid #C70039;
      }
      .btn {
        border: none;
        border-radius: 10px;
        background-color: #F6A6B2;
        color: #C70039;
        font-size: 24px;
        font-weight: bold;
        cursor: pointer;
      }
      .btn:hover {
        background-color: #C70039;
        color: white;
      }
      .btn-stop {
        background-color: #C70039;
        color: white;
      }
    </style>
  </head>
  <body>
    <div class="remote">
      <div></div>
      <button class="btn" onclick="sendCmd('up')">↑</button>
      <div></div>
      <button class="btn" onclick="sendCmd('left')">←</button>
      <button class="btn btn-stop" onclick="sendCmd('stop')">Stop</button>
      <button class="btn" onclick="sendCmd('right')">→</button>
      <div></div>
      <button class="btn" onclick="sendCmd('down')">↓</button>
      <div></div>
    </div>

    <script>
      function sendCmd(cmd) {
        fetch('/cmd?dir=' + cmd);
      }
    </script>
  </body>
  </html>
  )rawliteral";

void setup() {
 pinMode(OUT1, OUTPUT);
 pinMode(OUT2, OUTPUT);
 pinMode(OUT3, OUTPUT);
 pinMode(OUT4, OUTPUT);

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


  // Página principal (HTML)
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlPage);
  });

  // Ruta para recibir comandos de movimiento
  server.on("/cmd", HTTP_GET, []() {
    String dir = server.arg("dir");  // Obtener el parámetro 'dir' de la URL
    controlMotores(dir);             // Llamar a la función para controlar los motores
    server.send(200, "text/plain", "OK");
  });
 server.begin();
}

void loop() {
 server.handleClient ();
}
