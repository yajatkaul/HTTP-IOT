#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "WifiName";     
const char* password = "WifiPass";  

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n');
    receivedData.trim();  // Remove any leading/trailing whitespace

    if (receivedData == "DETECTED") {
      sendGetRequest();
    }
  }
}

void sendGetRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;  // Create a WiFiClient object
    http.begin(client, "http://192.168.1.10:2000/");  // Use the new begin method

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}