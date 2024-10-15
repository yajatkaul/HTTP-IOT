#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Define the pins for the TCS3200
#define S0 D1  // GPIO 5
#define S1 D2  // GPIO 4
#define S2 D3  // GPIO 0
#define S3 D4  // GPIO 2
#define sensorOut D5  // GPIO 14

// Variables to hold the frequency
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

const char* ssid = "WifiName";     
const char* password = "WifiPass";  

void setup() {
  // Set the pins as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  Serial.begin(9600);
}

void loop() {
  colorDetection();
}

void colorDetection(){
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  
  // Read green color
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Read blue color
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Print the results
  Serial.print("R = ");
  Serial.print(redFrequency);
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  Serial.print(" B = ");
  Serial.println(blueFrequency);

  if(redFrequency <= 110){
    sendGetRequest();
  }

  delay(500);
}

void sendGetRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;  // Create a WiFiClient object
    http.begin(client, "http://192.168.1.9:2000/");  // Use the new begin method

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
  delay(7000);
}