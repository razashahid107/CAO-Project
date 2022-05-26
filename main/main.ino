#include "DHT.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "WiFi.h"

#define LED 2
#define DHTPIN 4
DHT dht(DHTPIN, DHT11);
float heat;
float humidity;
float temperature;

const char* SSID = "Ali";
const char* PASS = "554151955";

AsyncWebServer server(80);

//***************************************************************************************************************************************************************

String readTemp() {
  temperature = dht.readTemperature();
  while (isnan(temperature)) {
    temperature = dht.readTemperature();
  }  
  return String(temperature);
}

String readHumidity() {
 humidity = dht.readHumidity();
 while (isnan(humidity)) {
    humidity = dht.readHumidity();
  }  
 return String(humidity);
}

String readHeat() {
  heat = dht.computeHeatIndex(temperature, humidity, false);
  return String(heat);
}




//***************************************************************************************************************************************************************


//*******************************************************************************************************************************************
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {
      font-family: Arial; 
      display: inline-block; 
      text-align: center;
    }
    h2 {
      font-size: 3.0rem;
    }
    p {
      font-size: 3.0rem;
    }
    body {
      max-width: 600px; 
      margin:0px auto; 
      padding-bottom: 25px;
    }
    .switch {
      position: relative; 
      display: inline-block; 
      width: 120px; 
      height: 68px;
    } 
    .switch input {
      display: none;
    }
    .slider {
      position: absolute; 
      top: 0; 
      left: 0; 
      right: 0; 
      bottom: 0; 
      background-color: #ccc; 
      border-radius: 6px;
    }
    .slider:before {
      position: absolute; 
      content: ""; 
      height: 52px; 
      width: 52px; 
      left: 8px; 
      bottom: 8px; 
      background-color: #fff; 
      -webkit-transition: .4s; 
      transition: .4s; 
      border-radius: 3px
    }
    input:checked+.slider {
      background-color: #b30000;
    }
    input:checked+.slider:before {
      -webkit-transform: translateX(52px); 
      -ms-transform: translateX(52px); 
      transform: translateX(52px)
    }
  </style>
</head>
<body>
  <h1>ESP Web Server</h1>
  <p>
    <span>Temperature</span> 
    <span id="temp">%TEMPERATURE%</span>
  </p>
  <p>
    <span>Humidity</span> 
    <span id="humidity">%HUMIDITY%</span>
  </p>
  <p>
    <span>Heat Index</span> 
    <span id="heat">%HEAT%</span>
  </p>
  <script>
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("temp").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/temp", true);
      xhttp.send();
    }, 2000 ) ;

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("humidity").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/humidity", true);
      xhttp.send();
    }, 2000 ) ;

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("heat").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/heat", true);
      xhttp.send();
    }, 2000 ) ;

    </script>
</body>
</html>)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  if (var == "TEMPERATURE"){
    return readTemp();
  }
  else if (var == "HUMIDITY"){
    return readHumidity();
  }
  else if (var == "HEAT"){
    return readHeat();
  }
  return String();
}

//*******************************************************************************************************************************************


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
  pinMode(LED,OUTPUT);
  dht.begin();
  delay(1500);

 WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("Connected to WiFi");
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readHumidity().c_str());
  });
  server.on("/heat", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readHeat().c_str());
  });

  // Start server
  server.begin();


}

void loop() {

  delay(500);
//
//  humidity = dht.readHumidity();
//  temperature = dht.readTemperature();
//  // Read temperature as Fahrenheit (isFahrenheit = true)
//  float f = dht.readTemperature(true);
//
//  // Check if any reads failed and exit early (to try again).
//  if (isnan(humidity) || isnan(temperature) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
//
//  // Compute heat index in Fahrenheit (the default)
//  // float hif = dht.computeHeatIndex(f, h);
//  // Compute heat index in Celsius (isFahreheit = false)
//  heat = dht.computeHeatIndex(temperature, humidity, false);
}
