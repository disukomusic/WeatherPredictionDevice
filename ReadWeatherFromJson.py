import json

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