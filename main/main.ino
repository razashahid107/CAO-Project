#include "DHT.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "WiFi.h"

#define LED 2
#define DHTPIN 15
DHT dht(DHTPIN, DHT11);
float heat;
float humidity;
float temperature;

const char* SSID = "gg";
const char* PASS = "hello123";

AsyncWebServer server(80);

//***************************************************************************************************************************************************************

String readTemp() {
  temperature = dht.readTemperature();
  while (isnan(temperature)) {
    temperature = dht.readTemperature();
  }
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
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
      background-image: url('https://www.almanac.com/sites/default/files/image_nodes/rainbow-weather.jpg');
    }
    h1 {
      font-size: 3.0rem;
      color: black;
    }
    p {
      font-size: 2.0rem;
    }

    body {
      max-width: 600px; 
      margin:0px auto; 
      padding-bottom: 25px;
    }
  </style>
</head>
<body>
  <h1>ESP Weather Station</h1>
  <p>
    <span>Temperature:</span> 
    <span id="temp">%TEMPERATURE%</span>
  </p>
  <p>
    <span>Humidity:</span> 
    <span id="humidity">%HUMIDITY%</span>
  </p>
  <p>
    <span>Heat Index:</span> 
    <span id="heat">%HEAT%</span>
  </p>
  <h1 style="color: rgb(159, 10, 192);">
    Happy Weather Predicting
  </h1>
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
    Serial.print(".");
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

}
