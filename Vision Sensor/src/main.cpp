/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jason                                                     */
/*    Created:      5/31/2023, 1:13:32 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
motor testMotor = motor(PORT10);


/*

These signatures are copied from vex code when you configure the vision sensor on the laptop.

*/

vision::signature GREEN_BLOCK (1, -5125, -4369, -4748, -5051, -4273, -4662, 2.500, 1);
vision::signature RED_BLOCK (2, 8953, 9971, 9462, -1247, -991, -1118, 2.500, 1);
vision::signature BLUE_BLOCK (3, -3343, -2605, -2974, 7617, 10443, 9030, 2.500, 1);
vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);

/*

This is also copied from vex code when configruing the vision sensor on the laptop

*/

vision::code GAME_PIECES (RED_BLOCK, BLUE_BLOCK, GREEN_BLOCK );

/*

Creating a vision sensor is done automatically when you configure it in vex code, so all you have to do is copy it.

To explain though, you have to specify the sensor 'vision', give the sensor a name 'visionSensor', and then you
have to initialize it. To initialize, in the parenthesis first enter the port number which the sensor is connected to,
the brightness level (scale 0 to 255), and then all the signature names (in no particular order or amount) that you copied
from vex code.

*/

vex::vision visionSensor = vision( vex::PORT19, 50, GREEN_BLOCK, RED_BLOCK, BLUE_BLOCK, SIG_4, SIG_5, SIG_6, SIG_7 );


void run(){
    testMotor.spinFor(1, rotationUnits::rev);
}


int main() {

    while(true) {
        
   /*
   
    To take a snapshot or picture: visionSensor.takeSnapshot(signature)
    This will take a snapshot of the vision sensor field of view and look for objects of the signature you specify/pass.
    This snapshot needs to be put in the while loop, so that the vision sensor will continuosuly take pictures and update
    the location of objects with a specific signature in frame.
    
    For a code to be recognized, all the signatures have to be present

   */

   // visionSensor.takeSnapshot(GAME_PIECES); code only recognized if all signatures are together
    //visionSensor.takeSnapshot(RED_BLOCK);
     
  /*
  
   Once you take a snapshot you can access information about that snapshot. 

   To get an object count with the signature you specified: visionSensor.objectCount
   No I didn't forget parentheses, objectCount is a variable in vision class

   To get the largest object with the signature specified: visionSensor.largestObject
   Often times the largest object in frame is the closest object. You can access different 
   properties of the largestObject such as originX, orginY, centerX, centerY.

   originX -> The x position of the top left portion of the largest object

   originY -> The y position of top left portion of the largest object

   centerX -> The x position of the center of the largest object

   centerY -> The y position of the center of the largest object

   visionSensor.largestObject.centerX 
   visionSensor.largestObject.centerY 
   visionSensor.largestObject.orginX 
   visionSensor.largestObject.originY 

   To get an array of the largest objects (of the signature you specified of course): visionSensor.objects[]
   Just how you would typically access an element in an array. For example, to get the 2nd largest object
   you would type: visionSensor.objects[1] (remember that indexign starts at 0)


  */

 //visionSensor.takeSnapshot(RED_BLOCK);
 // if(visionSensor.objectCount > 0 ){
    //  Brain.Screen.clearLine();
    //    Brain.Screen.print("Block found");
        
   //    run();

  //  

 /*
 
 To take snapshots of objects with multiple signatures you CANNOT just do

 visionSensor.takeSnapshot(BLUE_BLOCK);
 visionSensor.takeSnapshot(RED_BLOCK);

 This will just take a snapshot and gather data on blue block's and then immediately take a new 
 screenshot and gather data on the red block's. So if you try to visionSensor.largestObject, it will
 only return data about the largest red block since it was the most recent snapshot.

 To gather information about multiple objects with different signatures you will need to use if else statements.


 
 */


   //  if(visionSensor.takeSnapshot(RED_BLOCK)){
    //    Brain.Screen.clearLine();
    //    Brain.Screen.print("Red block found");
        
   // } else if(visionSensor.takeSnapshot(BLUE_BLOCK)){
   //     Brain.Screen.clearLine();
  //      Brain.Screen.print(visionSensor.largestObject.angle);
        

  // }


   /*
  
     The vision sensor has a resolution of 316 x 212 pixels. You can use this information along with 
     the functionality of the visionSensor.largestObject (centerX, centerY, originX, originY) to perform a
     variety of tests.

     The code below runs a motor if the the largest block seen by the vision sensor is centered horizontally in front of
     the camera with a tolerance of 10 pixels. Specifically, if the CENTER pixel (centerX) of the block is lined up with
     the center pixel of the camera view.

     If the camera has a resolution or image width of 316 pixels horizontally, this means that for an object to be centered in front
     of the camera it should be at the 158th pixel (316 / 2). Depending on how strictly you want the block to be centered, you can allow
     for the object to be offcenter by adding a certain amount of pixels to the center pixel and subtracting a certain ammount of pixels
     from the center pixel.

     In this case I took the center pixel (158) and added/subtracted 10 pixels creating a range of pixel values to be considered "center".
     "If the block is at least at pixel 148 and no greater than pixel 168 consider it centered". 

     To reiterate, adding/subtracting pixels and creating a range of "centered" values gives leeway so that the block can be
     slightly offcentered to the left OR right. 


  
   */

  //Conversion factor?
   

  // if(visionSensor.largestObject.centerX >= 148 && visionSensor.largestObject.centerX <= 168 ){
   //       Brain.Screen.clearLine();
   //       Brain.Screen.print("Block centered");
        
   //       run();
  // }


 /*
   Some settings you can change on the vision sensor

   To change the birghtness of the led on the sensor: visionSensor.setBrightness(0 to 255)

   To change the white balance: visionSensor.setWhiteBalanceValues(0 to 255, 0 to 255, 0 to 255)
   
   To change detection mode: 
      
       visionSensor.setMode(vision::detectionMode::objectDetect) -> This is default and automatically done for you

       visionSensor.setMode(vision::detectionMode::lineDetect)

       visionSensor.setMode(vision::detectionMode::mixedDetect)

       visionSensor.setMode(vision::detectionMode::test)

 */
 
   
   

    }
}
