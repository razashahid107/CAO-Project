///*
// * Rui Santos 
// * Complete Project Details https://randomnerdtutorials.com
// */
//
//// Load required libraries
//#include <WiFi.h>
//#include "SD.h"
//#include "DHT.h"
//#include <Wire.h>
//#include <Adafruit_BMP085.h>
//
//// Replace with your network credentials
//const char* ssid     = "gg";
//const char* password = "hello123";
//
//// uncomment one of the lines below for whatever DHT sensor type you're using
//#define DHTTYPE DHT11   // DHT 11
////#define DHTTYPE DHT21   // DHT 21 (AM2301)
////#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//
//// GPIO the DHT is connected to
//const int DHTPin = 15;
////intialize DHT sensor
//DHT dht(DHTPin, DHTTYPE);
//
//// create a bmp object
//Adafruit_BMP085 bmp;
//
//// Web page file stored on the SD card
//File webFile; 
//
//// Set potentiometer GPIO
//const int potPin = 32;
//
//// IMPORTANT: At the moment, GPIO 4 doesn't work as an ADC when using the Wi-Fi library
//// This is a limitation of this shield, but you can use another GPIO to get the LDR readings
//const int LDRPin = 4;
//
//// variables to store temperature and humidity
//float tempC;
//float tempF;
//float humi;
//
//// Variable to store the HTTP request
//String header;
//
//// Set web server port number to 80
//WiFiServer server(80);













// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 15     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();

//   if (!bmp.begin()){
//    Serial.println("Could not find BMP180 or BMP085 sensor");
//    while (1) {}
//  }
//
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, password);
//
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  // Print local IP address and start web server
//  Serial.println("");
//  Serial.println("WiFi connected.");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//  server.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
