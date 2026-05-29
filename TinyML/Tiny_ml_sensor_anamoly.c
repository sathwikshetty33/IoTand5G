#include <Arduino.h>

#define LED_PIN   15
#define TEMP_PIN  26
#define GAS_PIN   27

// Tiny 2→4→3 hardcoded network (replace weights with your trained ones)
float relu(float x) { return x > 0 ? x : 0; }

void softmax(float* arr, int n) {
  float sum = 0;
  for (int i = 0; i < n; i++) arr[i] = exp(arr[i]);
  for (int i = 0; i < n; i++) sum += arr[i];
  for (int i = 0; i < n; i++) arr[i] /= sum;
}

void predict(float temp, float gas, float* out) {
  // Layer 1 weights (2 inputs → 4 hidden) — replace with your trained weights
  float w1[4][2] = {{1.2,-0.5},{-0.8,1.4},{0.6,0.9},{-1.1,-0.7}};
  float b1[4]    = {0.1, 0.2, -0.1, 0.3};

  // Layer 2 weights (4 hidden → 3 outputs)
  float w2[3][4] = {{0.9,-1.2,0.4,0.6},{-0.5,0.8,-0.3,1.1},{-0.8,0.5,0.9,-0.4}};
  float b2[3]    = {0.0, 0.1, -0.2};

  float h[4] = {0};
  for (int i = 0; i < 4; i++) {
    h[i] = b1[i] + w1[i][0] * temp + w1[i][1] * gas;
    h[i] = relu(h[i]);
  }
  for (int i = 0; i < 3; i++) {
    out[i] = b2[i];
    for (int j = 0; j < 4; j++) out[i] += w2[i][j] * h[j];
  }
  softmax(out, 3);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("[INFO] Ready.");
}

void loop() {
  float temp = analogRead(TEMP_PIN) / 1023.0f;
  float gas  = analogRead(GAS_PIN)  / 1023.0f;

  float output[3] = {0};
  predict(temp, gas, output);

  Serial.println("========== Prediction ==========");
  Serial.print("  Temp: "); Serial.print(temp, 3);
  Serial.print("  Gas: ");  Serial.println(gas, 3);
  Serial.print("  Normal  : "); Serial.println(output[0], 4);
  Serial.print("  Warning : "); Serial.println(output[1], 4);
  Serial.print("  Danger  : "); Serial.println(output[2], 4);

  if (output[2] > 0.6f) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("  >> DANGER DETECTED!");
  } else if (output[1] > 0.5f) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("  >> WARNING LEVEL");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("  >> NORMAL");
  }
  Serial.println("================================");
  delay(1000);
}