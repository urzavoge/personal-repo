from whatsapp_api_client_python import API
from src import config

import requests
import json

url = "https://api.green-api.com/waInstance1103899911/lastOutgoingMessages/1bad4151e6a84010b1a77c2469817be80d277b83e3dc4203ae"

payload = {}
headers= {}

response = requests.request("GET", url, headers=headers, data = payload)

data = json.loads(response.text)

data = sorted(data, key = lambda x: x['timestamp'])

for message in data:
    for typ in message.keys():
        print(typ, ' : ', message[typ])
    print()



