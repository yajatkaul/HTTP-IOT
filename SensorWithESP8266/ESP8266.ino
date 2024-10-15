#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace with your network credentials
const char* ssid = "WifiName";     
const char* password = "WifiPass";

// Pins for HC-SR04
const int trigPin = D1;  // GPIO5
const int echoPin = D2;  // GPIO4

void setup() {
  Serial.begin(9600); // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  long distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Check if the distance is less than 20 cm
  if (distance < 20) {
    sendGetRequest();
    delay(6000);
  }
  
  delay(500);
}

void sendGetRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;  // Create a WiFiClient object
    http.begin(client, "http://192.168.1.8:2000/");  // Use the new begin method

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("HTTP Code: ");
      Serial.println(httpCode);
      Serial.println("Payload:");
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
