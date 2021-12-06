#include <PS4Controller.h>
#include <Robojax_L298N_DC_motor.h>


/* The following section defines all of the variables and pins for motor control. 
 *  
 *    Code is explained line by line. See End of Document for GITHUB link and References
 */

#define CHA 0                      //Definition of pins for DC motor          
#define ENA 17                     //power control       
#define IN1 16                     //pwm 1
#define IN2 4                      //pwm 2

byte servoPin = 5;                 //pwm pin for servo 1
byte servoPin2 = 13;               //pwm pin for servo 2

const int CCW = 2;                 //variable to store CCW direction (Dc motor)
const int CW  = 1;                 //variable to store CW direction (Dc motor)

#define motor1 1                   //Motor definition to be referenced for motor attachment and control

Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA, true);  

void setup() 
{
  Serial.begin(115200);           //Opens Serial monitor to observe code output
  motor.begin();                  //Attaches the DC motor to the ENA,IN1, and IN2 pins
  PS4.begin("1a:2b:3c:01:01:01"); //Connects the PS4 controler to ESP32 through MAC adress created by editing the PS4's internal PS4 MAC adress.

  pinMode(servoPin, OUTPUT);      //Sets the servo pin as an output.
  digitalWrite(servoPin, LOW);    //Sets the servo's intial state to off.
  pinMode(servoPin2, OUTPUT);
  digitalWrite(servoPin2, LOW);
}

void loop() 
{
  /*
   * The following code loops 16 million times per second. These condition IF statements that make up the primary body of the code take in the inputs of the PS4 contoller using PS4Controller library and checks for
   * button presses. If a button is pressed code will execute and motors will turn.
   */

  
  if (PS4.isConnected())                                          
  {
    Serial.printf("Battery Level : %d\n", PS4.Battery());         //If the PS4 contorler is connected print the battery level out so that we can monitor it.
  }
    
  if (PS4.Right())                                               /* Control for the "Steering servos"
                                                                  */
                                                                                          
  {
    digitalWrite(servoPin, HIGH);                                //The following code creates a perioic square wave that repeats approximately every 20ms. This in turn
    delayMicroseconds(1900);    //position                       //Drives the servo. The position that the servo ends at is determined by the first delay.             
    digitalWrite(servoPin, LOW);                                 //Right,Left,Up,Upright,and Triagnle buttons all contorl servos and are all the same block of code besides thier final position
    delayMicroseconds(18100);           
  }
  if (PS4.Up()) 
  {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(1000);    //position
    digitalWrite(servoPin, LOW);
    delayMicroseconds(18900);  
  }
  if (PS4.Left())
  {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(600);    //position
    digitalWrite(servoPin, LOW);
    delayMicroseconds(18900); 
  }
                                                                  /* Control for the "Trailer DUMP servos"
                                                                  */
  if (PS4.Triangle())
  {
    digitalWrite(servoPin2, HIGH);
    delayMicroseconds(2100);  //position
    digitalWrite(servoPin2, LOW);
    delayMicroseconds(17900);   
  }
  if (PS4.UpRight())
  {
    digitalWrite(servoPin2, HIGH);
    delayMicroseconds(700);   
    digitalWrite(servoPin2, LOW);
    delayMicroseconds(19300);  
  }    
  if (PS4.Square())
  {
      motor.rotate(motor1, 100, CW);                             //Tells the DC motor to rotate at full power in the clockwise direction
  }
  if (PS4.Cross())
  {
      motor.brake(1);                                            //Tells the DC motor to diconnect (stop spinning)
  }
  if (PS4.Circle())
  { 
      motor.rotate(motor1, 100, CCW);                            //Tells the DC motor to rotate at full power in the counterclockwise direction
  }
}


//References

//
