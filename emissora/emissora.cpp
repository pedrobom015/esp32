// Limeira, SP - 27/06/2026: (Placa na Casa do Sítio - Controla as duas receptoras)
// A página web continuará centralizada no seu celular, mas agora ela enviará códigos
// distintos para cada destino.

#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306Wire.h"

#define SS      18
#define RST     14
#define DIO0    26
#define BAND    915E6

const char* ssid     = "NOME_DA_SUA_REDE_WIFI";
const char* password = "SENHA_DO_WIFI";

WiFiServer server(80);
SSD1306Wire display(0x3c, 4, 15);

void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); delay(50); digitalWrite(16, HIGH);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    display.drawString(0, 0, "Erro no LoRa!");
    display.display();
    while (1);
  }
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  server.begin();
  display.clear();
  display.drawString(0, 0, "Wi-Fi Conectado!");
  display.drawString(0, 15, "IP do Painel:");
  display.drawString(0, 30, WiFi.localIP().toString());
  display.display();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html; charset=utf-8");
            client.println("Connection: close");
            client.println();
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<style>body{font-family:Arial; text-align:center;} .btn{padding:20px; font-size:24px; margin:10px; cursor:pointer; color:white; border:none; border-radius:5px;} .on{background-color:green;} .off{background-color:red;}</style></head>");
            client.println("<body><h1>Controle Multi-LoRa</h1>");
            client.println("<h3>Bomba d'Água (Receptor 1):</h3>");
            client.println("<button class='btn on' onclick=\"location.href='/BOMBA_ON'\">LIGAR</button>");
            client.println("<button class='btn off' onclick=\"location.href='/BOMBA_OFF'\">DESLIGAR</button>");
            client.println("<h3>Iluminação do Poste (Receptor 2):</h3>");
            client.println("<button class='btn on' onclick=\"location.href='/LUZ_ON'\">LIGAR</button>");
            client.println("<button class='btn off' onclick=\"location.href='/LUZ_OFF'\">DESLIGAR</button>");
            client.println("</body></html>");
            client.println();
            break;
          } else { currentLine = ""; }
        } else if (c != '\r') { currentLine += c; }
        
        // Comandos agora levam o prefixo do destino correto
        if (currentLine.endsWith("GET /BOMBA_ON")) { LoRa.beginPacket(); LoRa.print("BOMBA:ON"); LoRa.endPacket(); }
        if (currentLine.endsWith("GET /BOMBA_OFF")) { LoRa.beginPacket(); LoRa.print("BOMBA:OFF"); LoRa.endPacket(); }
        if (currentLine.endsWith("GET /LUZ_ON")) { LoRa.beginPacket(); LoRa.print("POSTE:ON"); LoRa.endPacket(); }
        if (currentLine.endsWith("GET /LUZ_OFF")) { LoRa.beginPacket(); LoRa.print("POSTE:OFF"); LoRa.endPacket(); }
      }
    }
    client.stop();
  }
}
