// Limeira, SP - 27/06/2026: (Placa Exclusiva no Poste de Iluminação)
// Esta placa usará a outra placa de relés conectada ao pino 13 para acionar a lâmpada de 110V. 
// Ela ignorará mensagens da "BOMBA:".
//

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306Wire.h"

#define SS      18
#define RST     14
#define DIO0    26
#define BAND    915E6

const int pinoLuz = 13; // Pino conectado ao relé da iluminação
SSD1306Wire display(0x3c, 4, 15);

void setup() {
  Serial.begin(115200);
  pinMode(pinoLuz, OUTPUT);
  digitalWrite(pinoLuz, HIGH); // Inicia Desligado

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); delay(50); digitalWrite(16, HIGH);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) { while (1); }
  
  display.drawString(0, 0, "RECEPTOR 2: ILUMINAÇÃO");
  display.drawString(0, 15, "Aguardando rede...");
  display.display();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String comando = "";
    while (LoRa.available()) { comando += (char)LoRa.read(); }
    
    // Filtra e aceita apenas comandos direcionados ao POSTE
    if (comando == "POSTE:ON") {
      digitalWrite(pinoLuz, LOW); // Liga o Relé
      display.clear();
      display.drawString(0, 0, "Status do Poste:");
      display.drawString(0, 20, "ILUMINAÇÃO LIGADA");
      display.display();
    } 
    else if (comando == "POSTE:OFF") {
      digitalWrite(pinoLuz, HIGH); // Desliga o Relé
      display.clear();
      display.drawString(0, 0, "Status do Poste:");
      display.drawString(0, 20, "ILUMINAÇÃO DESLIGADA");
      display.display();
    }
  }
}
