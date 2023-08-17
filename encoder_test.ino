  #include <Wire.h>
#include "DFRobot_LCD.h"
#define clk 8
 #define data 9
const int stepPin = 3; 
const int dirPin = 4; 
const int forwards = 52;
const int backwards = 50;
const int save_value = 48;
const int go_to_value = 46;
const int zero = 44;
int track_val = 0;
  int saved_val = 0;
 int counter = 0; 
 int State;
 int LastState;  
 DFRobot_LCD lcd(16,2);  
 byte arrow[8] = {
    0b00000,
    0b00000,
    0b00100,
    0b00110,
    0b11111,
    0b00110,
    0b00100,
    0b00000
};
int submenu = 0;
int page = 1;
int pushed = 0;
 void setup() { 
  lcd.init();
  //Define the pins as inputs
   pinMode (clk,INPUT);
   pinMode (data,INPUT);   
   Serial.begin (9600); //Start serial com so we could print the value on the serial monitor
   // Reads the initial state of the clock pin
   LastState = digitalRead(clk);   
    #if 1   
    // create a new character
    lcd.customSymbol(1, arrow);
    #endif 
     //Print the first page menu.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write(1); 
    lcd.print("Move Left");
    lcd.setCursor(0,1);
    lcd.print(" Move Right");
 } 
 void loop() { 
  
   State = digitalRead(clk); // Reads the "current" state of the clock pin
   // If the previous and the current state of the clock are different, that means a step has occured
   if (State != LastState){     
   // If the data state is different to the clock state, that means the encoder is rotating clockwise
     if (digitalRead(data) != State) { 
       counter ++;
       Serial.println(counter);
     } else {
       counter --;
       Serial.println(counter);
     }
     
      if(0 <= counter && counter <5){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1); 
        lcd.print("Move Left");
        lcd.setCursor(0,1);
        lcd.print(" Move Right");
        page = 1;
      }

      if(5 <= counter && counter <10){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Move Left");
        lcd.setCursor(0,1);
        lcd.write(1); 
        lcd.print("Move Right");
        page = 2;
      }

      if(10 <= counter && counter <15){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1); 
        lcd.print("Zero");
        lcd.setCursor(0,1);
        lcd.print(" Save Position");
        page = 3;
      }

      if(15 <= counter && counter <20){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Zero");
        lcd.setCursor(0,1);
        lcd.write(1);
        lcd.print("Save Position");
        page = 4;
      }

      if(20 <= counter && counter <25){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(1); 
        lcd.print("Go To Saved Position");
        
        page = 5;
      }
   }
   if(page == 1 && digitalRead(pushed) == HIGH){
    //digitalWrite(dirPin,HIGH);
    for(int x = 0; x < 10; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500); 
      track_val = track_val + 1;
    }
   }

   if(page == 2 && digitalRead(pushed) == HIGH){
    //digitalWrite(dirPin,LOW);
    for(int x = 0; x < 10; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
    track_val = track_val - 1;
    
    }
   }

   if(page == 3 && digitalRead(pushed) == HIGH){
    //track_val = 0;
   }

   if(page == 4 && digitalRead(pushed) == HIGH){
    //saved_val = track_val;
   }

   if(page == 5 && digitalRead(pushed) == HIGH){
    //go_to_saved_val(track_val,saved_val);
   }
   LastState = State; // Updates the previous state of the clock with the current state
    if(counter > 25)
    {
      counter=25;
    }
    if(counter < 0)
    {
      counter=0;
    }
 }
