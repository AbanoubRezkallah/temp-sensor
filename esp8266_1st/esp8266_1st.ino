#include <Ubidots.h>  
#include <DHT.h>
#include <ESP8266WiFi.h>

byte counter = 0;

float hum = 0.0, temp_C = 0.0;

const byte DHT_PIN = D1;
const byte DHT_TYPE = 11;

DHT dht(DHT_PIN, DHT_TYPE);

#define TOKEN "BBFF-1nTpECa3iUvDUM8QwYfG0eJpGSde0K"
#define WIFISSID "Maged"
#define PASSWORD "Maged840"

Ubidots client(TOKEN);
 
void setup(){
 Serial.begin(115200);
 dht.begin();
  client.wifiConnect(WIFISSID,PASSWORD);
  client.setDebug(true);

  client.setDeviceType("NodeMCU-1");

}

void loop(){
  delay(2000);
  
  hum = dht.readHumidity();
  temp_C = dht.readTemperature();
  //temp_F = dht.readTemperature(true);

  if(isnan(hum) || isnan(temp_C)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  client.add("Temperature", temp_C);
  client.add("Humidity", hum);

  client.send();
  
}
