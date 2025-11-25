import paho.mqtt.client as mqtt
import json, time

BROKER = "broker.hivemq.com"
TOPIC = "cardiaco/bpm"

def on_connect(client, userdata, flags, rc):
    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    recv_ts = int(time.time()*1000)
    data = json.loads(msg.payload.decode())
    latency = recv_ts - data["ts"]
    print("Latência (ms):", latency)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(BROKER, 1883)
client.loop_forever()
