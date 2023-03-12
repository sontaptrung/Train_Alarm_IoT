
// B1: Them thu vien
#include <Servo.h>

// B2: Dinh nghia, doi ten, khai bao chan cong
#define TRIG1 A0
#define ECHO1 13

#define TRIG2 A1
#define ECHO2 12

#define TRIG3 A2
#define ECHO3 11

#define TRIG4 A3
#define ECHO4 10

#define TRIG5 A4
#define ECHO5 9

#define TRIG6 A5
#define ECHO6 8

#define MOTOR 5

#define LED1 2
#define LED2 3

#define BT1 6
#define BT2 7

// B3: Khai bao bien toan cuc
Servo myservo;                       // create servo object to control a servo
int nhayDen = 0;                     // 0 la nhay LED2, 1 la nhay LED 1
int servoStatus = 0;                 // 0 la o goc 0, 1 la o goc 90
int ledStatus = 0;                   // 0 la tat nhay LED, 1 la bat nhay LED
int audioStatus = 0;                 // 0 la coi tat, 1 la coi bat
int temp1 = 0, temp2 = 0, temp3 = 0; // cac temp de xu ly chong nhieu cho button
int checkSensor1 = 0, checkSensor2 = 0, checkSensor3 = 0, checkSensor4 = 0, checkSensor5 = 0, checkSensor6 = 0;
int sensor1Status, sensor2Status, sensor3Status, sensor4Status, sensor5Status, sensor6Status;
int coVat = 0, coTau = 0;
unsigned long curMillis = 0;
// B4: Cac chuong trinh con

// lay du lieu tu cam bien
int SensorData(int TrigNumber, int EchoNumber, int number)
{
  // phat song am co xung 10 micros
  digitalWrite(TrigNumber, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigNumber, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigNumber, LOW);

  // dem thoi gian nhan xung cua echo
  // neu qua 30 micros echo khong nhan duoc tin hieu thi tu nhay ve trang thai LOW
  const unsigned long duration = pulseIn(EchoNumber, HIGH);

  // tinh khoang cach tu vat den sensor
  int distance = duration / 29 / 2;
  // check sensor con hoat dong
  if (distance < 200)
  {
    checkSensor(number, 1);
    // khoang co vat
    if (distance < 10)
      return 1;
    else
    {
      return 0;
    }
  }
  else
  {
    checkSensor(number, 0);
    return 0;
  }
}

void checkSensor(int number, int status)
{
  switch (number)
  {
  case 1:
    checkSensor1 = status;
    break;
  case 2:
    checkSensor2 = status;
    break;
  case 3:
    checkSensor3 = status;
    break;
  case 4:
    checkSensor4 = status;
    break;
  case 5:
    checkSensor5 = status;
    break;
  case 6:
    checkSensor6 = status;
    break;
  }
}

// ham truyen du lieu sang chip LCD
void TransmitSignal(int mode)
{
  // chip truyen
  if (mode == 1)
  {
    Serial.print(String("mode=1|") + checkSensor1 + "  " + checkSensor2 + "  " + checkSensor3 + "  " + checkSensor4 + "  " + checkSensor5 + "  " + checkSensor6 + "/");
  }
  else if (mode == 2)
    Serial.print("mode=2/");
  else if (mode == 3)
    Serial.print("mode=3/");
  else if (mode == 4)
    Serial.print("mode=4/");
}

// nut bam kiem tra 2 LED
void Button1()
{
  // xu ly chong nhieu cho nut bam
  if (digitalRead(BT1) == 0)
  {
    temp1 = 1;
  }

  if (temp1 == 1)
  {
    if (digitalRead(BT1) == 1)
    {

      // check 2 LED dang tat
      if (digitalRead(LED1) == 0 && digitalRead(LED2) == 0)
      {
        digitalWrite(LED1, 1);
        digitalWrite(LED2, 0);
        delay(150);
        digitalWrite(LED1, 0);
        digitalWrite(LED2, 1);
        delay(150);
        digitalWrite(LED1, 1);
        digitalWrite(LED2, 0);
        delay(150);
        digitalWrite(LED1, 0);
        digitalWrite(LED2, 1);
        delay(150);
      }
      temp1 = 0;
    }
  }
}

// nut bam kiem tra dong co servo
void Button2()
{
  // xu ly chong nhieu cho nut bam
  if (digitalRead(BT2) == 0)
  {
    temp2 = 1;
  }

  if (temp2 == 1)
  {
    if (digitalRead(BT2) == 1)
    {

      // check dong co dang o goc 0
      if (servoStatus == 0)
      {
        myservo.write(90);
        delay(500);
      }
      temp2 = 0;
    }
  }
}


void servoControl(int n)
{
  if (n == 1)
  {
    servoStatus = 1;
    myservo.write(90);
  }
  else
  {
    servoStatus = 0;
    myservo.write(0);
  }
}

