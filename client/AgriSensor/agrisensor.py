#!/usr/bin/python
#
# simple app to read topic and value strings from serial port (arduino board)
# and publish via MQTT
#
# uses the Python MQTT client from the Mosquitto project
# http://mosquitto.org
#
# Didier Donsez, 2013
# initially from Andy Piper http://andypiper.co.uk
# 2011/09/15

import serial
import os
import sys
import paho.mqtt.client as mqtt

#broker=sys.argv[1]
#broker = "10.0.1.3"
broker = "test.mosquitto.org"
port = 1883

# serialdev = '/dev/ttyACM0'
serialdev = '/dev/ttyUSB0'

# for instance, an IPv6 address
sensorid="123456789"

topicPrefix="sensor/" + sensorid

#MQTT callbacks

def on_connect(mosq, obj, rc):
    if rc == 0:
        print("Connected successfully.")
    else:
        raise Exception


def on_disconnect(mosq, obj, rc):
    print("Disconnected successfully.")


def on_publish(mosq, obj, mid):
    print("Message "+str(mid)+" published.")


def on_subscribe(mosq, obj, mid, qos_list):
    print("Subscribe with mid "+str(mid)+" received.")


def on_unsubscribe(mosq, obj, mid):
    print("Unsubscribe with mid "+str(mid)+" received.")


def on_message(mosq, obj, msg):
    print("Message received on topic "+msg.topic+" with QoS "+str(msg.qos)+" and payload "+msg.payload)


#called on exit
#close serial, disconnect MQTT
def cleanup():
    print "Ending and cleaning up"
    ser.close()
    mqttc.disconnect()

try:
    print "Connecting... ", serialdev
    #connect to serial port
    ser = serial.Serial(serialdev, 9600, timeout=20)
except:
    print "Failed to connect serial"
    #unable to continue with no serial input
    raise SystemExit


try:
    ser.flushInput()
    #create an mqtt client
    mypid = os.getpid()
    client_uniq = "arduino_pub_"+str(mypid)

    mqttc = mqtt.Client()

    #attach MQTT callbacks
    mqttc.on_connect = on_connect
    mqttc.on_disconnect = on_disconnect
    mqttc.on_publish = on_publish
    mqttc.on_subscribe = on_subscribe
    mqttc.on_unsubscribe = on_unsubscribe
    #mqttc.on_message = on_message

    #connect to broker
    print "coucou"
    mqttc.connect(broker, port, 60)
    print "caca"
    #remain connected to broker
    #read data from serial and publish
    while mqttc.loop() == 0:
        line = ser.readline()
        #split line as it contains topic and value
        list = line.split(" ")
        #second list element is value

        topic = list[0].rstrip()
        topic = "weedo"
        if topic.startswith('/'):        
            value = list[1].rstrip()
            print(topic + " is " + value)
            mqttc.publish(topicPrefix + topic, value)
            
        pass


# handle list index error (i.e. assume no data received)
except (IndexError):
    print "No data received within serial timeout period"
    cleanup()
# handle app closure
except (KeyboardInterrupt):
    print "Interrupt received"
    cleanup()
except (RuntimeError):
    print "uh-oh! time to die"
    cleanup()
