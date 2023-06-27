/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      6/26/2023, 8:58:23 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

controller controller1 = controller(controllerType::primary);

//6 Motor Tank-style drivetrain
motor leftF = motor(PORT18, gearSetting::ratio6_1);  
motor leftM = motor(PORT19, gearSetting::ratio6_1); 
motor leftB = motor(PORT20, gearSetting::ratio6_1); 
//Reversed for my drivetrain setup
motor rightF = motor(PORT13, gearSetting::ratio6_1,true);
motor rightM = motor(PORT14, gearSetting::ratio6_1,true);
motor rightB = motor(PORT15, gearSetting::ratio6_1,true);

motor_group leftSide = motor_group(leftF,leftM,leftB); 
motor_group rightSide = motor_group(rightF,rightM, rightB);

/*

  How does the gps system work?

  The gps sensor uses the black and white pattern around the walls to keep track of its location on the field.
  The gps can provide an x-position, a y-position, and a heading angle of the robot. The field can be thought of 
  as a coordinate grid that ranges from -1.8 meters to 1.8 meters on the x-axis and -1.8 meters to 1.8 meters along the
  y-axis. (To see a visual representation go to: https://kb.vex.com/hc/en-us/articles/360061932711-Using-the-V5-GPS-Sensor) 
  The origin (0,0) of this coordinate system is the center of the field. The heading angle of the robot is based on how the pattern
  around the walls are setup. This differs from how the inertial sensor works. Whenever you start running a program on the robot, whichever
  direction you robot is facing when that program is started will be considered forward (0 degrees). Whereas with the gps, when you start
  running the program the heading angle returned may not be 0 degrees. So the heading angle does not change to 0 everytime you rerun a program,
  and is permanent, unless the walls of the field are rearranged.



*/




//To create gps with no specifications, all you need is the port number that the gps is plugged into
gps gps1 = gps(PORT10, -123, 109, distanceUnits::cm);//gps(PORT21, -120, 130, distanceUnits::cm);

/*

 There are two different ways to create (instantiate) a gps 

  gps( int32_t index, double heading_offset = 0, turnType dir = turnType::right );
  gps( int32_t index, double ox, double oy, distanceUnits units = distanceUnits::mm, double heading_offset = 0, turnType dir = turnType::right );  

  Because of the way these constructor functions are setup, the bare minimum I need to create a gps is the port number, just like the gps on line 32.
  But as you can see on line 38 & 39 there are many more setting choices (parameters).


  gps( int32_t index, double heading_offset = 0, turnType dir = turnType::right );

  Firstly, you must always specify the port number of the gps. You are then given two more optional settings. The second parameter
  allows you to offset the heading. So for example, the heading of the robot is at 0 degrees with no offset. If you offset the gps by
  90 degrees then the heading of your robot would now return 270 degrees and if you turned your robot 90 degrees clockwise (to the right)
  then the heading would be 0 degrees at that location. The final setting you can change is the turnType of the robot. This tells the robot what turning direction
  (right/clockwise) or (left/counterclockwise) corresponds to an increase or decrease in the heading. The default turnType is right/clockwise. 
  So for example, the heading of the robot is at 0 degrees. If you turn the robot right/clockwise, the angle will increase towards 90 degrees. If you were
  to turn the robot in the left/counterclockwise, the angle will decrease towards 270. If the turnType is changed to left, then the previous scenarion would be
  flipped. If you turned the robot to the left/counterclockwise, it would approach 90 degrees, and if you turned the robot right/clockwise it would approach 270 degrees.
  

   gps( int32_t index, double ox, double oy, distanceUnits units = distanceUnits::mm, double heading_offset = 0, turnType dir = turnType::right );  
   
   Again, first you must specify the port number of the sensor. The next two parameters are x-position and y-position offsets.
   Whatever you offset the x and y position will now become the origin. The next parameter are the units of the x and y offset. 
   This parameter is in distanceUnits, which offers 3 options for units: in (inches), mm (millimeters), and cm (centimeters).
   The units you choose are hugely important. For example, lets say you set the x-position offset to 100 and the y-position offset to 100.
   If you accidentally, set the units to centimeters instead of milimeters this will significantly affect your gps. The next two parameters were
   discussed in the previous coonstructor.

   So lets say you set your gps like -> gps gps1 = gps(PORT21, 100, 100, distanceUnits::cm);

   This creates a gps named gps1 plugged into port 21 offset in the x and y position by 100 cm (which is 1 meter). So if the origin of 
   the filed is typically the center, with the offset applied, the origin would now be 1 meter forward and 1 meter to the right.

   
*/

