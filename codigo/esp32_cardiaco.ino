#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ===============================
// CONFIGURAÇÕES DE REDE
// ===============================
const char* ssid = "SUA_REDE_WIFI";
const char* password = "SUA_SENHA_WIFI";

// ===============================
// CONFIGURAÇÃO DO MQTT
// ===============================
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* topico_bpm = "cardiaco/bpm";
const char* topico_temp = "cardiaco/temperatura";
const char* topico_status = "cardiaco/status";
const char* topico_comando = "cardiaco/comando";
const char* topico_rtt = "cardiaco/rtt";

// ===============================
// PINOS DO HARDWARE
// ===============================
#define PINO_AD8232 34       // ECG
#define PINO_DS18B20 4       // Temperatura corporal
#define PINO_LED 2           // LED
#define PINO_BUZZER 15       // Alarme

OneWire oneWire(PINO_DS18B20);
DallasTemperature sensors(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long ultimoEnvio = 0;
unsigned long ultimoPico = 0;
bool picoAnterior = false;
float bpm = 0;
int threshold = 2000; // Ajustável

// =========================================================
// CALLBACK MQTT (recebe comandos)
// =========================================================
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)payload[i];

  if (String(topic) == topico_comando) {
    
    if (msg == "LED_ON") digitalWrite(PINO_LED, HIGH);
    if (msg == "LED_OFF") digitalWrite(PINO_LED, LOW);

    if (msg == "BEEP") {
      tone(PINO_BUZZER, 1800, 300);
    }

    if (msg.startsWith("CMD:")) {
      unsigned long ts_user = msg.substring(4).toInt();
      unsigned long ts_device = millis();

      String resposta = "{\"client_ts\":"+String(ts_user)+",\"recv_ts\":"+String(ts_device)+"}";
      client.publish(topico_rtt, resposta.c_str());
    }
  }
}

// =========================================================
// CONECTA AO WI-FI
// =========================================================
void conectaWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(300);
}

// =========================================================
// CONECTA AO MQTT
// =========================================================
void conectaMQTT() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    String id = "ESP32_" + String(random(9999));
    client.connect(id.c_str());
    delay(500);
  }

  client.subscribe(topico_comando);
}

// =========================================================
// DETECTA BATIMENTO CARDÍACO (BPM)
// =========================================================
void detectarECG() {
  int leitura = analogRead(PINO_AD8232);
  bool picoAtual = leitura > threshold;
  unsigned long agora = millis();

  if (picoAtual && !picoAnterior) {
    unsigned long intervalo = agora - ultimoPico;
    if (intervalo > 250 && ultimoPico != 0) {
      bpm = 60000.0 / intervalo;

      if (bpm < 50 || bpm > 120) {
        tone(PINO_BUZZER, 1500, 200);
        digitalWrite(PINO_LED, HIGH);
      } else {
        digitalWrite(PINO_LED, LOW);
      }
    }
    ultimoPico = agora;
  }

  picoAnterior = picoAtual;
}

// =========================================================
// SETUP
// =========================================================
void setup() {
  Serial.begin(115200);

  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);

  sensors.begin();
  conectaWiFi();
  conectaMQTT();
}

// =========================================================
// LOOP
// =========================================================
void loop() {
  if (!client.connected()) conectaMQTT();
  client.loop();

  detectarECG();

  if (millis() - ultimoEnvio > 4000) {
    ultimoEnvio = millis();
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);

    String payload = "{";
    payload += "\"bpm\":"+String(bpm,1)+",";
    payload += "\"temp\":"+String(temp,1)+",";
    payload += "\"ts\":"+String(millis());
    payload += "}";

    client.publish(topico_bpm, payload.c_str());
    client.publish(topico_temp, payload.c_str());
  }
}
