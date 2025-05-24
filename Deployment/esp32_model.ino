#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <TensorFlowLite.h>
#include "M2_Dhrubo.h"

#define BUZZER_PIN 25
#define LASER_PIN 26
#define BUTTON_PIN 27
#define VIBRATION_PIN 14
#define STANDING_TIME 30000
#define PULSE_SPIKE_THRESHOLD 20

char auth[] = "AuthToken";
char ssid[] = "WiFiSSID";
char pass[] = "WiFiPassword";

MAX30105 particleSensor;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

unsigned long standingStartTime = 0;
bool isStanding = false;
bool alertTriggered = false;
bool modelInitialized = false;

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LASER_PIN, OUTPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    while (1);
  }
  
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

  Blynk.begin(auth, ssid, pass);
  initializeModel();
}

void loop() {
  Blynk.run();
  
  if(digitalRead(BUTTON_PIN) == LOW) {
    shutdownSystem();
    return;
  }

  float currentAcc[3];
  readAccelerometer(currentAcc[0], currentAcc[1], currentAcc[2]);
  
  int movementStatus = classifyMovement(currentAcc);
  
  if(movementStatus == 1) {
    isStanding = false;
    alertTriggered = false;
    digitalWrite(LASER_PIN, LOW);
    digitalWrite(VIBRATION_PIN, LOW);
    Blynk.virtualWrite(V0, "Moving");
  } else {
    if(!isStanding) {
      standingStartTime = millis();
      isStanding = true;
    }
    
    Blynk.virtualWrite(V0, "Standing");
    Blynk.virtualWrite(V1, (millis() - standingStartTime) / 1000);
    
    if(millis() - standingStartTime > STANDING_TIME) {
      monitorPulseOximeter();
    }
  }

  if(alertTriggered) {
    triggerAlert();
  }

  delay(10);
}

void initializeModel() {
  const tflite::Model* model = tflite::GetModel(model_data);
  static tflite::MicroErrorReporter micro_error_reporter;
  static tflite::MicroInterpreter interpreter(model, tensor_arena, kTensorArenaSize, &micro_error_reporter);
  interpreter.AllocateTensors();
  modelInitialized = true;
}

int classifyMovement(float accData[3]) {
  if(!modelInitialized) return 0;
  
  static tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = interpreter->input(0);
  
  for(int i = 0; i < 3; i++) {
    input->data.f[i] = accData[i];
  }
  
  interpreter->Invoke();
  TfLiteTensor* output = interpreter->output(0);
  
  return output->data.f[0] > output->data.f[1] ? 0 : 1;
}

void readAccelerometer(float &x, float &y, float &z) {
  x = random(90, 110) / 100.0;
  y = random(90, 110) / 100.0;
  z = random(90, 110) / 100.0;
}

void monitorPulseOximeter() {
  long irValue = particleSensor.getIR();
  
  if (checkForBeat(irValue)) {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  Blynk.virtualWrite(V2, beatAvg);

  if (beatAvg > (beatAvg + PULSE_SPIKE_THRESHOLD)) {
    alertTriggered = true;
  }

  if (irValue < 50000) {
    Blynk.virtualWrite(V3, "No finger detected");
  }
}

void triggerAlert() {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LASER_PIN, HIGH);
  digitalWrite(VIBRATION_PIN, HIGH);
  
  while(SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }
  
  Blynk.virtualWrite(V3, "ALERT: Pulse Spike");
  
  if(gps.location.isValid()) {
    Blynk.virtualWrite(V4, gps.location.lat(), 6);
    Blynk.virtualWrite(V5, gps.location.lng(), 6);
    String location = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    Blynk.virtualWrite(V6, location);
  } else {
    Blynk.virtualWrite(V6, "GPS not available");
  }
  
  Serial.print("ALERT! Pulse spike detected at ");
  if(gps.location.isValid()) {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Lng: ");
    Serial.print(gps.location.lng(), 6);
  }
  Serial.println();
}

void shutdownSystem() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LASER_PIN, LOW);
  digitalWrite(VIBRATION_PIN, LOW);
  
  Blynk.virtualWrite(V3, "System Shutdown");
  
  while(digitalRead(BUTTON_PIN) == LOW) {
    delay(100);
  }
}