/*

There are multiple ways to "recieve" the angle of the robot

We can use yaw(), heading(), and rotation()


yaw() -> Returns an angle from -180 to 180 degrees. Lets say the robot is currently facing "forward" (Returning 0 degrees). If I turn the robot 
to the right, the angle will increase positively until it reaches 180 degrees. If I turn the robot to the left, then the angle will increase negatively,
until it reaches -180. Lets say, your turning right and you land at 180 degrees. If you turn anymore it will transition from 180 to -180 degrees and then
approach 0 as you continue turning. 


heading() -> Returns angle 0 to 360 degrees. Lets say the robot is currently facing "forward" (Returning 0 degrees). If I do one rotation it will now return 360 degrees.
If I turn any more it will reset back to 0.


rotation() -> Does not have a limit to the angle. Lets say the robot is currently facing "forward" (Returning 0 degrees). If I complete a rotation clockwise,
it will return 360 degrees. If I complete another rotation clockwise, it will return 720. This angle continues to increase if you turn clockwise. If you turn counterclockwise,
it will reduce the angle. So if I was at 720 degrees and I turn counterclockwise one rotation then the angle returned would be 360. If I was at 0 degrees and I turned counterclokwise
one rotation, then the angle returned would be -360.


*/



void headingAngle(){
    Brain.Screen.clearLine();
    Brain.Screen.print("Heading Angle: ");
    Brain.Screen.print(gps1.heading());
    
}

void yawAngle(){
    Brain.Screen.clearLine();
    Brain.Screen.print("Yaw Angle: ");
    Brain.Screen.print(gps1.yaw());
    
}

void rotationAngle(){
    Brain.Screen.clearLine();
    Brain.Screen.print("Rotation Angle: ");
    Brain.Screen.print(gps1.rotation());
    
}



void fieldPosition(){
    Brain.Screen.clearScreen();
    Brain.Screen.print("X-Position ");
    Brain.Screen.print(gps1.xPosition(distanceUnits::cm) / 100.0); // Centimeter / 100 = meter

    Brain.Screen.newLine();

    Brain.Screen.print("Y-Position ");
    Brain.Screen.print(gps1.yPosition(distanceUnits::cm) / 100.0); // Centimeter / 100 = meter

    
}

void setAngleZero(){
   // gps1.resetHeading();
   gps1.resetRotation();
}

void setAngle(){
   // gps1.resetHeading();
   gps1.setHeading(90, rotationUnits::deg);
}

void rotationRate(){
  Brain.Screen.clearLine();
  Brain.Screen.print("Rate of Rotation : ");
  Brain.Screen.print(gps1.gyroRate(axisType::zaxis, velocityUnits::dps));
  
}

void percievedSignal(){
  Brain.Screen.clearLine();
  Brain.Screen.print("Quality of signal : ");
  Brain.Screen.print(gps1.quality());
  
}

void accel(){
  Brain.Screen.clearLine();
  Brain.Screen.print("Acceleration in g's : ");
  Brain.Screen.print(gps1.acceleration(axisType::yaxis));
  
}

/*

If you want to set your current heading to be 0 degrees use gps1.resetHeading(). This means that if your heading was 90 degrees at the time
and you call gps1.resetHeading(), the gps will now return 0 degrees. resetHeading() only affects the angle when you call gps1.heading(). It does
not affect rotation() or yaw().

If you want to set your current rotation to be 0 degrees use gps1.resetRotation(). Works the same as gps1.resetHeading() except it applies to rotation() 
and not heading()

To set the heading to a given angle use gps1.setHeading(angle, units). So in the parameters you have to specify the value to set the current orientation (direction your facing)
to and then you have to specify the units of that value. The units are in rotationUnits which give you 3 options: deg, rev, and raw. 99.9% of scenarios will require you use deg (degrees).


To set the rotation to a given angle use gps1.setRotation(angle, units). Works the same as setHeading() except there is no limit on the degree offset.

*/

/*

To get the rate of rotation around an axis use gps1.gyroRate(axisType,velocityUnits). You have to specify what axis you want to measure rotation around. To get the rate at which your robot spins,
you would choose the z-axis. Then you have to specify the units for the rate of rotation. The choices are dps (degrees per second), rpm (revolutions per minute), and pct (percentage).

To get acceleration in g's of the robot use gps1.acceleration(axisType). You specify what axis you want to measure the acceleration on.

To set current location to origin use gps1.setOrigin(). Wherever your robot is when you use this function will set that to origin (0,0)

To see how well the gps is reading the pattern on the wall of the field use gps1.quality(). This returns a value from 0 to 100, where 100 means it see's the pattern the best
and 0 means it sees the pattern the worst. 

*/


int main() {

     


    while(1) {
        double forwardDrive = controller1.Axis3.position();
        double rightTurn = controller1.Axis1.position();

        leftSide.spin(directionType::fwd, forwardDrive + rightTurn, percentUnits::pct); //check motor spin direction
        rightSide.spin(directionType::fwd, forwardDrive - rightTurn, percentUnits::pct); //check motor spin direction

        controller1.ButtonA.pressed(yawAngle);
        controller1.ButtonB.pressed(headingAngle);
        controller1.ButtonY.pressed(rotationAngle);
        controller1.ButtonX.pressed(setAngle);
        controller1.ButtonR1.pressed(rotationRate);
        controller1.ButtonL1.pressed(percievedSignal);
        controller1.ButtonL2.pressed(accel);


    
    }
}
