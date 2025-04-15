import json
import serial

arduino = serial.Serial(port='COM6',   baudrate=9600, timeout=.1)

filePath = 'sampleWeatherData.json'

with open(filePath, encoding="utf-8-sig") as json_file:
    data = json.load(json_file)

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

#thanks chatgpt
message = f"{temp} {humid} {co2}\n"
arduino.write(message.encode('utf-8'))