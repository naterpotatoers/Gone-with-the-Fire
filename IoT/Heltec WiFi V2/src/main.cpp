#include "heltec.h"
#include "LoRa.h"
#include "HTTPClient.h"
#include "WiFiMulti.h"
#include "ArduinoJson.h"
#include "Adafruit_Sensor.h"

String Packet;


const char *AP_SSID = "kingdom2";
const char *AP_PWD = "22039622";

String id, Temp, Humid, Lat, Lon, Smoke;
  
WiFiMulti wifiMulti;


void displayOnBoard(String LoraInfo) {
  
  Heltec.display->clear();
  // Prepare to display temperature C and F
  Heltec.display->drawString(0, 0, LoraInfo);
  // Display the readings
  Heltec.display->display();
}

void LoraRecieve(){
    // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.println("Packet Received: ");

    if(LoRa.available()){
    id = "heltecNachooo";
    Temp = LoRa.readString();
    Humid = LoRa.readString();
    Lat = LoRa.readString();
    Lon = LoRa.readString();
    Smoke  = LoRa.readString();
    delay(3000);
  }

/*
    // read packet
    while (LoRa.available()) {
      Packet = LoRa.readString();
      Serial.println(Packet);
      displayOnBoard(Packet);
    }
    */
  }
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
    //


    doc["id"] = id;
    doc["temperature"] = Temp;
    doc["humidity"] = Humid;
    doc["longitude"] = Lat;
    doc["latitude"] = Lon;
    doc["smoke"] = Smoke;
    delay(5000);


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