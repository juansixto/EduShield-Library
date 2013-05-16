/*
 Motor.h - DC and stepper motor library for Arduino
 Copyright (c) 2012 Juan Jose Echevarria.  All right reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Arduino.h> 
#include "Motor.h"

DCMotor::DCMotor(int dir,int speed){
	this->dir=dir;
	this->speed=speed;
	pinMode(this->dir,OUTPUT);
	pinMode(this->speed,OUTPUT);
}

StepMotor::StepMotor(int pin1,int pin2,int pin3,int pin4){
  this->step_number = 0;
  this->speed = 0;
  this->dir = 0;
  this->last_step_time = 0; 
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pin3 = pin3;
  this->pin4 = pin4;
  pinMode(this->pin1, OUTPUT);
  pinMode(this->pin2, OUTPUT);
  pinMode(this->pin3, OUTPUT);
  pinMode(this->pin4, OUTPUT);
}

void StepMotor::begin(long numSteps)
{
	this->steps = numSteps;
}

void StepMotor::setSpeed(long whatSpeed)//rpm
{
  this->step_delay = 60L * 1000L / this->steps / whatSpeed;
}

void DCMotor::forward(int value)
{  
  digitalWrite(this->dir,HIGH);    
  if(value < 0)
    analogWrite(this->speed,0);      
  if(value>255)
	analogWrite(this->speed,255);
  analogWrite(this->speed,value);
  delay(10);
}

void DCMotor::backward(int value)
{  
  digitalWrite(this->dir,LOW);   
  if(value < 0)
    analogWrite(this->speed,0);      
  if(value>255)
	analogWrite(this->speed,255);
  analogWrite(this->speed,value);
  delay(10);
}

void DCMotor::stop()
{
	analogWrite(this->speed,0);
}

//move stepper 'num' positions
void StepMotor::moveSteps(int num)
{  
  int steps_left = abs(num); 
  if (num > 0) {this->dir = 1;}
  if (num < 0) {this->dir = 0;}
    
    
  while(steps_left > 0) {
  if (millis() - this->last_step_time >= this->step_delay) {
      this->last_step_time = millis();
      if (this->dir == 1) {
        this->step_number++;
        if (this->step_number == this->steps) {
          this->step_number = 0;
        }
      } 
      else { 
        if (this->step_number == 0) {
          this->step_number = this->steps;
        }
        this->step_number--;
      }
      steps_left--;
      moveDir(this->step_number % 4);
    }
  }
}

//move motor in the proper direction
void StepMotor::moveDir(int step)
{
    switch (step) {
      case 0:    // 1010
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      break;
      case 1:    // 0110
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      break;
      case 2:    //0101
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      break;
      case 3:    //1001
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      break;
    } 
}

StepMotor Stepper(DC_DIR_1,DC_DIR_2,DC_SPEED_1,DC_SPEED_2);
DCMotor M1(DC_DIR_1,DC_SPEED_1);
DCMotor M2(DC_DIR_2,DC_SPEED_2);
