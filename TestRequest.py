import os
import requests
import json

response = requests.get("http://192.168.0.119:80/latest")
data = response.text
data = json.loads(data).decode("utf-8-sig")

print(data)