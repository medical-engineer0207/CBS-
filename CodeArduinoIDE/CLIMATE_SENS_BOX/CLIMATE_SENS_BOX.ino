#include "arduino_secrets.h"
#include "thingProperties.h"

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <DHT_U.h>

#define ONE_WIRE_BUS 2 //GPIO pin ESP8266 01S board use for Temperature sensor DS18B20
#define DHTPIN 3//RX pin ESP8266 01S board for DHT22 sensor
#define DHTTYPE  DHT22//I use DHT22 Temperature/Humidity sensor
 
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);



void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(115200); 
  dht.begin();
  sensors.begin();
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(2500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
 
  sensors.requestTemperatures();

  airTemp = dht.readTemperature();

  airHumid= dht.readHumidity();

  soilTemp= sensors.getTempCByIndex(0);
  
  delay(2000);
}
