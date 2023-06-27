/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      6/5/2023, 12:15:37 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

/*

Limit Switched plugged into port A which is located on the side of the brain furthest from the power button.

*/
limit limitSwitch = limit(Brain.ThreeWirePort.A);

// Create controller
controller controller1 = controller(controllerType::primary);

//Create intake motors
motor intakeMotor1 = motor(PORT1, false); //May need to be reversed
motor intakeMotor2 = motor(PORT11, false); // May need to be reversed
motor_group intake = motor_group(intakeMotor1, intakeMotor2);

/*

It is not necessary to put the motors into a motor group but I am doing it so that
I only have to make 1 call to run both motors vs 2.

Meaning:

intake.spin(...);

vs.

intakeMotor1.spin(...);
intakeMotor2.spin(...);

BUT if you are going to be putting these motors in a group, they must spin in the same direction.
So either the arrow on the back of each of these motors must point in the same direction OR you 
must reverse one of the motors properly.


*/




int main() {

  
    
    while(1) {
        
       /*
       
       If both R1 and R2 button are being pressed then run the motor in reverse. For this example,
       I am assuming that the orientation of the motors make it where spinning them in reverse will make them eject an item.
       The purpose of this is to overide the limit switch, since in the condition of the if statement the state of the limit
       switch is not taken into account. 

       There are a multitude of ways to write this set of if-else statements with a multitude of different conditionals
       so that the same intake functionality occurs. 
       
       */

        if(controller1.ButtonR1.pressing() && controller1.ButtonR2.pressing()){
            intake.spin(directionType::rev, 100, percentUnits::pct);
        }

        /*
        
        If R1 button is being pressed and the limit switch is not being pressed then
        run the intake motors fwd. For this example I am assuming that the orientation of
        the motors make it to where spinning them fwd will intake an item. If not just switch
        directionType to rev OR velocity to -100
        
        */

        else if(controller1.ButtonR1.pressing() && !limitSwitch.pressing()){
          intake.spin(directionType::fwd, 100, percentUnits::pct);

        } 

        /*
        
        If R2 button is being pressed and the limit switch is not being pressed then
        run the intake motors in reverse. For this example I am assuming that the orientation of
        the motors make it to where spinning them in reverse will eject an item. If not just switch
        directionType to fwd OR velocity to -100
        
        */
        
        else if(controller1.ButtonR2.pressing() && !limitSwitch.pressing()){
          intake.spin(directionType::rev, 100, percentUnits::pct);
        } 

    }
}
