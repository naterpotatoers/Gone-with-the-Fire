//***THIS IS FOR THE WEATHER STATION RECIEVER***
#include "LoRa.h"
#include "HTTPClient.h"
#include "WiFiMulti.h"
#include "ArduinoJson.h"

 
const char *AP_SSID = "kingdom2";
const char *AP_PWD = "22039622";
  
WiFiMulti wifiMulti;

void LoRaRecieve(){
    // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("LoRa Packet Recieved");
    // read packet
    while (LoRa.available()) {
      Serial.print((String)LoRa.read());
    }
  }
}

void postDataToServer() {
 
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  if (wifiMulti.run() == WL_CONNECTED) {
     
    HTTPClient http;
     
    http.begin("http://20.38.169.98:5000/");
    http.addHeader("Content-Type", "application/json");
     
    StaticJsonDocument<200> doc;
    // Add values in the document
    //
    doc["sensor"] = "gps";
    //doc["time"] = 1351824120;
   
    // Add an array.
    //
    JsonArray data = doc.createNestedArray("FireData");
    data.add("Info");
     
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

/*
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  */

  delay(4000);
  wifiMulti.addAP(AP_SSID, AP_PWD);
  
}
 
void loop() {
  Serial.println("Sending information to server...");
  //LoRaRecieve();
  postDataToServer();
  delay(10000);
}
 
