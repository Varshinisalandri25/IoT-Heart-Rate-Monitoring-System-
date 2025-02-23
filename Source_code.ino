#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PulseSensorPlayground.h>

// Your WiFi credentials.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

// Your Blynk auth token
char auth[] = "YourAuthToken";

// Pulse Sensor
const int PulseWire = A0;  // Pulse Sensor purple wire connected to analog pin 0
int Threshold = 550;       // Determine which Signal to "count as a beat" and which to ignore

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  // Configure the PulseSensor object
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  // Start the PulseSensor
  if (pulseSensor.begin()) {
    Serial.println("PulseSensor started successfully");
  }
}

void loop() {
  Blynk.run();
  
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calculates BPM
  if (pulseSensor.sawStartOfBeat()) {           // Triggered when a beat is detected
    Blynk.virtualWrite(V1, myBPM);              // Send BPM to Blyn
Serial.println("SUCCESS");
  }

  // Register a callback for the beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  Blynk.run();
  pox.update();

  // Make sure to call update as fast as possible
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    tsLastReport = millis();

    // Report BPM and SpO2 to the Serial Monitor
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");

    // Send the values to the Blynk app
    Blynk.virtualWrite(V1, pox.getHeartRate());
    Blynk.virtualWrite(V2, pox.getSpO2());
  }
}
