/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      6/1/2023, 10:47:33 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <cmath>

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;


/*

Same code as X-Drive this time with inertial sensor 

*/


controller controller1 = controller(controllerType::primary);

/*

Just like other sensors and devices, to create an inertial sensor, you put the 
type of sensor, then sensor name of you choice, and then in the parentheses of the 
initializer you put the port where the inertial sensor is plugged into. You can use either
prelabled ports or literal integers (0 -> PORT1, 1 -> PORT2, 2 -> PORT3 ...)

*/

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

void headingChanged(){
  Brain.Screen.print("Heading has changed!");
}


void collisionOccur(axisType axis, double u, double v, double w){
  Brain.Screen.clearScreen();
  Brain.Screen.print(u);
  Brain.Screen.newLine();
  Brain.Screen.print(v);
  Brain.Screen.newLine();
  Brain.Screen.print(w);



}


int main() {


/*

Calibrate intertial sensor: inertialSensor.calibrate();


Used to calibrate the intertial sensor. The inertial sensor should be calibrated before
each match. And in some cases may have to be recalibrated during the match. 

**Explain rezeroing the heading 


*/

inertialSensor.calibrate();


int forward, rightStrafe, rotateClockwise;

while(true){

forward = controller1.Axis3.position();
rightStrafe = controller1.Axis4.position();
rotateClockwise = controller1.Axis1.position();


/*

The code below calibrates the inertial sensor if the A button on the controller is pressed. This could be 
useful if you need to recalibrate during the match. If you are going to recalibrate during a match, make sure
the robot is facing the correct direction and is not moving. Takes 2 seconds to recalibrate so the robot must be still for 2 seconds


*/

if(controller1.ButtonA.pressing()){
  inertialSensor.calibrate();
}


/*

Heading of robot is also refered to as the orientation of the robot. When the robot is calibrated,
whichever direction the inertial sensor x-axis is facing is considered to be 0 degrees. If you spin/rotate the robot
so that the inertial sensor is facing a different direction, the heading is the angle between the calibrated direction
and the current direction the inertial sensor x-axis is facing.

To get the heading of the robot: inertialSensor.heading()
Returns the angle in degrees (0 to 360)

The code below prints the heading of the robot to the screen if the button B is pressed. 

*/


if(controller1.ButtonB.pressing()){
    Brain.Screen.clearLine();
    Brain.Screen.print("Heading: ");
    Brain.Screen.print(inertialSensor.heading());
}

if(controller1.ButtonX.pressing()){
    Brain.Screen.clearLine();
    Brain.Screen.print("Rotation: ");
    Brain.Screen.print(inertialSensor.rotation());
}

 

/*

inertialSensor.rotation() works the same way as inertialSensor.heading() but instead of returning an angle 
from 0 to 360, it returns an angle that is not limited to 0 to 360 degrees. For example, if you rotated your 
robot 2 full revolutions, inertialSensor.heading() would return 0 because after two full rotations your orientation
would come back to the same direction. inertialSensor.rotation() would return 720 degrees, since 1 rotation = 360 degrees
so 2 * 360 = 720.

We can relate this to a clock (traditional clocks, the kind with arms). Once the big arm and small arm, complete a rotation
and make it back to the "12" aka (12:59), the time goes back to (1:00) instead of going to (13:00). This is similar to how
inertialSensor.heading() works. What if the time did go to (13:00) and kept going up (14:00, 15:00, ...).  Well this is similar
to how inertialSensor.rotation() works, it doesn't "restart". 

Another difference is in the direction you spin. 
**Visually show this (negative angle)


*/

/*

The code below prints the inertialSensor.angle() to the brain if the Y-Button is pressed.
The inertialSensor.angle() seems to work the exact same as inertialSensor.heading().


*/


//if(controller1.ButtonY.pressing()){
//    Brain.Screen.clearLine();
//    Brain.Screen.print("Angle: ");
//    Brain.Screen.print(inertialSensor.angle());
//}




/*

To reset the heading back to zero: inertialSensor.resetHeading()

To set the heading to a non-zero degree: inertialSensor.setHeading(0 thru 360, rotationUnits::deg)

To reset the rotation back to zero: inertialSensor.resetRotation()

To reset the rotation a non-zero value: inertialSensor.setRotation(integer value, rotationUnits::)

To reset the angle back to zero: inertialSensor.resetAngle()

To reset angle to non-zero value: inertialSensor.resetAngle(0 thru 360, rotationUnits::deg)


*/


/*

The inertial sensor can also measure how fast your robot is accelerating in a specific axis 

inertialSensor.acceleration(axisType::xaxis)
inertialSensor.acceleration(axisType::yaxis)
inertialSensor.acceleration(axisType::zaxis)

*/

/*

inertialSensor.changed(function) -> Takes in a function and runs it if the heading of the robot changes.
So if you robot rotates to a different angle, the inertialSensor.changed(function) will run the function
you passed to it.

inertialSensor.changed(headingChanged);

*/

/*

Probably don't need to worry terribly about this 

inertialSensor.collision(function(axisType, double, double, double)); -> Takes a function and runs that function
when the inertial sensor detects a collision. Different from other programs that take in a function (changed, pressed, etc) the
function you pass in has to have parameters (take in) 4 values, 1 of axisType, and 3 of double type (decimal)


inertialSensor.collision(collisionOccur);

*/

/*

To get the rate of rotation around an axis -> inertialSensor.gyroRate(axisType, velocityUnits)

So if you wanted to see how fast the robot can spin -> inertialSensor.gyroRate(axisType::zaxis, velocityUnits::dps)
When you spin the robot on the ground, you are rotating on the z-axis. 

if(controller1.ButtonY.pressing()){
    Brain.Screen.clearLine();
    Brain.Screen.print("Degree Per Second: ");
    Brain.Screen.print(inertialSensor.gyroRate(axisType::zaxis,velocityUnits::dps));
}

*/


/*

To get the roll, pitch, or yaw of the robot:

Roll: Angle about the x-axis
Pitch: Angle about the y-axis
Yaw: Angle about the z-axis -> If we were to use any of these it would be yaw(), because it returns an angle with respect
to whatever direction the heading was initialized to, just like angle(), heading(), and rotation().


inertialSensor.roll();
inertialSensor.pitch();
inertialSensor.yaw();

Yaw angle works like rotation(), it is not limited to be between 0 and 360, if you make more than one revolution, and can
return a negative value if you rotate counter clockwise

if(controller1.ButtonY.pressing()){
    Brain.Screen.clearLine();
    Brain.Screen.print("Yaw Angle: ");
    Brain.Screen.print(inertialSensor.yaw());
}

*/


int temp = forward * cos(inertialSensor.heading() * M_PI / 180) + rightStrafe * sin(inertialSensor.heading() * M_PI / 180);
rightStrafe = rightStrafe * cos(inertialSensor.heading() * M_PI / 180) - forward * sin(inertialSensor.heading() * M_PI / 180);
forward = temp;
 

leftF.spin(directionType::fwd,  max(deadband(forward + rightStrafe + rotateClockwise)) , percentUnits::pct);
leftB.spin(directionType::fwd, max(deadband(forward - rightStrafe + rotateClockwise)), percentUnits::pct);
rightF.spin(directionType::fwd,  max(deadband(forward - rightStrafe - rotateClockwise)), percentUnits::pct);
rightB.spin(directionType::fwd, max(deadband(forward + rightStrafe - rotateClockwise)), percentUnits::pct);

}
       
}
