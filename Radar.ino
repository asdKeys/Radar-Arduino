#include <Servo.h>

Servo myServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 8;

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  // Sweep 0 → 180 with easing
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(8);  // slower = smoother
    readDistance();
  }

  delay(200);  // pause at the end to prevent jerk

  // Sweep 180 → 0 with easing
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(8);
    readDistance();
  }

  delay(200);  // pause at the end to prevent jerk
}

void readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    Serial.println("No echo");
    return;
  }

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