// B5: Cai dat khoi tao ban dau
void setup()
{
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);

  pinMode(TRIG4, OUTPUT);
  pinMode(ECHO4, INPUT);

  pinMode(TRIG5, OUTPUT);
  pinMode(ECHO5, INPUT);

  pinMode(TRIG6, OUTPUT);
  pinMode(ECHO6, INPUT);

  Serial.begin(9600);

  myservo.attach(MOTOR); // attaches the servo on pin 7 to the servo object

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(BT1, INPUT_PULLUP);
  pinMode(BT2, INPUT_PULLUP);

  // cho dong co ve goc 0
  myservo.write(0);
}

// B6: Chuong trinh chinh
void loop()
{
  // B1: thu thap du lieu
  // thu thap du lieu sensor 1
  sensor1Status = SensorData(TRIG1, ECHO1, 1);
  // thu thap du lieu sensor 2
  sensor2Status = SensorData(TRIG2, ECHO2, 2);
  // thu thap du lieu sensor 3
  sensor3Status = SensorData(TRIG3, ECHO3, 3);
  // thu thap du lieu sensor 4
  sensor4Status = SensorData(TRIG4, ECHO4, 4);
  // thu thap du lieu sensor 5
  sensor5Status = SensorData(TRIG5, ECHO5, 5);
  // thu thap du lieu sensor 6
  sensor6Status = SensorData(TRIG6, ECHO6, 6);
  // B2: Xu ly, Chong nhieu

  if (coTau == 0)
  {
    // xu ly cam bien
    // check sensor 1 co vat, sensor 2 khong co vat, sensor 3 khong co vat
    if ((sensor1Status == 1 && sensor2Status == 0 && sensor3Status == 0) || (sensor6Status == 1 && sensor5Status == 0 && sensor4Status == 0))
    {
      curMillis = millis();
      coVat = 1;
      ledStatus = 1;
      servoControl(0);
      audioStatus = 0;
    }
    // check sensor 2 co vat, sensor 3 khong co vat
    else if ((coVat == 1 && sensor2Status == 1 && sensor3Status == 0) || (coVat == 1 && sensor5Status == 1 && sensor4Status == 0))
    {
      coTau = 1;
      coVat = 0;
      ledStatus = 1;
      servoControl(1);
      audioStatus = 0;
    }

    if ((millis() - curMillis) > 2000)
    {
      coVat = 0;
      ledStatus = 0;
      servoControl(0);
      audioStatus = 0;
    }
  }
  else
  {
    if ((sensor1Status == 1 && sensor2Status == 0 && sensor3Status == 0) || (sensor6Status == 1 && sensor5Status == 0 && sensor4Status == 0))
    {
      curMillis = millis();
      ledStatus = 1;
      servoControl(0);
      audioStatus = 0;
    }
    // check sensor 2 co vat, sensor 3 khong co vat
    else if ((sensor2Status == 1 && sensor3Status == 0) || (sensor5Status == 1 && sensor4Status == 0))
    {
      curMillis = millis();
      ledStatus = 1;
      servoControl(1);
      audioStatus = 0;
    }

    // check sensor 3 co vat
    else if (sensor3Status == 1 || sensor4Status == 1)
    {
      curMillis = millis();
      ledStatus = 1;
      servoControl(1);
      audioStatus = 1;
    }

    if ((millis() - curMillis) > 2000)
    {
      coTau = 0;
      ledStatus = 0;
      servoControl(0);
      audioStatus = 0;
    }
  }

// XU LY NHAY LED
  if (ledStatus == 1)
  {
    if (nhayDen == 0)
    {
      digitalWrite(LED1, 1);
      digitalWrite(LED2, 0);
      nhayDen++;
    }
    else if (nhayDen == 1)
    {
      digitalWrite(LED1, 0);
      digitalWrite(LED2, 1);
      nhayDen--;
    }
  }
  else
  {
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
  }
// truyen mode cho chip lcd
  // check dong co o goc 0, led tat, coi tat
  if (servoStatus == 0 && ledStatus == 0 && audioStatus == 0)
  {
    TransmitSignal(1);
    Button1();
    Button2();
  }
  // check dong co o goc 0, led bat, coi tat
  else if (servoStatus == 0 && ledStatus == 1 && audioStatus == 0)
  {
    TransmitSignal(2);
  }
  // check dong co o goc 90, led bat, coi tat
  else if (servoStatus == 1 && ledStatus == 1 && audioStatus == 0)
  {
    TransmitSignal(3);
  }
  // check dong co o goc 90, led bat, coi bat
  else if (servoStatus == 1 && ledStatus == 1 && audioStatus == 1)
  {
    TransmitSignal(4);
  }
}