// B1: Them thu vien
#include <LiquidCrystal.h>

// B2: Dinh nghia, doi ten, khai bao chan cong
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

#define AUDIO 13

#define BT3 8

// B3: Khai bao bien toan cuc
int MODE = 0;
int temp3 = 0;
String split;
// B4: Cac chuong trinh con

// nut bam kiem tra coi
void Button3() {
  if (digitalRead(BT3) == 0) {
    temp3 = 1;
  }

  if (temp3 == 1)
  {
    if (digitalRead(BT3) == 1) {
      if (digitalRead(AUDIO) == 0) {
        digitalWrite(AUDIO, 1);
      }
      delay(500);
      temp3 = 0;
    }
  }
}

// ham nhan tin hieu tu chip sensor
void ReceiveSignal() {
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('/');
    if ( command.startsWith("mode=1") ) {
      split = command.substring(7);
      MODE = 1;
      Serial.println("mode1");
    }
    else if ( command == "mode=2" ) {
      MODE = 2;
      Serial.println("mode2");
    }
    else if ( command == "mode=3" ) {
      MODE = 3;
      Serial.println("mode3");
    }
    else if ( command == "mode=4" ) {
      MODE = 4;
      Serial.println("mode4");
    }
  }
}

// B5: Cai dat khoi tao ban dau
void setup()
{
  lcd_1.begin(16, 2);
  pinMode(AUDIO, OUTPUT);
  Serial.begin(9600);
  pinMode(BT3, INPUT_PULLUP);
}

// B6: Chuong trinh chinh
void loop()
{
  // B1: thu thap du lieu
  // thu thap tin hieu tu chip sensor va xu ly
  ReceiveSignal();


  // B2: Dieu khien dau ra
  // che do hien thi LCD
  switch (MODE) {
    case 1:
      lcd_1.setCursor(0, 0); lcd_1.print("SYSTEM: READY         ");
      lcd_1.setCursor(0, 1); lcd_1.print(split);
      digitalWrite(AUDIO, 0);
      // nut chi kiem tra khi he thong dang trong trang thai "READY"
      Button3();
      break;
    case 2:
      lcd_1.setCursor(0, 0); lcd_1.print("DETECT SOMETHING      ");
      lcd_1.setCursor(0, 1); lcd_1.print("  LIGHT ON!           ");
      digitalWrite(AUDIO, 0);
      break;
    case 3:
      lcd_1.setCursor(0, 0); lcd_1.print(" TRAIN IS COMING       ");
      lcd_1.setCursor(0, 1); lcd_1.print("  BARIE DOWN!          ");
      digitalWrite(AUDIO, 0);
      break;
    case 4:
      lcd_1.setCursor(0, 0); lcd_1.print("TRAIN IS PASSING        ");
      lcd_1.setCursor(0, 1); lcd_1.print("   BUZZER ON!           ");
      digitalWrite(AUDIO, 1);
      break;
  }

}