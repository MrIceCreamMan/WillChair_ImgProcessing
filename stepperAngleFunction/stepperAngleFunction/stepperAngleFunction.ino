
int dirpin = 2;
int steppin = 5;

int a = 0 ;

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
 a = 0;
 Serial.begin(9600);

 pinMode(dirpin, OUTPUT);
 pinMode(steppin, OUTPUT);
}


void loop()
{

  Serial.println(a);

  if(a == 0)
  {
   move_by(180) ;
  }

  if( a == 1)
  { 
  move_by(100);
  }
  
  a++;
 
 delay(1000);
  
 
}
