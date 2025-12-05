<h1 align="center">🫀 Sistema de Monitoramento Cardíaco IoT com ESP32</h1>
<p align="center"><b>Monitoramento de Batimentos Cardíacos (PPG), Nível de Estresse (GSR), Display OLED, Buzzer e Envio MQTT</b></p>

<hr>

<h2>📌 Descrição do Projeto</h2>
<p>
Este projeto utiliza um <b>ESP32</b> para monitorar sinais fisiológicos — como batimentos cardíacos e nível de estresse — 
através de sensores PPG e GSR. As informações são exibidas em um <b>display OLED</b>, alertas sonoros são emitidos por um <b>buzzer</b>, 
e todos os dados são enviados via <b>MQTT</b> para um servidor, dashboard, celular ou aplicação IoT.
</p>

<hr>

<h2>📦 Componentes Utilizados</h2>
<ul>
  <li>ESP32 DevKit V1</li>
  <li>Sensor PPG (Pulse Sensor)</li>
  <li>Sensor GSR (Galvanic Skin Response)</li>
  <li>Display OLED I2C (SSD1306 – 128x64)</li>
  <li>Buzzer</li>
  <li>Protoboard e jumpers</li>
</ul>

<hr>

<h2>🧩 Funcionalidades</h2>
<ul>
  <li>✔ Leitura de batimentos cardíacos (BPM)</li>
  <li>✔ Cálculo de nível de estresse com base no GSR</li>
  <li>✔ Exibição em tempo real no OLED</li>
  <li>✔ Alerta sonoro em situações críticas</li>
  <li>✔ Envio dos valores via MQTT</li>
  <li>✔ Compatível com Wokwi e ESP32 físico</li>
</ul>

<hr>

<h2>🔌 Conexões dos Sensores</h2>

<h3>📍 Pulse Sensor (PPG)</h3>
<ul>
  <li>Sinal → GPIO 34</li>
  <li>VCC → 3.3V</li>
  <li>GND → GND</li>
</ul>

<h3>📍 Sensor GSR</h3>
<ul>
  <li>Sinal → GPIO 35</li>
  <li>VCC → 3.3V</li>
  <li>GND → GND</li>
</ul>

<h3>📍 OLED SSD1306</h3>
<ul>
  <li>SDA → GPIO 21</li>
  <li>SCL → GPIO 22</li>
  <li>VCC → 3.3V</li>
  <li>GND → GND</li>
</ul>

<h3>📍 Buzzer</h3>
<ul>
  <li>Positivo → GPIO 23</li>
  <li>Negativo → GND</li>
</ul>

<hr>

<h2>📡 Comunicação MQTT</h2>
<p>Este sistema envia dois tópicos principais via MQTT:</p>

<pre>
valeria/bpm
valeria/stress
</pre>

<p>Publicado pelo código:</p>

<pre>
client.publish("valeria/bpm", String(HR).c_str());
client.publish("valeria/stress", String(stressLevel).c_str());
</pre>

<hr>

<h2>📁 Estrutura do Projeto</h2>

<pre>
monitoramento-cardiaco-iot/
│
├── README.md
├── sketch.ino
├── diagram.json
├── pulse.chip.c
├── pulse.chip.json
├── libraries.txt
└── wokwi-project.txt
</pre>

<hr>

<h2>🛠 Bibliotecas Necessárias</h2>

<ul>
  <li>Adafruit GFX Library</li>
  <li>Adafruit SSD1306</li>
  <li>PubSubClient</li>
  <li>WiFi</li>
</ul>

<hr>

<h2>🚀 Como Executar</h2>
<ol>
  <li>Abra o projeto no VSCode ou Arduino IDE.</li>
  <li>Compile e envie para o ESP32.</li>
  <li>Abra seu servidor MQTT e monitore os tópicos.</li>
</ol>

<h3>📡 Tópicos para monitorar:</h3>

<pre>
valeria/bpm
valeria/stress
</pre>

<hr>

<h2>🧠 Lógica do Funcionamento</h2>
<ul>
  <li>Lê o sinal do PPG.</li>
  <li>Filtra ruídos (filtro mediano).</li>
  <li>Calcula a frequência cardíaca.</li>
  <li>Lê o GSR e determina nível de estresse.</li>
  <li>Mostra BPM e Stress no OLED.</li>
  <li>Envia tudo via MQTT.</li>
  <li>Ativa buzzer em caso de alerta.</li>
</ul>

<hr>

<h2>🖥 Exemplo de Tela</h2>

<pre>
BPM: 82
Stress: Baixo
Status: Normal
</pre>

<hr>

<h2>🌐 Simulação Wokwi</h2>
<p>Todo o projeto é compatível com o ambiente Wokwi.  
O arquivo <code>diagram.json</code> contém toda a simulação.</p>

<hr>

<h2>👩‍💻 Autora</h2>
<p><b>Valéria Santana </b>  
Projeto acadêmico integrando IoT, eletrônica e monitoramento fisiológico.</p>

<hr>
