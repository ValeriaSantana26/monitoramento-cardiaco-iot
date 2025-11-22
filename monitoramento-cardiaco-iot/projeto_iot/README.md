# Sistema IoT de Monitoramento Cardíaco — ESP32 + MQTT
Autora: **Valéria Santana**

Este projeto monitora:
- Batimentos cardíacos via **AD8232**
- Temperatura corporal via **DS18B20**
- Envia tudo via **MQTT** para um broker online

Quando valores estão fora do normal, o sistema:
- Ativa buzzer
- Acende LED
- Envia mensagem de alerta via MQTT

## Tecnologias Usadas
- ESP32
- AD8232 (ECG)
- DS18B20 (temperatura)
- HiveMQ (MQTT Broker)
- Arduino IDE

## Estrutura do Projeto
