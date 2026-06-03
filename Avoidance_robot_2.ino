#include <Servo.h>

Servo myServo;

int trigPin = 13;
int echoPin = 11;

long getDistance()
{
  long total = 0;
  int validReadings = 0;
  
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long Duration = pulseIn(echoPin, HIGH);
    long d = Duration * 0.034 / 2;
    
    if(d > 2)
    {
      total = total + d;
      validReadings = validReadings + 1;
    }
    delay(10);
  }
  
  if(validReadings == 0) return 999;
  return total / validReadings;
}

void forward()
{
  analogWrite(10, 255);  
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
  analogWrite(5, 255);  
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
}

void reverse()
{
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
}

void stopMotors()
{
  digitalWrite(10, LOW);
  digitalWrite(5, LOW);
}

void right()
{
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
}

void left()
{
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
}

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  myServo.attach(6);
  myServo.write(90);
  Serial.begin(9600);
}

void loop()
{
  long distance = getDistance();
  Serial.println(distance);

  if(distance > 2)
  {
    if(distance > 25)
    {
      forward();
    }
    else
    {
      stopMotors();
      delay(300);
      reverse();
      delay(400);
      stopMotors();

      myServo.write(180);
      delay(500);
      long RightDistance = getDistance();

      myServo.write(0);
      delay(500);
      long LeftDistance = getDistance();

      myServo.write(90);
      delay(300);

      if(RightDistance > LeftDistance)
      {
        right();
        delay(300);
      }
      else
      {
        left();
        delay(300);
      }
    }
  }
}