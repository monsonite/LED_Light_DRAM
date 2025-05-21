
// Using LED Array as light sensor

// Ken Boak - May 2025

// Runs on 5V Arduino Leonardo or equivalent

long micros_low;
long micros_high;
long pulsetime ;
int test ;
int state ;
int charge = 10;
int sensorPin = A0;   // select the input pin for the LED sensor
int sensorValue = 0;  // variable to store the value coming from the sensor



void setup() 
{
  // initialize 
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
  pinMode(14,OUTPUT);
  digitalWrite(14, LOW);
  pinMode(2,OUTPUT);
}

void loop() 
{

micros_low = micros();
digitalWrite(4, LOW);   // PWM pulse
pinMode(2,OUTPUT);
digitalWrite(2, HIGH);  // turn the charging LED on
delayMicroseconds(charge);

// Switch pin 2 mode to input and record the time to change from logic  1 to 0

pinMode(2,INPUT);
state = digitalRead(2);

while(state)              // Logic state of Pin 2
{
state = digitalRead(2);
digitalWrite(3,1-state);  // Using pin 3 as ascope probe indicator
}

micros_high = micros();

pulsetime = micros_high - micros_low ;

digitalWrite(4, HIGH);   // PWM pulse - used as test indicator

Serial.println(pulsetime/1000);


}







