#include <Servo.h>
#include <LiquidCrystal.h>

Servo myservo[8];
int segmentOn[8] = {180, 180, 180, 180, 75, 90, 180, 90};
int segmentOff[8] = {105, 105, 105, 105, 0, 15, 105, 15};
int jack[8] = {1, 1, 0, 0, 0, 0, 1, 1};
int jump[8] = {1, 1, 0, 0, 1, 1, 0, 0};
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int po0;
int po1;
int ste = 1500;
int mode;
void setup()
{
  myservo[0].attach(2);   //Assign all of the output pins
  myservo[1].attach(3);
  myservo[2].attach(4);
  myservo[3].attach(5);
  myservo[4].attach(6);
  myservo[5].attach(7);
  myservo[6].attach(44);
  myservo[7].attach(45);
  for (int i = 0 ; i < 8 ; i++) {
    myservo[i].write(segmentOn[i]);
  }
  lcd.begin(16, 2);
  lcd.print("Starting ...");
  delay(1000);
  lcd.clear();
  lcd.print(3);
  delay(1000);
  lcd.clear();
  lcd.print(2);
  delay(1000);
  lcd.clear();
  lcd.print(1);
  delay(1000);
  lcd.clear();
}
void segOn(int pin, int input);
void segOff(int pin, int input);
void Sdelay(int ms);

void loop()
{
  if (analogRead(A1) < 341) {
    lcd.setCursor(0, 0);
    lcd.print("Jump Jack mode  ");
    for(int i=0 ; i<8 ; i++){
      segOn(i, jack[i]);
    }
    Sdelay(ste);
    //delay(1500);
    for(int i=0 ; i<8 ; i++){
      segOff(i, jack[i]);
    }
    Sdelay(ste);
   }
   else if (analogRead(A1) < 683) {
    lcd.setCursor(0, 0);
    lcd.print("High Jump mode  ");
    for(int i=0 ; i<8 ; i++){
      segOn(i, jump[i]);
    }
    Sdelay(ste);
    //delay(1500);
    for(int i=0 ; i<8 ; i++){
      segOff(i, jump[i]);
    }
    Sdelay(ste);
   }
   else {
    lcd.setCursor(0, 0);
    lcd.print("Random mode  000");
    int limb[4] = {random(0,2), random(0,2), random(0,2), random(0,2)};
    int ran[8] = {limb[0], limb[1], 1-limb[0], 1-limb[1], limb[2], limb[3], 1-limb[2], 1-limb[3]};
    for(int i=0 ; i<8 ; i++){
      segOn(i, ran[i]);
    }
    Sdelay(ste);
    //delay(1500);
   }
}

void Sdelay(int ms) {
  while (ms > 0) {
    po0 = analogRead(A0);
    po1 = analogRead(A1);
    ste = po0+1000;
    lcd.setCursor(0, 1);
    lcd.print("Delay: ");
    lcd.print(ste);
    ms-=10;
    delay(10);
  }
}
void segOn(int pin, int input) {
  if (input) {
    myservo[pin].write(segmentOn[pin]);
  }
  else {
    myservo[pin].write(segmentOff[pin]);
  }
}
void segOff(int pin, int input) {
  if (input) {
    myservo[pin].write(segmentOff[pin]);
  }
  else {
    myservo[pin].write(segmentOn[pin]);
  }
}
