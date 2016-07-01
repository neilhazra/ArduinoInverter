volatile int wave0 = 0, wave1 = 0;
int pwm;
float voltage;
int i;
int sample;
double HERTZ;
const int dataSizeConst = 6;
const int maxSize = 30;
float processedData[dataSizeConst];
int dataSize;
char incommingData[maxSize];
char _incommingData[maxSize];
unsigned long startingTime = 0;
double prevTime = 0;
#include "Waveforms.h"
#define oneHzSample 1000000/maxSamplesNum
int x = 0;
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
  
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  tone(3,5000);
  //tone(3,31);
}

void serialEvent()  {
  if (Serial.available())  {
    x = Serial.parseInt();
    if (x == 1)  {
      Serial.println("ON");
      digitalWrite(5, HIGH);
      analogWrite(9, 0);
      analogWrite(10, 0);
      analogWrite(11, 40);

    }
    if (x == 0)  {
      Serial.println("OFF");
      digitalWrite(5, LOW);
      analogWrite(9, 40);
      analogWrite(10, 0);
      analogWrite(11, 0);
    }
  }
}


// the loop routine runs over and over again forever:
void loop() {
  /*
  int x = (waveformsTable[wave0][i] - 2048) / 8;
  pwm = abs(x);
  if (x < 0)  {
    positive();
  }
  if (x > 0)  {
    negative();
    //positive();
  }
  i += 1;
  //delayMicroseconds(138);
  if (i == maxSamplesNum)    i = 0;
  */
}

void positive ()
{
  digitalWrite(2, HIGH);
  analogWrite(3, pwm);
  digitalWrite(4, LOW);
}
void negative ()
{
  digitalWrite(2, LOW);
  analogWrite(3, pwm);
  digitalWrite(4, HIGH);
}
void convertData()  {
  for (int i = 0; i < dataSizeConst; i++)  {
    processedData[i] = processedData[i];
    Serial.print(processedData[i]);
    Serial.print(" ");
  }
  Serial.println();
}
void saveData()  {
  for (int i = 0; i < 50; i++)  {
    _incommingData[i] = incommingData[i];
  }
  char *p = _incommingData;
  char *str;
  char *data[dataSizeConst];
  int i = 0;
  while ((str = strtok_r(p, ";", &p)) != NULL)   {// delimiter is the semicolon
    data[i] = str;
    i++;
  }
  dataSize = i;
  for (int _i = 0; _i < i; _i++)  {
    processedData[_i] = atof(data[_i]);
  }
}
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  //return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
