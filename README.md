# ATIA-eduCopter
An educational platform for controlling a quadcopter using matlab

## What's in this repository? ##
This repository contains code that allow the control of a quadcopter using Matlab from a computer connected with serial (usb).  
The code is created for the STM32F401RE microcontroller and provides the following features:

* Set the speed of each one of the four motors
* Retrieve accelerometer/gyroscope values from the quadcopter's sensor
* Retrieve up to 4 analog inputs from the microcontroller

This code can be used to create a PID or other controller in matlab, and test it real time on the actual system, without
having to deploy it in the microcontroller.

## Hardware Requirements ##

The quadcopter must have 4 brushless dc motors, each controlled using a ESC with PWM (default frequency at 300 Hz). You can change 
the default settings in the Quadcopter_Settings.h file. The sensor must be an MPU6050 accelerometer/gyroscope. The microcontroller 
used, is an STM32F401RE (Nucleo package).

## Software requirements ##

A Computer running Matlab. You have to import the .m files located in the "Matlab" folder of the repository. The files contain functions
that allow reading from and writing to the quadcopter using serial communication.

You can see an example of creating a pd controller and adjusting the parameters using the analog inputs retrieved from the quadcopter

