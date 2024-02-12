import paho.mqtt.client as mqtt
import json
import time
import logging


logging.basicConfig(filename='logs/bridge.log', level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger('bridge-ttn-v2.3')


#==================== NODE CONFIG =======================
class NodeConfig:
    def __init__(self, address, port, application, topic, mqttApiKey):
        self.address    = address
        self.port       = port
        self.application= application
        self.topic      = topic
        self.mqttApiKey = mqttApiKey

"""
application = "iokey-application@ttn",
device      = "heltec-01",
topic       = f"v3/{application}/devices/{device}/up"
"""

NodeOne = NodeConfig(
    address     = "eu1.cloud.thethings.network", 
    port        = 1883,
    application = "iokey-application@ttn",
    mqttApiKey  = "NNSXS.4HKGKE4UFSYWOOGY27SFW2RGAR6JHQTQIRS6ACQ.4LKLX24BCNN7RM4WHQAGIB3RIXREGQ3KBJX2LZC7GGQBISEXKNIA",
    topic       = f"v3/iokey-application@ttn/devices/heltec-01/up"
)

NodeTwo = NodeConfig(
    address     = "127.0.0.1", #"57.129.14.253"
    port        = 1883,
    application = None,
    mqttApiKey  = None,
    topic       = "iokey/data"
)


#=================== JSON FORMATER ======================
def format_json(data):
    formatted_json = {
        "datalogger": data['datalogger'],
        "battery_level": data['battery_level'],
        "temperature": {
            "temperature_s1": data['temperature']['temperature_s1'],
            "temperature_s2": data['temperature']['temperature_s2'],
            "temperature_s3": data['temperature']['temperature_s3']
        },
        "humidity": {
            "humidity_s1": data['humidity']['humidity_s1'],
            "humidity_s2": data['humidity']['humidity_s2'],
            "humidity_s3": data['humidity']['humidity_s3']
        }
    }
    return json.dumps(formatted_json)



#================== BUILDING BRIDGE =====================
def connect_subscriber(client, userdata, flags, rc):
    if rc == 0:
        client.subscribe(NodeOne.topic)
               
        if (subscriber.is_connected()):
            logger.info(f"Connection successfully established between Node: {NodeOne.address}:{NodeOne.port} and Node: {NodeTwo.address}:{NodeTwo.port}")

        logger.info("<< MQTT bridge operational >>")
    else:
        logger.error(f"Connection between nodes failed with result code {rc}")


def disconnected_subscriber(client, userdata, rc):
    logger.error(f"Unexpected disconnection. Attempting to reconnect...")
       

def message_subscriber(client, userdata, message):
    #logger.info("Message received")
    try:
        message_decode = message.payload.decode('utf8')
        message_json = json.loads(message_decode)
        data = message_json.get('uplink_message', {}).get('decoded_payload', {})
        #data = json.dumps(message_decode)

        if data:
            formatted_payload = format_json(data)
            publisher.connect(NodeTwo.address, NodeTwo.port)
            time.sleep(1)
            publisher.publish(NodeTwo.topic, formatted_payload)
            publisher.disconnect()
            logger.info(f"Message broadcasted: {formatted_payload}")
        else:
            logger.warning("No valid data found in the incoming message")
    
    except json.JSONDecodeError as json_error:
        logger.error(f"JSON decoding error: {json_error}")
    
    except Exception as exc:
        logger.exception(exc)



publisher = mqtt.Client("Publisher")
#publisher.connect(NodeTwo.address, NodeTwo.port)

subscriber = mqtt.Client("Subscriber")
subscriber.username_pw_set(NodeOne.application, NodeOne.mqttApiKey)

subscriber.on_connect = connect_subscriber
subscriber.on_disconnect = disconnected_subscriber
subscriber.on_message = message_subscriber
subscriber.connect(NodeOne.address, NodeOne.port)


#====================== RUNNING =========================
while True:
    try:
        subscriber.loop_forever()
    except Exception as exc:
        logger.exception(exc)
        time.sleep(5)
