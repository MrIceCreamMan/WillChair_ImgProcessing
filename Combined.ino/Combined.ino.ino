#include <elapsedMillis.h>

//actuator horizontal => actuator_one
const int relay1 = 11; 
const int relay2 = 12; 

//actuator vertical => actuator_two
const int relay3 = 6;
const int relay4 = 7;

//For the stepper motor
int dirpin = 2;  //direct pin
int steppin = 5; //step pin
int control;


int func_variable1;
int func_variable2;

elapsedMillis current_time;


//Functions for actuator_one

void extendActuatorONE() 
{
  //Serial.println("extendActuator");
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
}

void retractActuatorONE() 
{
  //Serial.println("retractActuator");
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
}


void StopActuatorONE() 
{
  //Serial.println("retractActuator");
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}


void moveFixedDistanceONE(int distance)
{
  const float actuator_speed = 6.8; 
  const float reqtime = distance/actuator_speed; 
  const uint32_t period =  (uint32_t)(reqtime * 1000);
 
while (current_time < period )
   {
       extendActuatorONE();
   }

current_time = 0;
delay(25);
StopActuatorONE();

}

void moveFixedDistanceDownONE(int distance)
{
  const float actuator_speed = 6.8; 
  const float reqtime = distance/actuator_speed; 
  const uint32_t newperiod = (uint32_t)(reqtime * 1000);
  

  while(current_time < newperiod  )
   {
      retractActuatorONE();
   }

 current_time = 0;
 delay(25);
 StopActuatorONE();

}

void singleFunctionONE(int distance)
{ 
  //moves by a mm distance
  // Initial extension is 0.75 inches
  //Hence total extension is distance + 0.75 inches
  if( distance > 0)
  {
   moveFixedDistanceONE(distance);
  }

  if(distance < 0)
  {
    int newdistance = abs(distance);
    moveFixedDistanceDownONE(newdistance);
  }
}



//Functions for actuator_two

void extendActuatorTWO() 
{
  //Serial.println("extendActuator");
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

void retractActuatorTWO() 
{
  //Serial.println("retractActuator");
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
}


void StopActuatorTWO() 
{
  //Serial.println("retractActuator");
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}


void moveFixedDistanceTWO(int distance)
{
  const float actuator_speed = 4.5; 
  const float reqtime = distance/actuator_speed; 
  const uint32_t period =  (uint32_t)(reqtime * 1000);
 
while (current_time < period )
   {
       extendActuatorTWO();
   }

current_time = 0;
delay(25);
StopActuatorTWO();

}

void moveFixedDistanceDownTWO(int distance)
{
  const float actuator_speed = 4.5; 
  const float reqtime = distance/actuator_speed; 
  const uint32_t newperiod = (uint32_t)(reqtime * 1000);
  

  while(current_time < newperiod  )
   {
      retractActuatorTWO();
   }

 current_time = 0;
 delay(25);
 StopActuatorTWO();

}

void singleFunctionTWO(int distance)
{ 
  //moves by a mm distance
  // Initial extension is 0.75 inches
  //Hence total extension is distance + 0.75 inches
  if( distance > 0)
  {
   moveFixedDistanceTWO(distance);
  }

  if(distance < 0)
  {
    int newdistance = abs(distance);
    moveFixedDistanceDownTWO(newdistance);
  }
}

void move_by(int angle)
{

  int i;
  int degree;
  degree = angle; //DECIDE ANGLE
  double angleFactor;
  
  angleFactor = abs(angle) / 360.00;
  
  double steps;
  steps = angleFactor * 6400.00; //algorithm to count necessary steps
  //Serial.print(steps);
  
  if (degree < 0)
 {
  digitalWrite(dirpin, LOW);     //set the direction
  delay(100);

  
  for (i = 0; i < steps; i++)//iterate for x microsteps (COUNTERCLOCKWISE) (6400 = 360 degrees)
  {
    digitalWrite(steppin, LOW);  
    digitalWrite(steppin, HIGH); 
    delayMicroseconds(400);      
  }  
  
  digitalWrite(dirpin, HIGH);    // Change direction.
  delay(2000);   

 }

  if (degree > 0)
{
  digitalWrite(dirpin, HIGH);    // Change direction.
  delay(100);


  for (i = 0; i < steps; i++)     // Iterate for 4000 microsteps (CLOCKWISE)
  {
    digitalWrite(steppin, LOW);  
    digitalWrite(steppin, HIGH); 
    delayMicroseconds(400);      
  }  
  
  digitalWrite(dirpin, LOW);     //change direction
  delay(2000);                            
  
  }

}






void setup() 
{
  func_variable1 = 0; //control variable for first actuator
  func_variable2 = 0; //control variable for second actuator
  control = 0;
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if( func_variable1 == 0)
  {
    func_variable1++ ;
    singleFunctionONE(-100);
  }

/*if( func_variable1 == 1 )
{ 
  func_variable1++;
  singleFunctionONE(-100);
}

if( func_variable1 == 2 )
{ 
  func_variable1++;
  singleFunctionONE(40);
}

if( func_variable1 == 3 )
{ 
  func_variable1++;
  singleFunctionONE(-20);
}*/
  
  delay(5000);

if( func_variable2 == 0)
  {
    func_variable2++ ;
    singleFunctionTWO(-100);
  }

/*if( func_variable2 == 1 )
{ 
  func_variable2++;
  singleFunctionTWO(-100);
}

if( func_variable2 == 2 )
{ 
  func_variable2++;
  singleFunctionTWO(40);
}

if( func_variable2 == 3 )
{ 
  func_variable2++;
  singleFunctionTWO(-20);
}*/

 delay(5000);

 if(control == 0)
  {
   control++;
   move_by(180) ;
  }

  if( control == 1)
  { 
    control++; 
    move_by(100);
  
  }
  

 delay(5000);
 

}
