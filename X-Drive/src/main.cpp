/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      5/26/2023, 1:56:21 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
controller controller1 = controller(controllerType::primary);

/*

Some motors had to be reversed because of the way they were installed. If the motors are installed so that
the direction of rotation (which is marked on the motor) corresponds with the forward direction of the robot
then there is no need to reverse the motors in code.

*/

motor leftF = motor(0,false);
motor leftB = motor(10, false);
motor rightF = motor(9,true); // Reversed
motor rightB = motor(19,true); //Reversed


double deadband(double input){
  if(abs(input) > 5){
    return input;
  } else{
    return 0;
  }
  
}


/*

Limits the input to only be on a scale of -100 to 100. Likely unnecessary as it probably already
does this automatically if you try to put an input greater than 100 for percent units (which is -100 to 100 scale).

*/

double max(double input){
    if(input > 100){
        return 100;
    } else if(input < -100){
        return -100;
    } else{
        return input;
    }
}

int main() {

/*

forward - As the name implies, is the input responsible for driving forward and backward. Takes input
from the y-axis of the left joystick.

rightStrafe - Input responsible for moving robot right and left. Takes input from the x-axis of the
left joystick

rotateClockwise - Input responsible for spinning the robot in a clockwise direction. Takes input
from the x-axis of the right joystick

*/


int forward, rightStrafe, rotateClockwise;

while(true){

forward = controller1.Axis3.position();
rightStrafe = controller1.Axis4.position();
rotateClockwise = controller1.Axis1.position();

/*

Input is passed into deadband() first which either returns back the same input or 0 (if under threshold).
This returned value is the immediately passed to max() which either returns back the input, 100, or -100 (if above or below limit).


*/
leftF.spin(directionType::fwd,  max(deadband(forward + rightStrafe + rotateClockwise)) , percentUnits::pct);
leftB.spin(directionType::fwd, max(deadband(forward - rightStrafe + rotateClockwise)), percentUnits::pct);
rightF.spin(directionType::fwd,  max(deadband(forward - rightStrafe - rotateClockwise)), percentUnits::pct);
rightB.spin(directionType::fwd, max(deadband(forward + rightStrafe - rotateClockwise)), percentUnits::pct);

}
       
}
