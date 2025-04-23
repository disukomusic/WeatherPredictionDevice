#include <Servo.h>

Servo servo1;

int buttonPin = 10;
const unsigned long DebounceTime = 10;
boolean ButtonWasPressed = false;
unsigned long ButtonStateChangeTime = 0; // Debounce timer

int dataType;
// 1 - Temp
// 2 - Humid
// 3 - CO2

float currentTemp;
float minTemp = 0;
float maxTemp = 50;

float currentHumid;
float minHumid = 20;
float maxHumid = 90;

float currentCO2;
float minCO2 = 400;
float maxCO2 = 2000;

String dataList[3];

// LED pins
const int tempLED = 2;
const int humidLED = 3;
const int co2LED = 4;

void setup() {
  servo1.attach(9);
  Serial.begin(9600); 
  Serial.setTimeout(100); 
  dataType = 1;

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(tempLED, OUTPUT);
  pinMode(humidLED, OUTPUT);
  pinMode(co2LED, OUTPUT);
  updateLEDs();
}

void loop() {
  ReadWeatherData();
  RotateServo();
  checkButton();
}

void ReadWeatherData()
{
  if (Serial.available() > 0) {
    String data = Serial.readString();  
    data.trim();

    int StringCount = 0;
    String str = data;

    while (str.length() > 0 && StringCount < 3) {
      int index = str.indexOf(' ');
      if (index == -1) {
        dataList[StringCount++] = str;
        break;
      } else {
        dataList[StringCount++] = str.substring(0, index);
        str = str.substring(index + 1);
      }
    }

    if (StringCount == 3) {
      currentTemp = dataList[0].toFloat();
      currentHumid = dataList[1].toFloat();
      currentCO2 = dataList[2].toFloat();

      Serial.println(String(currentTemp) + " is the current Temp");
      Serial.println(String(currentHumid) + " is the current Humid");
      Serial.println(String(currentCO2) + " is the current CO2");
    }
  }
}

void RotateServo()
{
  float servoAngle = 0; 

  switch (dataType) {
    case 1:
      servoAngle = 180 - ((currentTemp - minTemp) / (maxTemp - minTemp)) * 180;
      break;
    case 2:
      servoAngle = 180 - ((currentHumid - minHumid) / (maxHumid - minHumid)) * 180;
      break;
    case 3:
      servoAngle = 180 - ((currentCO2 - minCO2) / (maxCO2 - minCO2)) * 180;
      break;
  }

  // Clamp to safe range
  servoAngle = constrain(servoAngle, 0, 180);
  servo1.write(servoAngle);
}

void checkButton()
{
  unsigned long currentTime = millis();
  boolean buttonIsPressed = digitalRead(buttonPin) == LOW;  // Active LOW

  if (buttonIsPressed != ButtonWasPressed &&
      currentTime - ButtonStateChangeTime > DebounceTime)
  {
    ButtonWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;

    if (ButtonWasPressed)
    {
      dataType = (dataType % 3) + 1;

      String typeName;
      switch (dataType) {
        case 1: typeName = "Temperature: " + String(currentTemp); break;
        case 2: typeName = "Humidity: " + String(currentHumid); break;
        case 3: typeName = "CO2: " + String(currentCO2); break;
      }

      Serial.println("Data type changed to: " + typeName);
      updateLEDs();
    }
  }
}

void updateLEDs() {
  digitalWrite(tempLED, dataType == 1 ? HIGH : LOW);
  digitalWrite(humidLED, dataType == 2 ? HIGH : LOW);
  digitalWrite(co2LED, dataType == 3 ? HIGH : LOW);
}
