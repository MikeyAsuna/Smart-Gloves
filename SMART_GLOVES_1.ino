#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"

SoftwareSerial mySerial2(10, 11);  

char mp3_flag = 0;



const int RunningAverageCount1 = 16;
float RunningAverageBuffer1[RunningAverageCount1], RunningAverageVolt1 = 0;
int NextRunningAverage1, i1;

const int RunningAverageCount2 = 16;
float RunningAverageBuffer2[RunningAverageCount2], RunningAverageVolt2 = 0;
int NextRunningAverage2, i2;

const int RunningAverageCount3 = 16;
float RunningAverageBuffer3[RunningAverageCount3], RunningAverageVolt3 = 0;
int NextRunningAverage3, i3;

const int RunningAverageCount4 = 16;
float RunningAverageBuffer4[RunningAverageCount4], RunningAverageVolt4 = 0;
int NextRunningAverage4, i4;

const int RunningAverageCount5 = 16;
float RunningAverageBuffer5[RunningAverageCount5], RunningAverageVolt5 = 0;
int NextRunningAverage5, i5;


int ms_cnt = 0;

int mv1, mv2, mv3, mv4, mv5;


char cnt = 0;

char flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;

int mp3_cnt1 = 0, mp3_cnt2 = 0, mp3_cnt3 = 0, mp3_cnt4 = 0, mp3_cnt6 = 0;

char mp3_flag1 = 0, mp3_flag2 = 0, mp3_flag3 = 0, mp3_flag4 = 0, mp3_flag6 = 0;


void setup()
{
 Serial.begin(9600);

 
 lcd.begin();

  
 lcd.backlight();

 
 
  mySerial2.begin(9600);
  mp3_set_serial(mySerial2);  
  mp3_set_volume(50);  

  delay(100);
  
}

