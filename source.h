#include <Servo.h> // 

// 180 
Servo horizontal; // 
int servoh = 180;   // 90;     // 

int servohLimitHigh = 180;
int servohLimitLow = 65;  // 

Servo vertical;   // 
int servov = 45;    //   90;     // 

int servovLimitHigh = 80;
int servovLimitLow = 15;


// LDR pin 
// analogpin PIN 0,1,2,3
int ldrlt = 0; //LDR 左上
int ldrrt = 1; //LDR 右上
int ldrld = 2; //LDR 左下
int ldrrd = 3; //LDR 右下

void setup()
{
  Serial.begin(9600);
// servo連接
// name.attacht(pin);
  horizontal.attach(9); //
  vertical.attach(10);  //
  horizontal.write(180); //初始值
  vertical.write(45); //初始值
  delay(3000); //延遲3000ms
}

void loop() 
{
  int lt = analogRead(ldrlt); // 左上
  int rt = analogRead(ldrrt); // 右上
  int ld = analogRead(ldrld); // 左下
  int rd = analogRead(ldrrd); // 右下
  

  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; // 
  int avd = (ld + rd) / 2; // 
  int avl = (lt + ld) / 2; // 
  int avr = (rt + rd) / 2; // 

  int dvert = avt - avd; // 
  int dhoriz = avl - avr;// 
  
  // IDE抓取LDR數值
  // IDE監測數值
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");
  
    
  if (-1*tol > dvert || dvert > tol) // 
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // 
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
   delay(dtime);

}





