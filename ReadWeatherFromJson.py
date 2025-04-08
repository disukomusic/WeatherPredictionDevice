import json
import sys
import platform

#Stupid check to let me test this code on Windows and not have to go in the raspberry pi before I'm ready to add the
#servo code
if platform.system() == "Windows":
    class MockServoKit:
        def __init__(self, channels):
            self.servo = [None] * channels['channels']
    ServoKit = MockServoKit
else:
    from adafruit_servokit import ServoKit


filePath = 'sampleWeatherData.json'

with open(filePath, encoding="utf-8-sig") as json_file:
    data = json.load(json_file)

def printTemp():
    for key, value in data.items():
        if key == "Temp":
            print("Temperature is " + value)

def printHumidity():
    for key, value in data.items():
        if key == "Humidity":
            print("Humidity is " + value)

def printCO2():
    for key, value in data.items():
        if key == "CO2(ppm)":
            print("CO2 level is " + value + "ppm")

print(data)

printTemp()
printHumidity()
printCO2()