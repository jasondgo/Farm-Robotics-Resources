/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      5/30/2023, 12:08:57 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;


/*

In terms of programming, the functionality of limit switches and bumpers are extremely similar
(same) as programming for buttons on a controller. There are two possible states for a limit switch/bumper,
either pressed or not pressed.

*/

/*

Like motors, you first specify what it is you are creating, either a limit (limit switch) or bumper, and then give 
it a name. In the parenthesis, you specify the port which the limit or bumper is plugged into. The syntax for this looks different
than for a motor. The limit switch and bumper use three wire cables, so they use the ports on the side of the brain lableled 
A thru H.

To specify a port for a limit switch or bumper, type Brain.ThreeWirePort. and then letter which corresponds to 
the port you used.


*/

limit limitSwitch = limit(Brain.ThreeWirePort.H);
bumper testBumper = bumper(Brain.ThreeWirePort.A);
motor testMotor = motor(PORT1);
motor testMotor2 = motor(PORT11);




void runOnRelease(){
    testMotor.spinFor(directionType::fwd, 1, rotationUnits::rev);
}

void runOnPress(){
    testMotor2.spinFor(directionType::fwd, 1, rotationUnits::rev);
}



int main() {
    
    
    while(true) {
        
     /*
       There three ways to access the state of a limit switch and bumper: pressing(), pressed(), and released()

       pressing() and pressed() work the same way here as they do for buttons on a controller.

       Pressing() -> Returns a true or false value. True if the limit/bumper is pressed otherwise false. Used to
       run code in an if statement

       Pressed() -> Doesn't return a value. Instead you pass it a function so that when the limit/bumper is pressed
       it runs that function.

       Released() -> Similar to pressed(), released() doesn't return a value but rather runs a function that you pass
       to it. Different from both pressed() and pressing(), released() runs the function when the bumper is released
       from being pressed. If the limit/bumper is in an unpressed state it doesn't run the code either.
       Again, only after being released.
     
     
     */

        testBumper.released(runOnRelease);
        testBumper.pressed(runOnPress);

        if(limitSwitch.pressing()){
         testMotor.spinFor(directionType::fwd, 1, rotationUnits::rev);
        }


    }
}
