import requests
import datetime
import json
import time
baseURL = "http://54.152.138.146:9000"

def postEnvToServer(temp ,ph ,waterlevel):
	endpointURL = baseURL+"/system/newSystem"
	theTime = time.time()
	print theTime
	payload = {"waterLevel":waterlevel,"ph":ph,"temperature":temp,"datetime":theTime}
	headers = {'Content-Type': 'application/json'}
	dump =json.dumps(payload)
	print dump
	r = requests.post(endpointURL,headers=headers, data = json.dumps(payload))
	print r.url 
	print r.status_code

def postPumpToServer(status):
	endpointURL = baseURL+"/pump/newPump"
	theTime = time.time()
	payload = {"status":status, "datetime":theTime}
	headers = {'Content-Type': 'application/json'}
	r = requests.post(endpointURL, headers=headers, data = json.dumps(payload))
	print r.status_code
 