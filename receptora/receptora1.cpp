// Limeira, SP - 27/06/2026: (Placa Exclusiva n,a Bomba d'Água)
// Esta placa usará o módulo de 1 canal conectado ao pino 13 para acionar a contatora da bomba. 
// Ela vai ignorar qualquer mensagem que comece com "POSTE:"
//

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306Wire.h"

#define SS      18
#define RST     14
#define DIO0    26
#define BAND    915E6

const int pinoBomba = 13; // Pino conectado ao relé da bomba
SSD1306Wire display(0x3c, 4, 15);

void setup() {
  Serial.begin(115200);
  pinMode(pinoBomba, OUTPUT);
  digitalWrite(pinoBomba, HIGH); // Inicia Desligado

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); delay(50); digitalWrite(16, HIGH);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) { while (1); }
  
  display.drawString(0, 0, "RECEPTOR 1: BOMBA");
  display.drawString(0, 15, "Aguardando rede...");
  display.display();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String comando = "";
    while (LoRa.available()) { comando += (char)LoRa.read(); }
    
    // Filtra e aceita apenas comandos direcionados à BOMBA
    if (comando == "BOMBA:ON") {
      digitalWrite(pinoBomba, LOW); // Liga o Relé
      display.clear();
      display.drawString(0, 0, "Status da Bomba:");
      display.drawString(0, 20, "LIGADA");
      display.display();
    } 
    else if (comando == "BOMBA:OFF") {
      digitalWrite(pinoBomba, HIGH); // Desliga o Relé
      display.clear();
      display.drawString(0, 0, "Status da Bomba:");
      display.drawString(0, 20, "DESLIGADA");
      display.display();
    }
  }
}
