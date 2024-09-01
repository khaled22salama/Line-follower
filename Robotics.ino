#include <Servo.h>
  Servo Hold_Drop;
  Servo Up_Down;
/* --------- Motors pins ------------*/
// right motor pins
#define right_motors_pwm_pin 5
#define right_motors_fowrad  9
#define right_motors_back    10

// left motors pins
#define left_motors_pwm_pin  6
#define left_motors_forward  A3
#define left_motors_back     A4

/*------------- Sensors Pins --------*/
#define front_s    2    
#define middel_s   4
#define middel_r1  7
#define middel_r2  8
#define middel_l1  12
#define middel_l2  13
#define back_s     A0  

/*---------- Arm Motors ----------*/
#define hold_Drop_motor 3
#define Up_Down_motor   11

/*----------PWM Value -------*/
#define PWM_DC     180
/*-------------- movement macros for Bleutooth----------*/
#define forwrad     'f'
#define back        'b'
#define turn_right  'r'
#define turn_left   'l'
#define _stop       's'
#define arm_up      'u'
#define arm_down    'd'
#define hold        'h'
#define drop        'p'

/*------------Modes Received From Bluetooth-----------*/
#define Transporter_Mode   'T'
#define Line_Follower_Mode 'L'

/*------------ Mode leds -----------------------*/
#define Transporter_Mode_Led   A1
#define Line_Follower_Mode_Led A2


/* -----------Variables---------*/
int Bluetooth_Data ;
int mode            = 'T';
int up_down_angle   =  0;
int hold_drop_angle =  0;





void setup() 
{
//declare IR sensors pins as input
pinMode(front_s,   INPUT);
pinMode(back_s,    INPUT);
pinMode(middel_s,  INPUT);
pinMode(middel_r1, INPUT);
pinMode(middel_r2, INPUT);
pinMode(middel_l1, INPUT);
pinMode(middel_l2, INPUT);

// Led for determine which mode is activated 
pinMode(Line_Follower_Mode_Led, OUTPUT);
pinMode(Transporter_Mode_Led,   OUTPUT);

// declare motor pins as output
pinMode(right_motors_fowrad,  OUTPUT);
pinMode(right_motors_back,    OUTPUT);

pinMode(left_motors_forward,  OUTPUT);
pinMode(left_motors_back,     OUTPUT);

Hold_Drop.attach(hold_Drop_motor);
Up_Down.attach  (Up_Down_motor  );

/*----------------------*/

  Up_Down.write(0);
  Hold_Drop.write(0);

Serial.begin(9600);
delay(500);
}

