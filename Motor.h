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

#ifndef Motor_h
#define Motor_h

#include <inttypes.h>

#define DC_DIR_2		13  
#define DC_SPEED_2		10     
#define DC_DIR_1		12  
#define DC_SPEED_1		11  
#define L0				4  
#define L1				5 
#define L2				6 
#define L3				7 
#define SW1				2 
#define SW2				3 

class DCMotor
{
public:
  DCMotor(int dir, int speed);
  void setSpeed(int value);
  void forward(int value); 
  void backward(int value);
  void stop();
  private:
	uint8_t dir;
	uint8_t speed;
};

class StepMotor
{
public:
  StepMotor(int pin1,int pin2,int pin3,int pin4);
  void setSpeed(long whatSpeed);
  void moveSteps(int num);
  void moveDir(int step);
  void begin(long numSteps);
  private:
	uint8_t dir;
	uint8_t speed;
	unsigned long step_delay;    // delay between steps, in ms, based on speed
    int steps;      // total number of steps this motor can take
    int pin_count;        // whether you're driving the motor with 2 or 4 pins
    int step_number;        // which step the motor is on
    // motor pin numbers:
    int pin1;
    int pin2;
    int pin3;
    int pin4; 
    long last_step_time;      // time stamp in ms of when the last step was taken
};

extern StepMotor Stepper;
extern DCMotor M1;
extern DCMotor M2;

#endif