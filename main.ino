#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Airtrik.h>

char* mykey = "__APP_KEY__";
String ssid = "WIFI__NAME";
String pass = "WIFI__PASSWORD";

// DHT Code

#include <dht.h>
dht DHT;
#define DHT11_PIN 2




void onReceive(char* deviceId, byte* message, unsigned int length){
  int i;
  for(i=0; i < length; i++){
    Serial.print(char(message[i]));
  }
  Serial.println("");
  Serial.println(deviceId);
  
}

Airtrik iot;

void setup() {
  iot.connect(ssid, pass, mykey);
  iot.subscribe("temperature");
  iot.subscribe("humidity");
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  
  char temp[50];
  char humid[50];
  
  const char* deviceId = "temperature";
  String msg = String(DHT.temperature, 2);
  msg.toCharArray(temp, 50);
  iot.send(deviceId, temp);

  deviceId = "humidity";
  msg = String(DHT.humidity, 2);
  msg.toCharArray(humid, 50);
  iot.send(deviceId, humid);

  iot.loop();
  delay(1000);
}
