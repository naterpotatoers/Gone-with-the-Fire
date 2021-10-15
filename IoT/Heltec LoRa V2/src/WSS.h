//***THIS IS FOR THE WEATHER STATION RECIEVER***

#include "DHTesp.h"
#include "heltec.h"
#include "LoRa.h"

String Packet;

void displayOnBoard(String LoraInfo) {
  
  Heltec.display->clear();
  // Prepare to display temperature C and F
  Heltec.display->drawString(0, 0, LoraInfo);
  // Display the readings
  Heltec.display->display();
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, false /*Serial Enable*/);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6, 1)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.println("Packet Received: ");

    // read packet
    while (LoRa.available()) {
      Packet = LoRa.readString();
      Serial.println(Packet);
      displayOnBoard(Packet);
    }
  }
}