/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      5/31/2023, 7:45:01 PM                                     */
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

Similar to the limit/bumper switch, pneumatics uses a three wire cable and so in the parentheses to specify
the port you cannot just put PORT1 or a number like a motor. You must type Brain.ThreeWirePort.  and specify 
the port (A thru H)

*/

pneumatics pneumatic = pneumatics(Brain.ThreeWirePort.A);


int main() {

   
    while(1) {


/*

Pneumatic system can only be open or closed. 

To open or extend the linear actuator: pneumatic.open()

To close or retract the linear actuator: pneumatic.close()


*/

        if(controller1.ButtonA.pressing()){
          pneumatic.open();
        } else if(controller1.ButtonB.pressing()){
          pneumatic.close();
        }
        
    }
}