void loop()
{
  ++cnt; if(cnt > 5)cnt = 1;

  if(cnt == 1)
  {
   RunningAverageBuffer1[NextRunningAverage1++] = analogRead(A0);
   if(NextRunningAverage1 >= RunningAverageCount1)NextRunningAverage1 = 0;
   RunningAverageVolt1 = 0;
   for(i1=0; i1< RunningAverageCount1; ++i1)RunningAverageVolt1 += RunningAverageBuffer1[i1];
   RunningAverageVolt1 /= RunningAverageCount1;
  }
  else if(cnt == 2)
  {
   RunningAverageBuffer2[NextRunningAverage2++] = analogRead(A1);
   if(NextRunningAverage2 >= RunningAverageCount2)NextRunningAverage2 = 0;
   RunningAverageVolt2 = 0;
   for(i2=0; i2< RunningAverageCount2; ++i2)RunningAverageVolt2 += RunningAverageBuffer2[i2];
   RunningAverageVolt2 /= RunningAverageCount2;
  }
  else if(cnt == 3)
  {
   RunningAverageBuffer3[NextRunningAverage3++] = analogRead(A2);
   if(NextRunningAverage3 >= RunningAverageCount3)NextRunningAverage3 = 0;
   RunningAverageVolt3 = 0;
   for(i3=0; i3< RunningAverageCount3; ++i3)RunningAverageVolt3 += RunningAverageBuffer3[i3];
   RunningAverageVolt3 /= RunningAverageCount3;
  }
  else if(cnt == 4)
  {
   RunningAverageBuffer4[NextRunningAverage4++] = analogRead(A3);
   if(NextRunningAverage4 >= RunningAverageCount4)NextRunningAverage4 = 0;
   RunningAverageVolt4 = 0;
   for(i4=0; i4< RunningAverageCount4; ++i4)RunningAverageVolt4 += RunningAverageBuffer4[i4];
   RunningAverageVolt4 /= RunningAverageCount4;
  }
  else if(cnt == 5)
  {
   RunningAverageBuffer5[NextRunningAverage5++] = analogRead(A6);
   if(NextRunningAverage5 >= RunningAverageCount5)NextRunningAverage5 = 0;
   RunningAverageVolt5 = 0;
   for(i5=0; i5< RunningAverageCount5; ++i5)RunningAverageVolt5 += RunningAverageBuffer5[i5];
   RunningAverageVolt5 /= RunningAverageCount5;
  }
 
 
  ++ms_cnt;
 
  if(ms_cnt > 50)
  {
   mv1 = map((int)RunningAverageVolt1, 270, 410, 0, 99); if(mv1 < 0)mv1 = 0;else if(mv1 > 99)mv1 = 99;
   mv2 = map((int)RunningAverageVolt2, 270, 410, 0, 99); if(mv2 < 0)mv2 = 0;else if(mv2 > 99)mv2 = 99;
   mv3 = map((int)RunningAverageVolt3, 270, 410, 0, 99); if(mv3 < 0)mv3 = 0;else if(mv3 > 99)mv3 = 99;
   mv4 = map((int)RunningAverageVolt4, 270, 410, 0, 99); if(mv4 < 0)mv4 = 0;else if(mv4 > 99)mv4 = 99;
   mv5 = map((int)RunningAverageVolt5, 270, 410, 0, 99); if(mv5 < 0)mv5 = 0;else if(mv5 > 99)mv5 = 99;

 
   lcd.setCursor(0, 0);
   lcd.print("  SMART GLOVES  ");
   
   lcd.setCursor(0, 1);
   if(mv1 < 10)lcd.print(" ");
   lcd.print(mv1);
   lcd.write(' ');
   
   if(mv2 < 10)lcd.print(" ");
   lcd.print(mv2);
   lcd.write(' ');
   
   if(mv3 < 10)lcd.print(" ");
   lcd.print(mv3);
   lcd.write(' ');
   
   if(mv4 < 10)lcd.print(" ");
   lcd.print(mv4);
   lcd.write(' ');
   
   if(mv5 < 10)lcd.print(" ");
   lcd.print(mv5);
   lcd.print(" %");
   
   

   if(flag1 == 0){ if(mv2 > 70)flag1 = 1; }
                   if(mv2 < 60)flag1 = 0;

   if(flag2 == 0){ if(mv3 > 70)flag2 = 1; }
                   if(mv3 < 60)flag2 = 0;

   if(flag3 == 0){ if(mv4 > 70)flag3 = 1; }
                   if(mv4 < 60)flag3 = 0;

   if(flag4 == 0){ if(mv5 > 70)flag4 = 1; }
                   if(mv5 < 60)flag4 = 0;                    
   
 
/

   if( (flag1 == 0) && (flag2 == 0) && (flag3 == 0) && (flag4 == 0) )  //all close
   {
    mp3_cnt1 = 0; mp3_flag1 = 0;
    mp3_cnt2 = 0; mp3_flag2 = 0;
    mp3_cnt3 = 0; mp3_flag3 = 0;
    mp3_cnt4 = 0; mp3_flag4 = 0;
    mp3_cnt6 = 0; mp3_flag6 = 0;
   }
   else
   {
    if( (flag1 == 0) && (flag2 == 1) && (flag3 == 1) && (flag4 == 1) )  //2,3,4 - open(1), 1 - close(0)
    {
     if(mp3_flag1 == 0)
     {
      ++mp3_cnt1;

      if(mp3_cnt1 > 10)
      {
       mp3_play(1);
       delay(3000);

       mp3_flag1 = 1;
      }
     }
   
     
     mp3_cnt2 = 0; mp3_flag2 = 0;
     mp3_cnt3 = 0; mp3_flag3 = 0;
     mp3_cnt4 = 0; mp3_flag4 = 0;
     mp3_cnt6 = 0; mp3_flag6 = 0;
    }
    else if( (flag1 == 1) && (flag2 == 0) && (flag3 == 0) && (flag4 == 0) )  //1 - open, 2,3,4 - close
    {
     if(mp3_flag2 == 0)
     {
      ++mp3_cnt2;

      if(mp3_cnt2 > 10)
      {
       mp3_play(2);
       delay(3000);

       mp3_flag2 = 1;
      }
     }
   
     mp3_cnt1 = 0; mp3_flag1 = 0;
     
     mp3_cnt3 = 0; mp3_flag3 = 0;
     mp3_cnt4 = 0; mp3_flag4 = 0;
     mp3_cnt6 = 0; mp3_flag6 = 0;
    }
    else if( (flag1 == 1) && (flag2 == 1) && (flag3 == 1) && (flag4 == 0) )  //4 - open, 1,2,3 - close
    {
     if(mp3_flag3 == 0)
     {
      ++mp3_cnt3;

      if(mp3_cnt3 > 10)
      {
       mp3_play(3);
       delay(3000);

       mp3_flag3 = 1;
      }
     }
   
     mp3_cnt1 = 0; mp3_flag1 = 0;
     mp3_cnt2 = 0; mp3_flag2 = 0;
     mp3_cnt4 = 0; mp3_flag4 = 0;
     mp3_cnt6 = 0; mp3_flag6 = 0;
    }
    else if( (flag1 == 0) && (flag2 == 0) && (flag3 == 1) && (flag4 == 1) )  //1,2 - open, 3,4 - close
    {
     if(mp3_flag4 == 0)
     {
      ++mp3_cnt4;

      if(mp3_cnt4 > 10)
      {
       mp3_play(4);
       delay(3000);

       mp3_flag4 = 1;
      }
     }
   
     mp3_cnt1 = 0; mp3_flag1 = 0;
     mp3_cnt2 = 0; mp3_flag2 = 0;
     mp3_cnt3 = 0; mp3_flag3 = 0;
     
     mp3_cnt6 = 0; mp3_flag6 = 0;
    }
    else if( (flag1 == 1) && (flag2 == 1) && (flag3 == 1) && (flag4 == 1) )  //1,2,3,4 - open
    {
     if(mp3_flag6 == 0)
     {
      ++mp3_cnt6;

      if(mp3_cnt6 > 10)
      {
       mp3_play(6);
       delay(3000);

       mp3_flag6 = 1;
      }
     }
   
     mp3_cnt1 = 0; mp3_flag1 = 0;
     mp3_cnt2 = 0; mp3_flag2 = 0;
     mp3_cnt3 = 0; mp3_flag3 = 0;
     mp3_cnt4 = 0; mp3_flag4 = 0;
     
    }
   
   }
       
   ms_cnt = 0;
  }  
   
  delay(10);
