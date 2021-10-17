//***THIS IS FOR THE WEATHER STATION SENDER***
#include "heltec.h"
#include "LoRa.h"
#include <TinyGPS++.h>
#include "SoftwareSerial.h"
#include "Adafruit_Sensor.h"
#include "DHT.h"

//Temperature Sensor
#define DHT11PIN 33
DHT dht(DHT11PIN, DHT11);
float currentTemp;
float currentHumidity;

//GPS
double Lon, Lat;
TinyGPSPlus gps;
static const int RXPin = 17, TXPin = 2;
static const uint32_t GPSBaud = 9600;
SoftwareSerial gpsSerial(RXPin, TXPin);

//Smoke Sensor
#define MQ2PIN (32)
float sensorValue;
bool Smoke = false;





void wakeGPS(){
    while (gpsSerial.available()){
    gps.encode(gpsSerial.read());
    if (gps.location.isUpdated()){

      Lat = gps.location.lat();
      Lon = gps.location.lng();

      Serial.print("Latitude: " + (String)Lat + "\nLongitude: " + (String)Lon);
      LoRa.print("Latitude: " + (String)Lat + "\nLongitude: " + (String)Lon);
    }
  }
}

void getSmoke(){
  pinMode(MQ2PIN, INPUT);
  sensorValue = analogRead(MQ2PIN);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  if(sensorValue > 750)
    {
      Smoke = true;
      Serial.println("Smoke detected!!!!");
    }else{
      Smoke = false;
    }
}


void CompileSensors(){

  Serial.println("Temperature: " + (String)currentTemp +  "°C");
  Serial.println("Temperature: " + (String)(1.8*currentTemp+32) + "°F");
  Serial.println("Humidity: " + (String)currentHumidity + "%\n");
  Serial.println("Latitude: " + (String)Lat + "\nLongitude: " + (String)Lon);
  Serial.println("Smoke Detection: " + (String)Smoke);

  //Sending the Data so it can be parsed by the reciever
  LoRa.println(1.8*currentTemp+32);
  LoRa.println(currentHumidity);
  LoRa.println(Lat);
  LoRa.println(Lon);
  LoRa.println(Smoke);

/*
  LoRa.println("Temperature: " + (String)currentTemp +  "°C");
  LoRa.println("Temperature: " + (String)(1.8*currentTemp+32) + "°F");
  LoRa.println("Humidity: " + (String)currentHumidity + "%");
  LoRa.println("Latitude: " + (String)Lat + "\nLongitude: " + (String)Lon);
  LoRa.println("Smoke Detection: " + (String)Smoke);
  */
}


void SendLoRaPacket(){
  LoRa.beginPacket();
  wakeGPS();
  getSmoke();
  CompileSensors();
  LoRa.endPacket();
}

/*
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
*/


void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  dht.begin();


  
  Serial.println("LoRa Sender starting...");

  if (!LoRa.begin(915E6, 1)) { // Set frequency to 433, 868 or 915MHz
    Serial.println("Could not find a valid LoRa transceiver, check pins used and wiring!");
  }
}
 
    
void loop()
{
  currentHumidity = dht.readHumidity();
  currentTemp = dht.readTemperature();

  SendLoRaPacket();
  
}