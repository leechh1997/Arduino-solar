#include <Servo.h> // 導入馬達資料庫

Servo horizontal; // 上層馬達
int servoh = 180;   // 初始最大值+180

int servohLimitHigh = 180;  //最大輸入值 ++180
int servohLimitLow = 65;  // 最小輸入值 - -65

Servo vertical;   // 下層馬達 
int servov = 45;    //初始最大值+45

int servovLimitHigh = 80; //最大輸入值 ++80
int servovLimitLow = 15; //最小輸入值 - -15


// LDR pin 光敏電阻連接訊號pin
// analogpin PIN 0,1,2,3

int ldrlt = 0; //LDR 左上
int ldrrt = 1; //LDR 右上
int ldrld = 2; //LDR 左下
int ldrrd = 3; //LDR 右下

void setup()
{
  Serial.begin(9600);

// servo連接

  horizontal.attach(9); //上層馬達pin 9
  vertical.attach(10);  //下層馬達pin 10
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
  
  int dtime = 10; // 檢查延遲
  int tol = 50; 
  
  int avt = (lt + rt) / 2; // 左上右上平均數值 上
  int avd = (ld + rd) / 2; // 左下右下平均數值 下
  int avl = (lt + ld) / 2; // 左上左下平均數值 左
  int avr = (rt + rd) / 2; // 右上右下平均數值 右

  int dvert = avt - avd; // 確認光敏電阻數值決定上下  
  int dhoriz = avl - avr;// 確認光敏電阻數值決定左右
  
  
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
  
    
  if (-1*tol > dvert || dvert > tol) // 確認阻值 , 檢查無負阻值否則改變角度

//下層

  {
  if (avt > avd)
  {
    servov = ++servov; // i=i+1
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov; // I = i-1
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov); //d
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // 確認阻值 , 檢查無負阻值否則改變角度

//上層

  {
  if (avl > avr)
  {
    servoh = --servoh; // i=i-1
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh; //1+1
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr) //左右
  {
    
    // 不做動作
  }
  horizontal.write(servoh); //t
  }
   delay(dtime);
}
