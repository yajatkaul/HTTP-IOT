const int trigPin = 8;  // Pin connected to Trig of HC-SR04
const int echoPin = 7;  // Pin connected to Echo of HC-SR04
const int ledPin = 13;  // Pin connected to an LED (optional, for indication)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < 20) {
    digitalWrite(ledPin, HIGH);
    Serial.println("DETECTED");
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}
