import os
import json
import serial
import requests
import time

# Open serial comms with the Arduino
arduino = serial.Serial(port='COM6',   baudrate=9600, timeout=.1)
#Wait for arduino to reset
time.sleep(2)


# HTTP Request to get weather data. Will be replaced with Jeffery's server instead
response = requests.get("https://raw.githubusercontent.com/disukomusic/WeatherPredictionDevice/refs/heads/main/sampleWeatherData.json")
# Decode using utf-8-sig to strip BOM, THEN parse
data = json.loads(response.content.decode("utf-8-sig"))

# local file
# with open(filePath, encoding="utf-8-sig") as json_file:
#     data = json.load(json_file)

def getTemp():
    temp = data.get("Temp", "")
    return temp
def getHumidity():
    humid = data.get("Humidity", "")
    return humid
def getCO2():
    co2 = data.get("CO2(ppm)", "")
    return co2

print(data)

temp = getTemp()
humid = getHumidity()
co2 = getCO2()

print(f"Temperature is {temp}")
print(f"Humidity is {humid}")
print(f"CO2 level is {co2}ppm")

print(f"Sending: {temp} {humid} {co2}")
message = f"{temp} {humid} {co2}\n"
arduino.write(message.encode('utf-8'))

