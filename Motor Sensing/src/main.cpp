/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      6/9/2023, 11:03:40 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

controller controller1 = controller(controllerType::primary);
//Create motor at port 18 using a 18:1 cartridge (green)
motor exampleMotor = motor(PORT18, gearSetting::ratio18_1);

/*

Vex Motor class offers many ways to gather information/data on the motors as they run. This data could be useful during
the match or could be saved onto an SD card to review match performance 

*/

void done(){
   Brain.Screen.clearLine();
   if(exampleMotor.isDone()){
       Brain.Screen.print("Motor has reached position");
   } else {
       Brain.Screen.print("Motor has NOT reached position");
   }
}

void getDirection(){
   Brain.Screen.clearLine();
   
   if(exampleMotor.direction() == directionType::fwd){
     Brain.Screen.print("Motor is spinning forward");
   } else if(exampleMotor.direction() == directionType::rev){
     Brain.Screen.print("Motor is spinning backward");
   } else{
     Brain.Screen.print("Motor is NOT spinning");
   }
  
}

int main() {

   /*
   
     When you spin a motor to specific position or distance (spinFor() or spinTo()), isDone() will return false if the motor
     has yet to reach its target. Returns true if it has already reached its target already.

     exampleMotor.isDone() 
   
   */

  /*
   
    When your spinning a motor, direction() will return what direction the motor is spinning. 
    It returns it as a directionType, which means you can't directly print it to the screen. However you can
    use an if statement like I did in my getDirection() function to check what direction its spinning, and then use that
    information accordingly.

    if(exampleMotor.direction() == directionType::fwd) -> If motor is spinning forward

    If the motor is NOT spinning then exampleMotor.direction() will return undefined or directionType::undefined

    direction() considers fwd (forward) to be whatever you set it to be when you create the motor. Meaning if you reverse
    the motor, that reverse direction (opposite to the direction of the arrow on back of motor) is considered fwd.
    
    exampleMotor.direction()
  
  */

   /*
   
    If you want to get the velocity of a motor use velocity(). It returns the velocity of the motor in the velocity
    units of your choice. 

    Either: 
    dps -> degrees per second 
    rpm -> revolutions per minute
    pct -> percentage of max velocity

    exampleMotor.velocity(velocityUnits::rpm);


    If you want to get the current being supplied to a motor, use current()

    Returns current supplied to motors in amps

    exampleMotor.current();

    If you want to get power being drawn by a motor, use power()

    Returns power drawn by motor in watts

    exampleMotor.power()

    If you want to get torque of motor, use torque()

    Returns torque of motor

    torqueUnits 
    Nm -> newton meters
    InLb -> lbs foot

    exampleMotor.torque(torqueUnits::Nm);

    If you want to get the motor efficiency, (ratio of power output to power input) use efficiency()

    Returns a value in percentageUnits (0 to 100)

    exampleMotor.efficiency();

    To get the temperature of a motor, use temperature()

    Returns a value in temperatureUnits (celsius or fahrenheit)

    exampleMotor.temperature(temperatureUnits::fahrenheit);

    
    To get the voltage being supplied to the motors, use voltage()

    Returns voltage being supplied to motor

    exampleMotor.voltage()


   
   */

   exampleMotor.spinTo( 3, rotationUnits::rev, false);
   
   
    while(1) {
        controller1.ButtonA.pressed(done); //If button A is pressed, print to brain whether the example motor has reached its target or not
        controller1.ButtonB.pressed(getDirection); //If button B is pressed, print the direction that the motor is spinning
    }
}
