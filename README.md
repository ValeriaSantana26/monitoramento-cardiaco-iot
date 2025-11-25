# Projeto IoT – Sistema de Monitoramento com MQTT

Este repositório contém o código-fonte, diagramas, documentação e imagens utilizadas no desenvolvimento do projeto final da disciplina de Internet das Coisas (IoT). O sistema realiza monitoramento em tempo real utilizando sensor, atuador e comunicação via protocolo MQTT.

---

## Objetivo do Projeto

Implementar um sistema IoT capaz de:

- Monitorar dados biométricos por meio de sensores.
- Acionar um atuador conforme comandos MQTT.
- Publicar e receber informações através de um broker MQTT.
- Exibir dados em tempo real em um dashboard.
- Documentar hardware, software e integrações utilizadas.

---

## Hardware Utilizado

- NodeMCU ESP8266  
- Sensor (definido no artigo)  
- Atuador (LED e/ou Buzzer)  
- Protoboard  
- Jumpers  
- Cabo USB  
- Fonte 5V  

---

## Comunicação via MQTT

### **Tópicos utilizados**

**Publicação:**
- `/monitoramento/sensor`
- `/monitoramento/status`

**Assinatura:**
- `/monitoramento/controle`

---

## Como Executar o Projeto

1. Instale a Arduino IDE ou o PlatformIO.
2. Instale as bibliotecas:
   - `ESP8266WiFi`
   - `PubSubClient`
   - Biblioteca do sensor utilizado
3. Configure o Wi-Fi e o MQTT no código.
4. Conecte o NodeMCU via USB.
5. Carregue o código para a placa.
6. Abra o Monitor Serial para verificar a conexão com a rede e o MQTT.

### **Configurações Que Devem Ser Editadas no Código**

```cpp
// Wi-Fi
const char* ssid = "SUA_REDE";
const char* password = "SUA_SENHA";

// MQTT
const char* mqtt_server = "BROKER_MQTT";
const char* mqtt_user = "";       // opcional
const char* mqtt_password = "";   // opcional

// Pinos do hardware
const int pino_sensor = A0;   // leitura do sensor
const int pino_led = D1;      // LED (atuador)
const int pino_buzzer = D2;   // buzzer (atuador)
```

---

## Arquitetura do Sistema

O sistema utiliza uma arquitetura baseada em três camadas: **sensoriamento**, **processamento** e **comunicação MQTT**.

### **1. Camada de Sensoriamento**
Coleta de dados por meio do sensor configurado no projeto.

### **2. Camada de Processamento – NodeMCU ESP8266**
Responsável por:

- Ler o sensor
- Processar os valores
- Enviar dados ao broker MQTT
- Assinar comandos MQTT
- Acionar LED/Buzzer

### **3. Camada de Comunicação – MQTT**
Protocolo leve baseado em *publish/subscribe*.

### **Fluxo da Arquitetura**

```
+------------------+
|     Sensor       |
+--------+---------+
         |
         v
+------------------+
| NodeMCU ESP8266  |
| Processamento     |
| WiFi + MQTT       |
+--------+---------+
         |
   Publica/Recebe
         |
         v
+------------------+
|   Broker MQTT    |
+--------+---------+
         |
         v
+--------------------------+
| Dashboard / Aplicação   |
+--------------------------+
```

---

## Testes Realizados

Foram avaliados:

- Tempo entre leitura do sensor e publicação MQTT.
- Tempo entre comando MQTT e acionamento do atuador.
- Quatro medições para cada categoria.

Os dados completos estão no artigo em PDF.

---


## Vídeo de Demonstração

🔗 **Inserir link do vídeo (não listado no YouTube)**  
**[INSERIR LINK AQUI]**

---

## Artigo Final (PDF)

🔗 **Inserir link ou fazer upload do arquivo PDF**  
**[INSERIR LINK AQUI]**

---

## Autora

**Valéria Santana**   
Universidade Presbiteriana Mackenzie

