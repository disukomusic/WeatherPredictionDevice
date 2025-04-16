#include <Servo.h>

Servo servo1;

int buttonPin = 10;

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

// Button state tracking for debouncing
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  servo1.attach(9);
  Serial.begin(9600); 
  Serial.setTimeout(100); 
  dataType = 1;

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  ReadWeatherData();
  RotateServo();

  int buttonVal = digitalRead(buttonPin);

  // Debounce logic
  if (buttonVal != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (lastButtonState == HIGH && buttonVal == LOW) {
      dataType = (dataType % 3) + 1;
      Serial.println("Data type changed to: " + String(dataType));
    }
  }

  lastButtonState = buttonVal;
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
