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
int reverseMotor = 1;
//Since all the motors are lined up, shouldnt need to reverse any
motor leftF = motor(PORT15); //front   
motor leftM = motor(PORT14); //middle
motor leftB = motor(PORT13); //back
motor rightF = motor(PORT20);
motor rightM = motor(PORT19);
motor rightB = motor(PORT18);


motor_group leftSide = motor_group(leftF,leftM,leftB); 
motor_group rightSide = motor_group(rightF,rightM, rightB);


double deadband(double val){
  if(abs(val) > 5){
    return val;
  } else{
    return 0;
  }

}

void reverseMotors(){
  reverseMotor *= -1;
}


int main() {



   while(true){

      controller1.ButtonA.pressed(reverseMotors);
 
      double forwardDrive = deadband(controller1.Axis3.position() * reverseMotor);
      double rightTurn = deadband(controller1.Axis1.position() * reverseMotor);
      leftSide.spin(directionType::fwd, forwardDrive + rightTurn, percentUnits::pct); 
      rightSide.spin(directionType::fwd, -forwardDrive + rightTurn, percentUnits::pct); 

 

   }
}