//v1.1 Change Notes:
//    -Changed Done to "bool" -Created Functions to make code more efficient -Fixed bug where door would lock when closed then quickly reopened

#define ping_Pin 13
#define echo_Pin 12

#include <Servo.h> 


#define Servo_Pin 1
Servo s;
bool done = true;

long distance(void);
void lock(void);

void setup() {
 
    pinMode(echo_Pin, INPUT);
    pinMode(ping_Pin, OUTPUT);
    
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