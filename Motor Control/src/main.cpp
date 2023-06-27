/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      6/8/2023, 3:25:04 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

 
//Create motor connected to port 18 and that has a gear ratio 6:1
motor exampleMotor = motor(PORT18, gearSetting::ratio6_1);
motor exampleMotor2 = motor(PORT13, gearSetting::ratio6_1);
controller controller1 = controller(controllerType::primary);



int main() {

/*

  There are three main functions used to spin the motor: spin(), spinFor(), and spinTo()

  spin() -> Allows you to run the motor based on a velocity you give it. This means it does not spin to a specific position
  and stop, but it runs the motor continuously at the velocity you specify. So, if you set the motor to a velocity, it will keep spinning
  until you set the motor velocity to 0.

  spinFor() -> Allows you to spin the motor a specific distance or amount. This means, if you tell the motor to spin for 360 degrees,
  it will spin 360 degrees (1 rotation) and stop. You can specify the velocity you want to run the motor at, in ordere to get to the position you tell it.
  But unlike spin(), when you specify the motor velocity, it runs that motor at that velocity to the distance you specify and stops. So 
  it doesn't run continuously, just to the distance you specify. 

  spinTo() -> Allows you to spin the motor to a specific position. This means, if you tell the motor to spin for 360 degrees,
  it will spin 360 degrees (1 rotation) and stop. The difference between spinTo() and spinFor(), is that if you were to call spinFor() 
  a second time, it will spin the motor 360 degrees again. If you call spinTo() a second time, it will not spin again. This is again because 
  spinTo() runs to a specific POSITION not distance. So once it is at that 360 degree position it has no need to move again. Whereas
  spinFor() spins a 360 degree DISTANCE each time.

*/
  
/*

  spin():

  spin( directionType dir );
  spin( directionType dir, double velocity, velocityUnits units );
  spin( directionType dir, double velocity, percentUnits units );
  spin( directionType dir, double voltage, voltageUnits units );

  These are all the spin() function, and in the end they all perform the same task (spin at a specified velocity). They
  differ in the inputs they take in, to acheive the same end task.

  Lets look at the spin() function on line 48 -> spin( directionType dir, double velocity, velocityUnits units ); 

  First, we need to specify the direction we want to spin the motor. Either forward or backward. Then, you specify 
  the velocity. Finally, you specify the velocity units. Either revolutions per minute (rpm) or degrees per second (dps). What this means,
  is that whenever you type in a number for the velocity, it either corresponds to revolutions per minute (rpm) or degrees per second (dps).
  For example, if I set my velocity as 60, if I say the units are rpm then the motor will spin at 60 rpm. If I say the units are dps, then the
  motor will spin at 60 dps. This is a MASSIVE difference (literally a 6x diffference in velocity), so make sure you specify the correct units.

  Lets look at the spin() function on line 49 -> spin( directionType dir, double velocity, percentUnits units );

  Similar to the other spin() function, we first need to specify the spin direction, either forward or backwards. Also like the other 
  spin() function, our second input needs to be the velocity. Finally, we enter in percentUnits. percentUnits is DIFFERENT from
  velocityUnits we used before. percentUnits offers one option, pct , which stands for percent. So our velocity input will be on a 
  scale from -100 to 100, where -100 is 100 PERCENT of the motors velocity in reverse, and 100 is 100 PERCENT of the motors velocity forward.
  For example, if I put the number 50 as the velocity, and used percentUnits, then it would run the motor at 50% of the motors top velocity.
  
  Lets look at the spin() function on line 50 -> spin( directionType dir, double voltage, voltageUnits units );

  Just like the previous two spin() functions we first need to specify the direction. The second value we enter is the amount of volts.
  This time, our units are voltageUnits, which offers the units as volts. So our voltage input will be on a scale from 0 to 12, since
  these motors run on 12V max. So if I type the number 12 in as the voltage, it will run the motor on 12 volts, which is the max voltage
  the motor runs on and therefore it runs at max velocity. If I type 6 in as the voltage, that is half of the max voltage the motor can run on,
  and therefore will run the motor at half of max veloctiy. 

*/

/*

 spinTo(): 

  spinTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
  spinTo( double rotation, rotationUnits units, bool waitForCompletion=true );

  These are the spinTo() functions and will perform the same task (spin to a specific position). They differ in there inputs,
  but will complete the same task.

  Lets look at the spinTo() function on line 85 -> spinTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
  
  First, we enter in the position we want to rotate to. Then we enter in the units for the position we specified before. Just like with spin() the 
  units you choose are important and greatly effect the outcome. For spinTo() we use rotationUnits which give us the option of degrees, revolutions,
  and ticks. So if enter in 1 as the position and say the units are in degrees, then it will spin 1 degree. If I say the position is
  revolutions, then it will spin 1 revolution. This is a MASSIVE difference (360x the distance). Next, we enter in the velocity we want to spin
  the motor at to get to that position. After that, you specify the unit of the velocity value you entered in previously.

  The final input into this spinTo() is optional. It takes a true or false input, and if you don't enter in anything it automatically takes the 
  value true. It is used to tell the brain to wait for this spinTo() function to complete, meaning the motor spins to its position. If you leave it blank
  or enter true, the motor has to spin to its position (function has to finish) before other code can run. If you enter false, then other code can run while
  that motor is running to its position. So lets imagine you want to spin two different motors to a specific position at the same time using spinTo()

  exampleMotor1.spinTo(1, rotationUnits::rev, 30, velocityUnits::rpm);
  exampleMotor2.spinTo(1, rotationUnits::rev, 30, velocityUnits::rpm);

  If use the code above, it will NOT run the motors simultaneously since I didn't give it a false input. Therefore, exampleMotor1 has to reach
  its final position before exampleMotor2 will be run.

  exampleMotor1.spinTo(1, rotationUnits::rev, 30, velocityUnits::rpm, false);
  exampleMotor2.spinTo(1, rotationUnits::rev, 30, velocityUnits::rpm);

  This code above WILL run the motors simultaneously, since I specified false in the final input. Basically, the function is asking "Do you want to wait for this function to finish before you run another?".
  By entering false, your basically saying NO, and so the exampleMotor2 can run at the same time as exampleMotor1.

*/




 /*
  
    spinFor():

    spinFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
    spinFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
    spinFor( double rotation, rotationUnits units, bool waitForCompletion=true );
    spinFor( directionType dir, double rotation, rotationUnits units, bool waitForCompletion=true );
    spinFor( double time, timeUnits units, double velocity, velocityUnits units_v );
    spinFor( directionType dir, double time, timeUnits units, double velocity, velocityUnits units_v );
    spinFor( double time, timeUnits units );
    spinFor( directionType dir, double time, timeUnits units );

    These are the spinFor() and will perform the same task (spin a speicifed distance or amount). They take in different inputs,
    but complete the same task in the end. 

    If you look at these spinFor() alot of there inputs are then same as the spin() and the spinTo() so I won't go into those.

    Lets look at the spinFor() function on line 133 -> spinFor( double time, timeUnits units );
     
    First we enter in a numerical value that represents time. Secondly, we specify the units for the time. We use timeUnits which
    has the units miliseconds and seconds. Again, using the correct units is EXTREMELY important and will give you significantly different results.

 */

/*
  If we look back at some of the spin(), spinTo(), and spinFor() function, they do not all make you specify the velocity.
  For example the spin() on line 47 and the spinTo() on line 86. So how does the brain not what speed to run the motor at?
  Well we can use the setVelocity() function in order to set a defualt velocity to spin that motor at if we don't specify in
  the spin(), spinTo(), and spinFor().

  exampleMotor.setVelocity(100, velocityUnits::rpm)

  In the line of code above, we set the default velocity of exampleMotor to spin at 100 rpm, when we don't specify it in the spin(),
  spinFor(), and spinTo().

  
*/

/*

  If you want to stop a motor while its running -> exampleMotor.stop()
  This can be used to stop a motor when its spinning using spin(), spinFor(), and spinTo()

  ** Have examples for video (using button, setting waitForCompletion=false)

*/

/*
  
 exampleMotor.setTimeout() -> Stops motor from rotating to a specific position after a specified time

 exampleMotor.setTimeout(2, timeUnits::sec);
 exampleMotor.spinTo(12, rotationUnits::rev);

 The code above sets the motor to stop running after 2 seconds. We then run our motor to spin to 12 revolutions. So the motor spins to reach its goal of 
 12 revolutions, but after 2 seconds it will stop no matter if it reaches its goal or not. If the motor reaches 12 revolutions before 2 seconds,
 then it simply reaches its goal and stops on its own. 

 Same applies when using setTimeout() with spinFor()

 If you do use setTimeout, it will NOT work if you set waitForCompletion = false
 setTimeout does not work with spin()


*/

/*

If you want to reset the position of the encoder to 0 -> exampleMotor.resetPosition()

exampleMotor.spinTo(180, rotationUnits::deg);
exampleMotor.resetPosition();

In the code, it spins the motor 180 degrees. We then reset the position to 0 so that the position we are at (180 degrees) is now
0 degrees. 

If you want to set the position of the encoder to some position that isn't 0 -> exampleMotor.setPosition()

exampleMotor.spinTo(180, rotationUnits::deg);
exampleMotor.setPosition(90, rotationUnits::deg);

In the code above, it spins the motor 180 degrees and then sets that position to now be 90 degrees
Setting the position to a new value changes that position across all units. So the if you setPosition() in degrees
it will effect also change the revolution value.


*/

exampleMotor.setVelocity(10, percentUnits::pct); //Set the default velocity of this motor to 10% of max speed
exampleMotor.spinTo(180, rotationUnits::deg); //Spins motor to position 180 degree and will spin at 10% of max speed since that is default
exampleMotor.resetPosition(); //Sets what would be the 180 degree position to now be 0 degree position
exampleMotor.spinTo(180, rotationUnits::deg); // Since we are now at 0 degree, we can run the spinTo() with 180 degrees again, which we couldn't otherwise
  
    while(1) {
      
      exampleMotor.spin(directionType::fwd); // Spins motor continuously in the forward direction at a velocity 10% of the max velocity


      while(controller1.ButtonA.pressing()){
        // If Button A is being held down, run the motor at 100% velocity. Setting to a specific velocity overrides default
         exampleMotor.spin(directionType::fwd, 100, percentUnits::pct);
      } 
      
      if(controller1.ButtonB.pressing()){
         // If Button B is being held down completely stop the motor from running
         exampleMotor.stop();
      }


       


       
        
    }
} 
