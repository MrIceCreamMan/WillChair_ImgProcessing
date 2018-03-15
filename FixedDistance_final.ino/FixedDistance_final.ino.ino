#include <elapsedMillis.h>

const int relay1 = 11; 
const int relay2 = 12; 
uint32_t period;
int func_variable;
elapsedMillis current_time;

void setup() 
{

  int func_variable = 0;
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  Serial.begin(9600);

}

void extendActuator() 
{
  //Serial.println("extendActuator");
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
}

void retractActuator() 
{
  //Serial.println("retractActuator");
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
}


void StopActuator() 
{
  //Serial.println("retractActuator");
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}


void moveFixedDistance(int distance)
{
  const float actuator_speed = 6.8; 
  const float reqtime = distance/actuator_speed; 
  const uint32_t period =  (uint32_t)(reqtime * 1000);
 
while (current_time < period )
   {
       extendActuator();
   }

current_time = 0;
delay(25);
StopActuator();

}

void moveFixedDistanceDown(int distance)
{
  const float actuator_speed = 6.8; 
  const float reqtime = distance/actuator_speed; 
  const uint32_t newperiod = (uint32_t)(reqtime * 1000);
  

  while(current_time < newperiod  )
   {
      retractActuator();
   }

 current_time = 0;
 delay(25);
 StopActuator();

}

void singleFunction(int distance)
{ 
  //moves by a mm distance
  // Initial extension is 0.75 inches
  //Hence total extension is distance + 0.75 inches
  if( distance > 0)
  {
   moveFixedDistance(distance);
  }

  if(distance < 0)
  {
    int newdistance = abs(distance);
    moveFixedDistanceDown(newdistance);
  }
}

void loop() 

{

  if( func_variable == 0)
  {
    func_variable++ ;
    singleFunction(-150);
  }

/*if( func_variable == 1 )
{ 
  func_variable++;
  singleFunction(-100);
}

if( func_variable == 2 )
{ 
  func_variable++;
  singleFunction(40);
}

if( func_variable == 3 )
{ 
  func_variable++;
  singleFunction(-20);
}*/
  
  delay(15000);
} 
