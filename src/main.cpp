#include <Arduino.h>
#include "StepperDrivers.hpp"

const int green_button_pin = 3;//CCW for now//Pin is using a pull-down style setup
const int red_button_pin = 4;//CW for now//Pin is using a pull-down style setup







TB6600 nema17(5,6,7);//Init Stepper




void setup()
{

Serial.begin(9600);

nema17.SetPulseDelayMicroseconds(60);//Set up stepper values

pinMode(green_button_pin, INPUT);//Set pin to read push button value
pinMode(red_button_pin, INPUT);//Set pin to read push button value
}




void loop()
{


  while(digitalRead(green_button_pin) == HIGH && digitalRead(red_button_pin) == HIGH)
  {
    //If both buttons are pushed at the same time, block any action in the program. Only check pins and do action if only one button is pressed
      //Add dual button push code here
  }
      if(digitalRead(green_button_pin) == HIGH)//Check if green button is pushed and record its value. Sets button val state to green
      {
        //Add test code here
      }
      if(digitalRead(red_button_pin) == HIGH)//Check if red button is pushed and record its value. Sets button val state to red
      {
        //Add test code here
      }
 
}