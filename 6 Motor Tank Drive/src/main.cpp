/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      5/26/2023, 11:36:30 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <cmath>
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
controller controller1 = controller(controllerType::primary);

//Since all the motors are lined up, shouldnt need to reverse any
motor leftF = motor(20, gearSetting::ratio18_1); //front   
motor leftM = motor(9, gearSetting::ratio18_1); //middle
motor leftB = motor(10, gearSetting::ratio18_1); //back
motor rightF = motor(16, gearSetting::ratio18_1);
motor rightM = motor(12, gearSetting::ratio18_1);
motor rightB = motor(11, gearSetting::ratio18_1);


/*

Creates a group of motors so that you can assign same movement to multiple 
motors without having to write it multiple times

leftFrontMotor.spin(...)
leftFrontMotor.spin(...)
leftFrontMotor.spin(...)
leftFrontMotor.spin(...)
leftFrontMotor.spin(...)
leftFrontMotor.spin(...)

vs

leftSide.spin(...)
rightSide.spin(...)

*/

motor_group leftSide = motor_group(leftF,leftM,leftB); 
motor_group rightSide = motor_group(rightF,rightM, rightB);

/*

Even when you are not pressing on the joystick it can return a minute input values.
To get around this we can check the joystick value and set it to 0 if it is below a certain threshold.
For example, in this code I pass in the joystick value and if its less than 5 (5% input) just set it to 0.
You can set the deadband or minimum threshold for input at whatever value you want.

*/

double deadband(double val){
  if(abs(val) > 5){
    return val;
  } else{
    return 0;
  }

}





int main() {

/*

To get joystick input you specify the controller, the axis you want to get input from, and then  use position().
For example, controller1.Axis3.position() returns input when it moves on the y-axis / vertical axis
of the left joystick. Using position() return a value from -100 to 100. On a vertical axis, pushing the joystick completely
up corresponds to 100 and completely down to -100. When the joystick sits idle the value returned should be 0. On the horizontal axis, 
100 corresponds to moving the joystick completely to the right and -100 means completely to the left.

This is also why for a deadband, the value 5 represents 5% input since the values of input scale to 100.
5 / 100 = 0.05 or 5%

*/

 

while(true){

 
/*

Unlike spinTo or spinFor, spin is not based on positional information from the motor encoder. Spin() sets a spin
direction and spin velocity. It then runs continuously in that direction and velocity. So unless you set the velocity 
to 0, the motor will spin continuously

*/

/*
Different ways to control velocity:

Velocity
Voltage
Percentage

Percentage -> -100 to 100 -> percentUnits::pct
Voltage -> -12 to 12V -> voltageUnits::volt

Velocity 

velocityUnits::dps -> degrees per second
velocityUnits::pct -> percentage -> -100 to 100
velocityUnits::rpm -> rotations per minute
 
*/

/*

Since spin() is based on an input velocity we can map joystick input (which ranges from -100 to 100)
to set the motor velocity based on percentage units. Therefore a joystick input value of 20 maps to
20% motor speed.

*/

//testMotor2.spin(directionType::fwd, controller1.Axis3.position(), percentUnits::pct);
//Brain.Screen.print("RPM: ");
//Brain.Screen.print(testMotor2.velocity(velocityUnits::rpm));
//Brain.Screen.newLine();
 

double forwardDrive = deadband(controller1.Axis3.position());
double rightTurn = deadband(controller1.Axis1.position());

/*

This assumes the fwd spinning direction of each motor follows the forward direction of the robot.
If not you can reverse the motors when you create them. 

*/

leftSide.spin(directionType::fwd, forwardDrive + rightTurn, percentUnits::pct); //check motor spin direction
rightSide.spin(directionType::fwd, forwardDrive - rightTurn, percentUnits::pct); //check motor spin direction

 

}
}


 
