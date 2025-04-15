#include <Servo.h>

Servo servo1;

float currentTemp;
float currentHudmid;
float currentCO2;

String dataList[3];

int dataType;
// 1 - Temp
// 2 - Humid
// 3 - CO2

void setup() {
  servo1.attach(9);

  Serial.begin(9600); 
  Serial.setTimeout(100); 
}

void loop() {
  while (Serial.available() == 0) {}

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

  currentTemp = dataList[0].toFloat();
  currentHudmid = dataList[1].toFloat();
  currentCO2 = dataList[2].toFloat();

  Serial.println(String(currentTemp) + " is the current Temp");
  Serial.println(String(currentHudmid) + " is the current Humid");
  Serial.println(String(currentCO2) + " is the current CO2");
}
