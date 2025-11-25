Projeto IoT – Sistema de Monitoramento com MQTT

Este repositório contém o código-fonte, diagramas, documentação e arquivos utilizados no desenvolvimento do projeto final da disciplina de Internet das Coisas (IoT). O sistema implementa a leitura de sensores, acionamento de atuadores e comunicação com a internet via protocolo MQTT.

Objetivo do Projeto

Implementar um sistema IoT capaz de:

Monitorar dados por meio de um sensor.

Acionar um atuador conforme comandos recebidos.

Enviar e receber mensagens através de um broker MQTT.

Comunicar-se via internet utilizando o protocolo MQTT.

Apresentar documentação completa, código-fonte e vídeo de demonstração.

Hardware Utilizado

NodeMCU ESP8266

Sensor (modelo utilizado descrito no artigo)

Atuador (LED, buzzer ou relé)

Protoboard

Jumpers

Fonte 5V

Cabo USB

Comunicação via MQTT
Tópicos utilizados:

Publish:

/projeto_iot/sensor

/projeto_iot/status

Subscribe:

/projeto_iot/controle

Como Executar o Projeto

Instale a Arduino IDE ou PlatformIO.

Instale as seguintes bibliotecas:

ESP8266WiFi

PubSubClient

Biblioteca correspondente ao sensor utilizado

Edite no código:

const char* ssid = "SUA_REDE";
const char* password = "SUA_SENHA";
const char* mqtt_server = "BROKER_MQTT";


Envie o código para o NodeMCU.

Abra o Monitor Serial para verificar conexão com WiFi e MQTT.

Arquitetura do Sistema
Sensor → NodeMCU → Broker MQTT → Aplicação
Atuador ← NodeMCU ← Broker MQTT ← Comandos

Testes Realizados

Foram medidos:

Tempo entre leitura do sensor e publicação no broker.

Tempo entre comando MQTT e acionamento do atuador.

Quatro medições foram feitas, conforme tabela no artigo final.

Resultados

Imagens da montagem.

Diagrama Fritzing.

Fluxograma de funcionamento.

Capturas da comunicação MQTT.

Gráficos dos tempos de resposta.

Vídeo de Demonstração

Link do vídeo no YouTube (não listado):
[INSERIR LINK DO VÍDEO AQUI]

Artigo Final (PDF)

Link para o artigo completo (ABNT):
[INSERIR LINK DO PDF AQUI]

Repositório

Este repositório contém:

Código-fonte

Diagramas Fritzing

Fluxograma

Imagens dos testes

PDF final do artigo

Documentação completa do hardware, software e MQTT

Autora

Valéria Santana (Fênix)
Projeto desenvolvido para a disciplina de Internet das Coisas (IoT).
