/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      6/5/2023, 2:41:21 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller controller1 = controller(controllerType::primary);
int reverseMotor = 1;

// define your global instances of motors and other devices here

inertial inertialSensor = inertial(PORT5);

motor leftF = motor(0,false);
motor leftB = motor(10, false);
motor rightF = motor(9,true); 
motor rightB = motor(19,true); 


double deadband(double input){
  if(abs(input) > 5){
    return input;
  } else{
    return 0;
  }
  
}


double max(double input){
    if(input > 100){
        return 100;
    } else if(input < -100){
        return -100;
    } else{
        return input;
    }
}


void reverseMotors(){
    reverseMotor *= -1;
}

int main() {

   
   int forward, rightStrafe, rotateClockwise;

       while(true){

          forward = controller1.Axis3.position() * reverseMotor;
          rightStrafe = controller1.Axis4.position() * reverseMotor;
          rotateClockwise = controller1.Axis1.position() * reverseMotor;
        
          int temp = forward * cos(inertialSensor.heading() * M_PI / 180) + rightStrafe * sin(inertialSensor.heading() * M_PI / 180);
          rightStrafe = rightStrafe * cos(inertialSensor.heading() * M_PI / 180) - forward * sin(inertialSensor.heading() * M_PI / 180);
          forward = temp;
 
          controller1.ButtonA.pressed(reverseMotors);

          leftF.spin(directionType::fwd,  max(deadband(forward + rightStrafe + rotateClockwise)) , percentUnits::pct);
          leftB.spin(directionType::fwd, max(deadband(forward - rightStrafe + rotateClockwise)), percentUnits::pct);
          rightF.spin(directionType::fwd,  max(deadband(forward - rightStrafe - rotateClockwise)), percentUnits::pct);
          rightB.spin(directionType::fwd, max(deadband(forward + rightStrafe - rotateClockwise)), percentUnits::pct);

    }
}
