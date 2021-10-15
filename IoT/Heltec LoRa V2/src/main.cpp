//***THIS IS FOR THE WEATHER STATION SENDER***

#include "DHTesp.h"
#include "heltec.h"
#include "LoRa.h"

#include <TinyGPS++.h>
#include <SoftwareSerial.h>


DHTesp dht;
float currentTemp;
float currentHumidity;
TinyGPSPlus gps;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
SoftwareSerial ss(RXPin, TXPin);


void GPSCheck(){
    while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
}

 
void displayOnBoard() {
   
  String CtemperatureDisplay ="Temperature: " + (String)currentTemp +  "°C";
  String FtemperatureDisplay ="Temperature: " + (String)(1.8*currentTemp+32) + "°F";
  String humidityDisplay = "Humidity: " + (String)currentHumidity + "%";
 
  Heltec.display->clear();
  // Prepare to display temperature C and F
  Heltec.display->drawString(0, 0, CtemperatureDisplay);
  Heltec.display->drawString(0, 12, FtemperatureDisplay);
  // Prepare to display humidity
  Heltec.display->drawString(0, 24, humidityDisplay);
  // Display the readings
  Heltec.display->display();
}

void SendLoRaPacket(){
  LoRa.beginPacket();
  LoRa.print("Temperature: " + (String)currentTemp +  "°C");
  LoRa.print("Temperature: " + (String)(1.8*currentTemp+32) + "°F");
  LoRa.print("Humidity: " + (String)currentHumidity + "%");
  LoRa.endPacket();
}


void setup()
{

  Serial.begin(9600);
  Serial.println("LoRa Sender starting...");

    if (!LoRa.begin(915E6, 1)) { // Set frequency to 433, 868 or 915MHz
    Serial.println("Could not find a valid LoRa transceiver, check pins used and wiring!");
    delay(1000);
  }
 
  dht.setup(33, DHTesp::DHT11);
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, false /*Serial Enable*/);
}
 
    
void loop()
{
  currentTemp = dht.getTemperature();
  currentHumidity = dht.getHumidity();
  displayOnBoard();
  SendLoRaPacket();
  Serial.println("Temp: " + (String)currentTemp + "     Humidity: " + (String)currentHumidity);
  GPSCheck();
  delay(10000);
}


