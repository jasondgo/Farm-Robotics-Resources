/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      5/30/2023, 2:45:58 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;


/*

Defined same as motor except its an optical sensor so you use optical

*/

optical opticalSensor = optical(PORT20);
motor testMotor = motor(PORT10);

void run(){
    testMotor.spinFor(1, rotationUnits::rev);
}


int main() {

   opticalSensor.gestureEnable(); // Go to line 134 to see what dis do

   opticalSensor.objectDetectThreshold(1); // Go to line 164 to see what dis do
   
  
 
    while(true) {
    
    /*
    
    To get the hue of an object: opticalSensor.hue()
    This returns a number from 0 to 359. These numbers correspond to a range of colors. To see what color each number
    corresponds to you can go to 'devices' on your v5 brain, click on the optical sensor, and it will show you what hue
    the sensor currently see's and what number that corresponds to.

    Also just go to this link to see a visual of the color scale: https://kb.vex.com/hc/en-us/articles/360051005291-Using-the-V5-Optical-Sensor
    

    */

   /*
   
     When you look at the scale you can find the range of values which correspond to a specific color. With this information,
     you can get a hue value from the sensor using opticalSensor.hue() and then check to see if its in the range of the color
     you want. This can be used in an if else statement to run certain commands if a specific color is spotted by the optical
     sensor.
   
   */

   /*
  
    In the example, below I check to see if the hue value returned falls in the range of 0 to 20. If you look at the color scale,
    this roughly corresponds to the color red. So if the sensor returns a value between 0 and 20, the color of the object in front of 
    the sensor is red. By checking if the hue value returned by the sensor is from 0 to 20, I am bascally asking "Is the object in front of the sensor red?".
    If this happens to be true, run some code, otherwise run a different code.
  
   */

      if(opticalSensor.hue() > 0 && opticalSensor.hue() < 20 ){
        run();
       } else{
        testMotor.spin(directionType::fwd, 0, percentUnits::pct);
      }

    


    
    /*
    
     To detect if an object is near: opticalSensor.isNearObject() 
     This returns a true value if an object is near which can be used to run a code when used in a conditional


     To detect if an object is near: opticalSensor.objectDetected(function)
     This does not return a value but rather runs a function you pass in, when an object is detected


     These two have a relationship to each other similar to that of pressing() vs pressed() for button control.
     They essentially do the same thing in a slightly different way.


     To detect if an object has moved from the view of the optical sensor: opticalSensor.objectLost(function)
     This does not return a value but rather runs a function you pass in, when an object that was in view of the sensor
     is no longer in view of that sensor. If there is no object in front of the sesnor initially, this will still not run the function.
     Only once an object enters the view and the leaves will the function you passed run. 



    
    */

    opticalSensor.objectDetected(run); 

       if(opticalSensor.isNearObject()){
        run();
    }

     opticalSensor.objectLost(run);


    /*
    
    Setting adjustments for optical sensor

    Turn on led light: opticalSensor.setLight(ledState::on)

    Set the intensity of the led light: opticalSensor.setLightPower(0 to 100);
    Enter a value from 0 to 100 in parenthesis. Represents the intensity of the light you want on a scale of 0 to 100%

    */

     opticalSensor.setLight(ledState::on);
     opticalSensor.setLightPower(10);


   /*
   
     The optical sensor also has the ability to sense specific types of movements. Like if you want to do something
     only if the object moves up, or to the left. This is called a gesture.

     To do this you first need to enable gestures: opticalSensor.gestureEnable();

     To recognize upwards motion: opticalSensor.gestureUp(function)
     This doesn't return a value but rather runs a function you pass in, when an object in the view of the optical sensor
     moves upwards.

     To recognize downwards motion: opticalSensor.gestureDown(function)
     This doesn't return a value but rather runs a function you pass in, when an object in the view of the optical sensor
     moves downwards.

     To recognize leftwards motion: opticalSensor.gestureLeft(function)
     This doesn't return a value but rather runs a function you pass in, when an object in the view of the optical sensor
     moves leftwards.

     To recognize rightwards motion: opticalSensor.gestureRight(function)
     This doesn't return a value but rather runs a function you pass in, when an object in the view of the optical sensor
     moves rightwards.


     CAUTION: When I test basic tests, trying different gestures it just recognized motion in general.
     Meaning in your code you could use opticalSensor.gestureUp(function) but it would run the function
     if the object moves left, right, or down. Basically, it doesn't work that good.
   
   */

    


   /*
   
    You can adjust the sensitivity of object detection using: opticalSensor.objectDetectThreshold(1 to 255)
    I can't find the whether the scale is from most sensitive to least sensitive, meaning if you enter 1 it makes
    the sensor as sensitive to object detection as possible and 255 least sensitive to object detection. OR if its the 
    other way. 

    Seemingly, based on my tests 1 is most sensitive and 255 is least sensitive

    Changing the objectDetectThreshold() value has effects on multiple functions and some of which
    don't make sense. But this is only based on the test I ran.
        
         isNearObject() doesn't really work at all when objectDetectThreshold(255)
         isNearObject() always detects an object (even if one is not there) when objectDetectThreshold(1)
         objectDetected(function) didn't work for any value I used with objectDetectThreshold()
         objectDetectThreshold() also effects ability to detect object of specific color()


  
  
   */

   /*
   
    Instead of opticalSensor.hue() you can use opticalSensor.color(). opticalSensor.color() returns the color name
    of the color of the object in view of the optical sensor. Vex has 12 predefined colors you can use to compare to the color
    recognized by the sensor.
    
    If you want to run code based on the color of an object:

     if(opticalSensor.color() == color::red ){
        run();
    }

    So to access the predefined color you type color:: then the color you want. Just as shown in the if statement above
     
   
   */

    
    }
}
