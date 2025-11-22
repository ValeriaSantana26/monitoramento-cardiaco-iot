/*
  monitor.ino
  ESP32 + AD8232 (ECG) + DS18B20 (temperatura)
  Comunicação via MQTT - HiveMQ Broker
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// -------- CONFIG Wi-Fi --------
const char* ssid = "SEU_WIFI";        // coloque seu Wi-Fi
const char* password = "SENHA_WIFI";  // coloque a senha

// -------- MQTT CONFIG --------
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* topic_ecg   = "valeria/ecg";
const char* topic_temp  = "valeria/temperatura";
const char* topic_alert = "valeria/alerta";

// -------- PINOS --------
const int pinAD8232 = 34;  // ECG (AD8232)
const int pinDS18B20 = 4;  // Temperatura
const int pinLED = 2;      // LED
const int pinBuzzer = 15;  // buzzer

// OneWire + DallasTemp
OneWire oneWire(pinDS18B20);
DallasTemperature sensors(&oneWire);

// MQTT / WiFi
WiFiClient espClient;
PubSubClient client(espClient);


// SIMULAÇÃO DE BPM (contenção didática)
int readBPM() {
  int threshold = 1800;
  int beats = 0;

  for (int i = 0; i < 200; i++) {
    int value = analogRead(pinAD8232);
    if (value > threshold) beats++;
    delay(2);
  }

  int bpm = beats * 3;
  if (bpm < 30) bpm = 0;
  return bpm;
}


// Callback MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;

  for (int i = 0; i < length; i++) msg += (char)payload[i];

  if (msg == "ALERTA") {
    digitalWrite(pinLED, HIGH);
    tone(pinBuzzer, 2000, 400);
    delay(400);
    digitalWrite(pinLED, LOW);
  }
}


// Reconexão MQTT
void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_Valeria")) {
      client.subscribe(topic_alert);
    } else {
      delay(1000);
    }
  }
}


void setup() {
  Serial.begin(115200);

  pinMode(pinLED, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  sensors.begin();
}


void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int bpm = readBPM();
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  char msg[50];

  sprintf(msg, "{\"bpm\": %d}", bpm);
  client.publish(topic_ecg, msg);

  sprintf(msg, "{\"temperatura\": %.2f}", temp);
  client.publish(topic_temp, msg);

  if (bpm > 120 || temp > 38.0) {
    client.publish(topic_alert, "ALERTA");
  }

  delay(2000);
}
