#include <WiFi.h>
#include <PubSubClient.h>          // Para MQTT
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

// ==================== Configurações de Wi-Fi e MQTT ====================
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// ==================== Pinos ====================
#define PPG_PIN 34      // Sensor PPG
#define GSR_PIN 35      // Sensor GSR
#define SCL_PIN 26      // OLED
#define SDA_PIN 25      // OLED
#define BUZZER_PIN 4    // Buzzer

#define WINDOW_SIZE 5
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

unsigned long previousMillis = 0;
const long interval = 1000; // 1 segundo

// ==================== Função Setup ====================
void setup() {
  Serial.begin(9600);
  pinMode(PPG_PIN, INPUT);
  pinMode(GSR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

// ==================== Função Loop ====================
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int ppgData = analogRead(PPG_PIN);
    int gsrData = analogRead(GSR_PIN);

    int ppgFiltered = medianFilter(ppgData);
    int gsrFiltered = medianFilter(gsrData);

    int HR = calculateHeartRate(ppgFiltered);
    int stressLevel = calculateStressLevel(gsrFiltered);

    // ==================== Impressão Serial ====================
    Serial.print("PPG Filtered: "); Serial.println(ppgFiltered);
    Serial.print("HR: "); Serial.println(HR);
    Serial.print("Stress: "); Serial.println(stressLevel);

    // ==================== Publicar no MQTT ====================
    client.publish("valeria/bpm", String(HR).c_str());
    client.publish("valeria/stress", String(stressLevel).c_str());

    // ==================== Alerta local ====================
    if(HR > 120 || stressLevel > 80) { // limites exemplares
      digitalWrite(BUZZER_PIN, HIGH);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.println("ALERTA CRITICO!");
      display.display();
      delay(5000);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}

// ==================== Filtro de mediana ====================
int medianFilter(int data) {
  static int window[WINDOW_SIZE];
  static int currentIndex = 0;

  window[currentIndex] = data;
  currentIndex = (currentIndex + 1) % WINDOW_SIZE;

  // Bubble Sort
  for(int i=0;i<WINDOW_SIZE-1;i++){
    for(int j=0;j<WINDOW_SIZE-i-1;j++){
      if(window[j]>window[j+1]){
        int temp=window[j];
        window[j]=window[j+1];
        window[j+1]=temp;
      }
    }
  }

  return window[WINDOW_SIZE/2];
}

// ==================== Cálculos ====================
int calculateHeartRate(int ppgFiltered){
  int threshold = 500;
  int peakCount = 0;
  static bool aboveThreshold = false;

  if(ppgFiltered > threshold){
    if(!aboveThreshold){
      peakCount++;
      aboveThreshold = true;
    }
  } else aboveThreshold = false;

  int heartRate = peakCount * 60 / (interval/1000);
  return heartRate;
}

int calculateStressLevel(int gsrFiltered){
  const int GSR_MIN=0, GSR_MAX=1023;
  const int CONDUCTANCE_MIN=0, CONDUCTANCE_MAX=100;
  int conductance = map(gsrFiltered, GSR_MIN, GSR_MAX, CONDUCTANCE_MIN, CONDUCTANCE_MAX);
  return constrain(conductance,0,100);
}

// ==================== Wi-Fi e MQTT ====================
void setup_wifi(){
  delay(10);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void reconnect(){
  while(!client.connected()){
    if(client.connect("ESP32Client")){
      Serial.println("MQTT connected");
    } else{
      delay(5000);
    }
  }
}
