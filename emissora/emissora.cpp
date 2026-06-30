// Limeira, SP - Atualizado em 30/06/2026: (Placa na Casa do Sítio - Emissor Central)
#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <HTTPClient.h> // Biblioteca necessária para enviar comandos ao ESP-01
#include "SSD1306Wire.h"

#define SS      18
#define RST     14
#define DIO0    26
#define BAND    915E6

const char* ssid     = "mikrotik";
const char* password = "Linux123pb";

// IMPORTANTE: Insira aqui o IP definitivo que o seu ESP-01 vai pegar no Wi-Fi
const String IP_DO_ESP01 = "11.22.33.44"; 

WiFiServer server(80);
SSD1306Wire display(0x3c, 4, 15);

// Função auxiliar para disparar o comando Wi-Fi direto para o IP do ESP-01
void enviarComandoEsp01(String comando) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://" + IP_DO_ESP01 + comando;
    http.begin(url);
    int httpCode = http.GET();
    http.end();
  }
}

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
            client.println("<style>body{font-family:Arial; text-align:center;} .btn{padding:15px; font-size:20px; margin:5px; cursor:pointer; color:white; border:none; border-radius:5px;} .on{background-color:green;} .off{background-color:red;} hr{margin:20px 0; border:0; border-top:1px solid #ccc;}</style></head>");
            client.println("<body><h1>Controle Integrado - Sitio</h1>");
            
            // Comandos Existentes via LoRa
            client.println("<h3>Bomba d'Água (Receptor LoRa 1):</h3>");
            client.println("<button class='btn on' onclick=\"location.href='/BOMBA_ON'\">LIGAR</button>");
            client.println("<button class='btn off' onclick=\"location.href='/BOMBA_OFF'\">DESLIGAR</button>");
            
            client.println("<h3>Iluminação do Poste (Receptor LoRa 2):</h3>");
            client.println("<button class='btn on' onclick=\"location.href='/LUZ_ON'\">LIGAR</button>");
            client.println("<button class='btn off' onclick=\"location.href='/LUZ_OFF'\">DESLIGAR</button>");
            
            client.println("<hr>");
            
            // Novos controles locais via Wi-Fi (ESP-01 + Relê Duplo LCUS-2)
            client.println("<h3>Refletor Externo 1 (ESP-01 Wi-Fi):</h3>");
            client.println("<button class='btn on' onclick=\"location.href='/REFLETOR1_ON'\">LIGAR</button>");
            client.println("<button class='btn off' onclick=\"location.href='/REFLETOR1_OFF'\">DESLIGAR</button>");
            
            client.println("<h3>Refletor Externo 2 (ESP-01 Wi-Fi):</h3>");
            client.println("<button class='btn on' onclick=\"location.href='/REFLETOR2_ON'\">LIGAR</button>");
            client.println("<button class='btn off' onclick=\"location.href='/REFLETOR2_OFF'\">DESLIGAR</button>");
            
            client.println("</body></html>");
            client.println();
            break;
          } else { currentLine = ""; }
        } else if (c != '\r') { currentLine += c; }
        
        // Processamento dos comandos LoRa originais
        if (currentLine.endsWith("GET /BOMBA_ON")) { LoRa.beginPacket(); LoRa.print("BOMBA:ON"); LoRa.endPacket(); }
        if (currentLine.endsWith("GET /BOMBA_OFF")) { LoRa.beginPacket(); LoRa.print("BOMBA:OFF"); LoRa.endPacket(); }
        if (currentLine.endsWith("GET /LUZ_ON")) { LoRa.beginPacket(); LoRa.print("POSTE:ON"); LoRa.endPacket(); }
        if (currentLine.endsWith("GET /LUZ_OFF")) { LoRa.beginPacket(); LoRa.print("POSTE:OFF"); LoRa.endPacket(); }
        
        // Processamento dos novos comandos Wi-Fi direcionados ao ESP-01
        if (currentLine.endsWith("GET /REFLETOR1_ON"))  { enviarComandoEsp01("/R1_ON"); }
        if (currentLine.endsWith("GET /REFLETOR1_OFF")) { enviarComandoEsp01("/R1_OFF"); }
        if (currentLine.endsWith("GET /REFLETOR2_ON"))  { enviarComandoEsp01("/R2_ON"); }
        if (currentLine.endsWith("GET /REFLETOR2_OFF")) { enviarComandoEsp01("/R2_OFF"); }
      }
    }
    client.stop();
  }
}
