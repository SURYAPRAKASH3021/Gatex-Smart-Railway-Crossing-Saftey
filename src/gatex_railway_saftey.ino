#include <ESP32Servo.h>

// Gatex - Educational railway crossing model
// Not for real railway deployment.

const int TRAIN_PIN = 18;    // Active HIGH simulated train input
const int TRIG_PIN  = 5;
const int ECHO_PIN  = 19;
const int SERVO_PIN = 13;
const int LED_PIN   = 2;
const int BUZZER_PIN = 4;

const int GATE_OPEN = 0;
const int GATE_CLOSED = 90;
const float OBSTACLE_LIMIT_CM = 20.0;

Servo gateServo;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1.0;
  return duration * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRAIN_PIN, INPUT_PULLDOWN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_OPEN);

  Serial.println("Gatex model started");
}

void loop() {
  bool trainDetected = digitalRead(TRAIN_PIN) == HIGH;
  float distance = readDistanceCm();

  bool obstacleDetected =
      distance >= 0 && distance < OBSTACLE_LIMIT_CM;

  if (trainDetected) {
    gateServo.write(GATE_CLOSED);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, obstacleDetected ? HIGH : LOW);

    Serial.println(obstacleDetected
      ? "WARNING: Obstacle detected in model zone"
      : "Train input active: model gate closed");
  } else {
    gateServo.write(GATE_OPEN);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("No train input: model gate open");
  }

  delay(200);
}
