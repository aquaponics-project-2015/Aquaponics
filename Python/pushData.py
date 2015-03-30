import serial
import sys
import requests
import datetime

baseURL = "ServerIP"
ser = serial.Serial('COM#', 9600, timeout = 0)

def main():
    while True:
        while(ser.inWaiting() == 0):
            pass
        val = getValue()
        print val

def getValue():
    val = ''
    this = True
    while this:
        byte = ser.read()
        if byte == '\r':
            this = False
        if (byte != '\r') and (byte != '\n'):
            val+=(byte)
    return val

def postEnvToServer(temp ,ph ,waterlevel):
	endpointURL = baseURL+#The api endpoint
	date=datetime.datetime.now()
	payload = {"waterLevel":waterlevel,"ph":ph,"temperature":temp,"datetime":date}
	r = requests.post(endpointURL, data = payload)
	print r.status_code

def postPumpToServer(status):
	endpointURL = baseURL+#The api endpoint
	date=datetime.datetime.now()
	payload = {"status":status, "datetime":date}
	r = requests.post(endpointURL, data = payload)
	print r.status_code
main()
