import paho.mqtt.client as mqtt
import json, time

BROKER = "broker.hivemq.com"

TOPIC_CMD = "cardiaco/comando"
TOPIC_RTT = "cardiaco/rtt"

def on_connect(client, userdata, flags, rc):
    client.subscribe(TOPIC_RTT)

def on_message(client, userdata, msg):
    recv_ts = int(time.time()*1000)
    data = json.loads(msg.payload.decode())
    client_ts = data["client_ts"]
    rtt = recv_ts - client_ts
    print("RTT (ms):", rtt)

def enviar_comando():
    ts = int(time.time()*1000)
    client.publish(TOPIC_CMD, f"CMD:{ts}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(BROKER, 1883)
client.loop_start()

for i in range(4):
    enviar_comando()
    time.sleep(2)

client.loop_stop()