void loop()
{
// checking for any received data  
if(Serial.available())
{ 
 //if some date is sent, reads it and saves in state     
  Bluetooth_Data = Serial.read();
}

     if(Bluetooth_Data == Line_Follower_Mode) //Auto Line Follower Command
     {
       mode=Line_Follower_Mode;
      }   
     if(Bluetooth_Data == Transporter_Mode  ) //Manual Android Application Control Command
      {
        mode=Transporter_Mode;
      }   

  
  if ( mode == Transporter_Mode )  // transporter mode 
  {
    
        Stop();
        digitalWrite(Transporter_Mode_Led,   HIGH);
        digitalWrite(Line_Follower_Mode_Led, LOW);
     
  // Movement control
  switch(Bluetooth_Data)
  {
    
       case (forwrad)   :       { Forward();    break; } // if the Bluetooth_Data is '1' the motor will go forward
       case (back)      :       { Back();       break; } // if the Bluetooth_Data is '2' the motor will Reverse
       case (turn_right):       { Turn_Right(); break; } // if the Bluetooth_Data is '3' the motor will turn right
       case (turn_left) :       { Turn_Left();  break; } // if the Bluetooth_Data is '4' the motor will turn left
       case (_stop)     :       { Stop();       break; } // if the Bluetooth_Data    '5' the motor will Stop

       case (arm_up)    :       { Arm_Up();     break; } // if the Bluetooth_Data    '6' Arm move to up
       case (arm_down)  :       { Arm_Down();   break; } // if the Bluetooth_Data    '7' Arm move to dowm
       case (hold)      :       { Hold();       break; } // if the Bluetooth_Data    '8' Arm hold object
       case (drop)      :       { Drop();       break; } // if the Bluetooth_Data    '9' Arm drop object
  } 
  
  }

/*-------------------------------------------------------------------*/
/*--------------------- Line Follower Condition  -------------------*/
/*-----------------------------------------------------------------*/

  if ( mode == Line_Follower_Mode ) // line follower
  {
     digitalWrite(Transporter_Mode_Led,   LOW);
     digitalWrite(Line_Follower_Mode_Led, HIGH);
     
      if ((( (digitalRead(front_s)   == 1) && (digitalRead (middel_s ) == 1)  && (digitalRead (back_s) == 1) )|| 
           ( (digitalRead(front_s)   == 1) && (digitalRead (back_s )   == 1) )||
           ( (digitalRead(back_s)    == 1) && (digitalRead (middel_s ) == 1) )||
           ( (digitalRead(front_s)   == 1) && (digitalRead (middel_s ) == 1) ) /*for the middel sensors */)&&
           (((digitalRead(middel_l1) == 0) && (digitalRead (middel_l2) == 0)   /*for right sensors*/      )&&
             (digitalRead(middel_r1) == 0) && (digitalRead (middel_r2) == 0)   /*for right sensors*/      )
       //   ((digitalRead(middel_r1) == 1) && (digitalRead(middel_l1) == 1))  for second condition "right and left secsors"
                                                                                                          )/* for if*/ 
           
            {
             Forward();    // if any sensor from this group (front_s or middel_s or back_s) detect a line, go forward 
            }/* for if "forward condition"*/
    /*____________________________________________________________________________________________________________________________________*/

       if ( ((digitalRead(middel_r1) == 1) || (digitalRead (middel_r2) == 1))&&
            ((digitalRead(middel_l1) == 1) || (digitalRead (middel_l2) == 1))&&
             (digitalRead(front_s)   == 1))
            {
              Forward();
            } /* else if "forward condition"*/
    /*_____________________________________________________________________________________________________________________________________*/
  
     if ( ((digitalRead(middel_r1) == 1) || (digitalRead (middel_r2) == 1))&&
          ((digitalRead(middel_l1) == 1) || (digitalRead (middel_l2) == 1))&&
           (digitalRead(front_s)   == 0))
            {
              Turn_Right();
            } /* else if "forward condition"*/
    /*_____________________________________________________________________________________________________________________________________*/
  
    if ( ((digitalRead(middel_l1) == 1) || (digitalRead (middel_l2) == 1))&&
         ((digitalRead(middel_r1) == 0) || (digitalRead (middel_r2) == 0))&&
          (digitalRead(front_s)   == 0) )
            {
              Turn_Left();
            }/* else if "turn left condition"*/
    /*_____________________________________________________________________________________________________________________________________*/
   
    if ( ((digitalRead(middel_r1) == 1) || (digitalRead (middel_r2) == 1))&&
         ((digitalRead(middel_l1) == 0) || (digitalRead (middel_l2) == 0))&&
          (digitalRead(front_s)   == 0) )
            {
              Turn_Right();
            } /* else if "turn right condition"*/
    /*____________________________________________________________________________________________________________________________________*/
   
      if( (digitalRead (front_s ) == 0)&&
          (digitalRead (middel_s) == 0)&&
          (digitalRead (back_s  ) == 1) )
         {
          Stop();  // if the front sensour does not detect aline and 
         } /* for if "stop condition" */
  
  }/* for else if */
        
  } /*void loop*/
  


/*-------------------------------------------------------------------*/
/*---------------------------- movement functions -------------------*/
/*------------------------------------------------------------------*/


void Forward () //this function make robot go forward
{ 
 digitalWrite(right_motors_fowrad, 1);
 digitalWrite(right_motors_back,   0);
 digitalWrite(left_motors_forward, 1);
 digitalWrite(left_motors_back,    0);

 analogWrite(right_motors_pwm_pin, PWM_DC);
 analogWrite(left_motors_pwm_pin,  PWM_DC);
}

void Back() //this functionmake robot go back 
{
 digitalWrite(right_motors_fowrad, 0);
 digitalWrite(right_motors_back,   1);
 digitalWrite(left_motors_forward, 0);
 digitalWrite(left_motors_back,    1);

 analogWrite(right_motors_pwm_pin, PWM_DC);
 analogWrite(left_motors_pwm_pin,  PWM_DC);// right motors go back
}

void Turn_Right ()//this function make robot turn right
{

 digitalWrite(right_motors_fowrad, 0);
 digitalWrite(right_motors_back,   1);
 digitalWrite(left_motors_forward, 1);
 digitalWrite(left_motors_back,    0);

 analogWrite(right_motors_pwm_pin, PWM_DC);
 analogWrite(left_motors_pwm_pin,  PWM_DC);
 }
void Turn_Left () // this function make robot turn left
{
 digitalWrite(right_motors_fowrad, 1);
 digitalWrite(right_motors_back,   0);
 digitalWrite(left_motors_forward, 0);
 digitalWrite(left_motors_back,    1);

 analogWrite(right_motors_pwm_pin, PWM_DC);
 analogWrite(left_motors_pwm_pin,  PWM_DC);
 }
void Stop() //this function make robot stop
{
 digitalWrite(right_motors_fowrad, 0);
 digitalWrite(right_motors_back,   0);
 digitalWrite(left_motors_forward, 0);
 digitalWrite(left_motors_back,    0);

 analogWrite(right_motors_pwm_pin, 0);
 analogWrite(left_motors_pwm_pin,  0);
 }


/*-------------------------------------------------------------------*/
/*---------------------------- Arm functions -----------------------*/
/*-----------------------------------------------------------------*/

void Arm_Up()  // make arm up
{
Up_Down.write(70);
}

void Arm_Down() // make arm down
{
  Up_Down.write(0);
}
void Drop () // make arm hold object
{
Hold_Drop.write(0);
}
void Hold () // make arm drop object
{
  Hold_Drop.write(30);
}    
