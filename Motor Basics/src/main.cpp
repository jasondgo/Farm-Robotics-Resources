/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      5/26/2023, 1:03:18 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <iostream>
using namespace vex; // Have to include this, otherwise you have to put vex:: infront of stuff


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// Define your global instances of motors and other devices here

/*
 This is how you create a controller. 
 You have to specify whether it is the primary or partner controller
*/

controller testController = controller(controllerType::primary);

/*

When you create a motor, in the parentheses you put the "port number". There are pre-built terms
you can use like I did for each port. Or you can just enter in the port number as a literal number. But If
you enter the port number as a number it starts at 0. So port 1 corresponds to 0, port 2 corresponds to 1
so on and so forth

*/

motor testMotor = motor(PORT1); 
motor testMotor2 = motor(PORT11, true); //Motor is reversed
motor testMotor3 = motor(0, gearSetting::ratio18_1); // This corresponds to a motor connected to port 1 and has gear cartridge with 18:1 ratio

/* 

On the physical motor, there is an arrow indicating the default forward spin direction. There may be 
an instance where you want to reverse the forward direction of rotation. You can do this when you instantiate the motor
or later on.

*/

/*

On the backend they are basically asking "Is this motor reversed?". If you don't answer the question aka
you dont put true, it is reversed, or false, its not reversed, then they assume false automatically. And so the motor 
just assumes forward to be the same direction as that arrow

*/

/*

Vex V5 motors ship with an 18:1 gear cartridge. When instantiating (creating) a motor you NEED to specfiy the 
gear cartridge in the motor. Simply add it after the port -> motor exampleMotor = motor(PORT1,gearSetting::ratio18_1);

Red Cartridge -> 36:1
Green Cartridge -> 18:1
Blue Cartridge -> 6:1


*/

 


void currentPosition(){
  Brain.Screen.print("Current Rev: ");
  Brain.Screen.print(testMotor.position(rotationUnits::rev));
  Brain.Screen.newLine();
}

void runDistance(){
  testMotor.spinFor(directionType::fwd, 1, rotationUnits::rev);
  Brain.Screen.clearScreen();
  currentPosition();
   
}

void runToPosition(){
  testMotor.spinTo(1, rotationUnits::rev);
  Brain.Screen.clearScreen();
  currentPosition();
   
}

 


int main() {

//If you want to reverse the motor later on use setReversed() as seen below
//testMotor.setReversed(true);

/*

Not sure of exact definition but general guidline

Coast - No braking of any sort when motor is not running
Brake - Weak resistance against motion when motor is not running
Hold - Uses a PID loop to resist any motion. Basically if you try to move a shaft manually the motor will run in reverse to maintain set position
*/

testMotor.setStopping(brakeType::hold); // Look at braking definitions





/*

To get input from the controller we specify the controller name, the button or joystick axis, and 
what kind of "state" we want to obtain from the button or joystick axis. For example, a button has two states,
its either pressed or its not pressed.

*/

 

while(true){
 

/*

There are two different ways we can get the state of a button, pressing() or pressed().
Pressing() returns a true or false value. If you press on the button it returns true and otherwise returns false.
You can use this in an if statement so that when you press the button, it returns true, and runs the code in the if statement

*/

/*

Line 123 - 127
If the Y button on the controller is being pressed/held down, run the motor at 100% velocity. Otherwise don't run
the motor (0% of the motors max velocity equals 0 and a velocity of 0 means the motor does not spin)

*/

if(testController.ButtonY.pressing()){
  testMotor2.spin(directionType::fwd, 100, velocityUnits::pct);
} else{
    testMotor2.spin(directionType::fwd, 0, velocityUnits::pct);
}


/*

Pressed() does not return a true or false value. Pressed() takes in a function as an argument (input) so that
when the button is pressed in runs that function.

*/ 

/*

Line 145: If button A is pressed run the code inside the function runDistance (runDistance can be found at line 62)
Line 146: If button X is pressed run the code inside the function runToPosition (runToPosition can be found at line 69)

*/

testController.ButtonA.pressed(runDistance); //Callback function
testController.ButtonX.pressed(runToPosition); //Callback function


/*

Rotational Units: 

raw = ticks
rev = revolutions
deg = degrees

11W Motor
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears

5.5W Motor
960 ticks/rev

For further understanding of rotational units, go to corresponding youtube video. Can be reached at the youtube channel linked in the jasondgo
github "homepage"

*/

/*

Throughout this file you have likely seen the use of spinFor() and spinTo(). 

spinFor() -> Runs a specific amount/distance
spinsTo() -> Runs to a specific position

There are a multitude of spinFor() and spinTo() functions which all work as described in line 175/176, but take in different
arguments (inputs). 

I will go through all of the different versions in the next file in the series/order
 
*/






 
 

}
}


 