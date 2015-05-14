import sys
import datetime
import time
import json
import requests
from random import randint

#Can be Downloaded from this Link
#https://pypi.python.org/pypi/pyserial

#Can be Downloaded from this Link
#http://docs.python-requests.org/en/latest/
baseURL = "http://54.152.138.146:9000"


def main():
    while True:
        temp = randomTemp()
        pH = randompH()
        water = randomWaterlevel()
        postEnvToServer(temp,pH,water)
        time.sleep(120)
        


def randomTemp():
    baseTemp = 24
    numberSeed = randint(1,50)
    variance = numberSeed*0.1
    return baseTemp+variance

def randompH():
    base = 6
    numberSeed = randint(1,20)
    variance = numberSeed*0.1
    return base+variance

def randomWaterlevel():
    base = 20
    numberSeed = randint(0,5)
    
    return base+numberSeed

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
 
main()
