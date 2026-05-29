#define TRIG_PIN  PA0
#define ECHO_PIN  PA1
#define BUZZER_PIN PA2
#define LED_PIN   PA3

#define THRESHOLD_CM 50  

void setup() {
  Serial.begin(115200);
  while (!Serial);  

  pinMode(TRIG_PIN,   OUTPUT);
  pinMode(ECHO_PIN,   INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN,    OUTPUT);

  // Startup test — blink LED and beep once
  digitalWrite(LED_PIN,    HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(LED_PIN,    LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("=== Theft Detection System Ready ===");
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) return -1;  

  float distance = (duration * 0.0343) / 2.0;
  return distance;
}

void triggerAlarm() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN,    HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN,    LOW);
    delay(100);
  }
}

void loop() {
  float distance = getDistance();

  if (distance == -1) {
    Serial.println("[WARN] No echo — sensor out of range or disconnected");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN,    LOW);
  }
  else {
    Serial.print("[INFO] Distance: ");
    Serial.print(distance, 2);
    Serial.println(" cm");

    if (distance < THRESHOLD_CM) {
      Serial.println("[ALERT] Object detected! ALARM ON");
      triggerAlarm();
    } else {
      Serial.println("[OK] All clear");
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN,    LOW);
    }
  }

  delay(200);
}