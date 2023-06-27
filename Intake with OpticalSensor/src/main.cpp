/*

There are multiple examples in this code. For one to work, you must comment out the other.


*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

//Creates optical sensor
optical opticalSensor = optical(PORT2);

//Create intake motors
motor intakeMotor1 = motor(PORT1); //May need to reverse
motor intakeMotor2 = motor(PORT11); //May need to reverse
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


    intake.setVelocity(100, percentUnits::pct); //For example 2
   
    while(1) {
    /*
    
      There are multiple ways to recognize color with the optical sensor. Either thru hue() or color().

      opticalSensor.hue() returns a number value from 0 - 360 which corresponds to a color. To know what numbers
      corresponds to what colors, reference https://kb.vex.com/hc/en-us/articles/360051005291-Using-the-V5-Optical-Sensor
      which has an image of a color wheel with corresponding values from 0 - 360. For example, a value from 0 - 20 corresponds
      to red.

      opticalSensor.color() returns a list of predefined colors by vex. For example, to check if the optical sensor has
      a red object in front of it - > if(opticalSensor.color() == color::red). 
    
    */

     /*
     
     If color of object recognized by the optical sensor is red OR green, intake the item. If the color of 
     the object recognized by the optical sensor is blue, eject the item. 

     This only runs while the object is in view of the optical sensor. Depending on the location of the sensor 
     this may not completely intake or eject the item. If this is the case, scroll down past if-else to example 2.

     
     
     */
    
     if(opticalSensor.color() == color::red || opticalSensor.color() == color::green){
        /*

        For this example I am assuming that the orientation of
        the motors make it to where spinning them fwd will intake an item. If not just switch
        directionType to rev OR velocity to -100

        */
        intake.spin(directionType::fwd, 100, percentUnits::pct);

     }
     
     else if(opticalSensor.color() == color::blue){
        /*
        
        For this example I am assuming that the orientation of
        the motors make it to where spinning them in reverse will eject an item. If not just switch
        directionType to fwd OR velocity to -100

        */
        intake.spin(directionType::rev, 100, percentUnits::pct);

     }


     /*
     
      Another option is to run the intake for a set amount of rotations so that even after the object is out
      of view of the optical sensor, it will continue to intake or eject.
     
     */

     
    /*
    
      If you go to line 55, you will see that I used intake.setVelocity(). This is used to set the default velocity
      of the motor group. So when I tell the motors to spin to a certain distance, but never specify the velocity,
      the motor group will spin at the default velocity that you set. Notice below, that when I called intake.spinFor(),
      I never specified a velocity to spin those motors at to reach 20 revolutions. Therefore, they will spin at the 
      default velocity I set at line 55.

      If you don't specify the default velocity, the motors will spin very slow.
    
    */

    if(opticalSensor.color() == color::red || opticalSensor.color() == color::green){
        /*
        
         Spins forward for 20 revolutions
        
        */
          intake.spinFor(20, rotationUnits::rev);
    }
     
     else if(opticalSensor.color() == color::blue){
        /*
        
         Spins backwards for 20 revolutions
        
        */

        intake.spinFor(-20, rotationUnits::rev);

     }

/*

  If you want to spin the motor (or just run code at all) for any color object, then you dont necessarily need to recognize 
  the color at all, you can just recognize that there is an object in view of the optical sensor 


*/

  if(opticalSensor.isNearObject()){
    //run code
  }

  /*
  
   or you can use hue, and set the number range to correspond with all colors on the color wheel
  
  */

  if(opticalSensor.hue() > 0 && opticalSensor.hue() < 360){
    //run code
  }
     
    }
}
