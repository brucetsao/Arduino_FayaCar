#include <SoftwareSerial.h>   // 引用程式庫

/*
wire connection map
======= Module =====  ==== fayaduino ====
left gear motor SIG <----> Pin 7
left gear motor DIR <----> Pin 8

Right gear motor SIG <----> Pin 9
Right gear motor DIR <----> Pin 10

BT module VCC <----> 5V
BT module GND <----> GND
BT module RX  <----> RX(Pin 0)
========================================
*/

#define txpin 11
#define rxpin 12
#define sigL 7
#define dirL 8

#define sigR 9
#define dirR 10

int Mspeed = 220;    //減速馬達轉速(PWM範圍:0~255)
SoftwareSerial BT(txpin, rxpin); // 接收腳, 傳送腳
char BTChar ;
void setup()
{
  BT.begin(9600);
  pinMode(sigL,OUTPUT);
  pinMode(dirL,OUTPUT);
  pinMode(sigR,OUTPUT);
  pinMode(dirR,OUTPUT);
  Serial.begin(9600);
}

int temp = 0;
//steps=512 ,RPM=40, 1024=半圈

void loop()
{

  if (BT.available() >0)
      {

        BTChar = BT.read() ;
            Serial.println( BTChar, HEX) ;    
        if (BTChar == 'F' )
           Advance();      //前進
        if (BTChar == 'B' )
             Retreat();   //後退
        if (BTChar == 'R' )
            Turnright();   //右轉
        if (BTChar == 'L' )
             Turnleft();    //左轉
        if (BTChar == 'S' )
            stopmove();  //停止      //停車
      }
      delay(150);
 
}

void Retreat() //後退
{
  analogWrite(sigL,Mspeed);
  digitalWrite(dirL,LOW);

  analogWrite(sigR,Mspeed);
  digitalWrite(dirR,HIGH);  
}

void Advance() //前進
{
  analogWrite(sigL,Mspeed);
  digitalWrite(dirL,HIGH);

  analogWrite(sigR,Mspeed);
  digitalWrite(dirR,LOW);  
}

void Turnright() //右轉
{
  analogWrite(sigL,Mspeed);
  digitalWrite(dirL,HIGH);

  analogWrite(sigR,Mspeed);
 digitalWrite(dirR,HIGH);  
}

void Turnleft() //左轉
{
  analogWrite(sigL,Mspeed);
  digitalWrite(dirL,LOW);

  analogWrite(sigR,Mspeed);
  digitalWrite(dirR,LOW);  
}

void stopmove() //停止
{
  analogWrite(sigL,0);
  digitalWrite(dirR,LOW);
  analogWrite(sigR,0);
  digitalWrite(dirL,LOW);
}
