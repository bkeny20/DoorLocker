//v1.1 Change Notes:
//    -Changed Done to "bool" -Created Functions to make code more efficient -Fixed bug where door would lock when closed then quickly reopened

#define ping_Pin 13
#define echo_Pin 12

#include <Servo.h>
#include <LiquidCrystal.h>

const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int status = 0; //0: armed, 1: disarmed 1min, 2: disarmed 3min, 3: disarmed 5min

#define Servo_Pin 1
Servo s;
bool done = true;

long distance(void);
void lock(void);

void setup() {
    pinMode(echo_Pin, INPUT);
    pinMode(ping_Pin, OUTPUT);

    lcd.begin(16,2);
    lcd.print("ARMED");
    
    pinMode(Servo_Pin, OUTPUT); //Set servo pin to be an output
    s.attach(Servo_Pin);//attaches servo "s" to the correct pin
    s.write(0);
    delay(500);
}

void loop() {
  
   if(distance() > 10)
   {
    done = false;
    lock();
   }
  int input = analogRead(A0);
  if (input>=1020){
    status = checkInput();
    lcd.setCursor(0, 1);
    lcd.print("              ");
    printStatus(status);
  }

//------------------------------------------------------------------
}

long distance(void)
{
  long duration, distance;
  
   digitalWrite(ping_Pin, LOW);
   delay(500);
   digitalWrite(ping_Pin, HIGH);
   delay(500);
   digitalWrite(ping_Pin, LOW);
   
   duration = pulseIn(echo_Pin, HIGH);
   distance = .0184*(duration)-.0624;

   return distance;
}

void lock(void)
{
while (!done)
  {
    if(distance() < 10)
    {
      delay(5000);
      if(distance() < 10)
      {
      for(int pos = 0; pos <= 180;pos++) //vary variable "pos" from 0 to 120
      {
        s.write(pos); // write current value of pos to servo
        delay(15);
      }
      }
      done = true;
    }
  }
    if (done == true)
    s.write(0);
}

int checkInput(void){
  int choice = 3;
  int previous = 0;
  int current = 0;
  int count = 0;
  int input = 0;
  while(1){
    if (count >= 20){
      break;
    }
    input = analogRead(A0);
    if (input>=1020){
      current = 1;
    }
    else{
      current = 0;
    }
    if (current == 0 && previous == 1){
      choice = (choice + 1)%4;
      count = 0;
    }
    previous = current;
    lcd.setCursor(0, 1);
    lcd.print("            ");
    lcd.setCursor(0, 1);   
    switch (choice){
      case 0:
        lcd.print("Arm");
        break;
      case 1:
        lcd.print("Disarm 1 min");
        break;
      case 2:
        lcd.print("Disarm 3 min");
        break;
      case 3:
        lcd.print("Disarm 5 min");
        break;        
    }
    delay(200);
    count++;
  }
  return choice;
}

void printStatus(int status){
  lcd.setCursor(0, 0);
  lcd.print("              ");
  lcd.setCursor(0, 0);
  switch (status){
    case 0:
      lcd.print("ARMED");
      break;
    case 1:
      lcd.print("DISARMED 1 MIN");
      break;
    case 2:
      lcd.print("DISARMED 3 MIN");
      break;
    case 3:
      lcd.print("DISARMED 5 MIN");
      break;        
  }
}