import requests
import datetime
baseURL = "ServerIP"

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