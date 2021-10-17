#include "heltec.h"
#include "LoRa.h"
#include "HTTPClient.h"
#include "WiFiMulti.h"
#include "ArduinoJson.h"
#include "Adafruit_Sensor.h"

#include <string_view>



const char *AP_SSID = "kingdom2";
const char *AP_PWD = "22039622";

String Packet;
String id, Temp, Humid, Lat, Lon, Smoke;

String pack[5];
  
WiFiMulti wifiMulti;

void LoraRecieve(){
    // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
  }
    // received a packet
    

    if(LoRa.available()){
      Serial.println("Packet Received: ");
    Packet = LoRa.readString();
  }
  Serial.println(Packet);

  for(int i=0; i<5; i++){
      substr(Packet.find("\n"));
      Packet = substr(Packet.find("\n"));
      pack[i] = Packet;
  }

  delay(10000);
}

void postDataToServer() {
 
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  if (wifiMulti.run() == WL_CONNECTED) {
     
    HTTPClient http;
     
    http.begin("http://20.69.111.104:5000/iot");
    http.addHeader("Content-Type", "application/json");
     
    StaticJsonDocument<200> doc;
    // Add values in the document

//char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    doc["name"] = "ESP32";
    doc["temperature"] = pack[0];
    doc["humidity"] = pack[1];
    doc["longitude"] = pack[2];
    doc["latitude"] = pack[3];
    doc["smoke"] = pack[4];

    //doc["time"] = 1351824120;
   
    // Add an array.
    //
    //JsonArray data = doc.createNestedArray("FireData");
    //data.add("Info");
     
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);
      Serial.println(response);
     
    }
    else {
     
      //Serial.printf("Error occurred while sending HTTP POST: %s\n", http.errorToString(statusCode).c_str());
       
    }
     
  }
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

  wifiMulti.addAP(AP_SSID, AP_PWD);

}

void loop() {
  LoraRecieve();
  postDataToServer();
}