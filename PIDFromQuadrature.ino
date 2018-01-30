/*
 */

#include <SoftPWMServo.h>
#include <PID_v1.h>

// Global variables for keeping track of position
static volatile char lastLeftA;
static volatile char lastLeftB;
static volatile bool errorLeft;
volatile long position = 0;


double input=0, output=0, setpoint=0;

// TODO: STUDENTS NEED TO FIND THE RIGHT CONTROL GAINS FOR GOOD POSITION CONTROL
double kp=1.0,ki=0.0,kd=0.0;
PID myPID(&input, &output, &setpoint,kp,ki,kd, DIRECT);

int pidSampleTime = 10;
long counter=1; // This counter is used to determine when the control loop should run


void setup() {
  
  // Set up the serial port in case we want output or input
  Serial.begin(9600);
  Serial.println("Timer Interrupt Encoder Test:");
  
  // Set up the quadrature inputs
  pinMode(2, INPUT);
  pinMode(20, INPUT);
  
  errorLeft = false;
  lastLeftA = digitalRead(2);
  lastLeftB = digitalRead(20);
  
  attachCoreTimerService(MyCallback);
  
  // Set up the motor outputs
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  digitalWrite(3,0);
  digitalWrite(4,0);
  
  SoftPWMServoPWMWrite(3, 0);
  
  
  //Setup the pid 
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(pidSampleTime);
  myPID.SetOutputLimits(-2400,2400);
  
}



void loop() {
  
  long newPosition = position;
  
  // Allow the user to change the setpoint by typing either 'a' or 'z' into the serial monitor 
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // say what you got:
    if (incomingByte == 'a')
    {
      setpoint += 300; 
    }
    else if (incomingByte == 'z')
    {
      setpoint -= 300;
    }               
  }
        
  

  Serial.print("setpoint: ");Serial.print(setpoint); Serial.print(" ");
  Serial.print("input: ");Serial.print(input); Serial.print(" ");
  Serial.print("output: ");Serial.print(output); Serial.print(" ");
  Serial.println("");
        
  delay(100);
        
}


/******************************************************************************************************************
 *  DON'T TOUCH ANYTHING BELOW THIS POINT. I RECOMMEND READING IT TO UNDERSTAND WHAT IS GOING ON, BUT FOR THIS
 *  TUTORIAL/CLASS YOU WON'T NEED TO MODIFY IT.
 ******************************************************************************************************************/

/* For the core timer callback, just toggle the output high and low
   and schedule us for another 100uS in the future. CORE_TICK_RATE
   is the number of core timer counts in 1 millisecond. So if we 
   want this callback to be called every 10uS, we just divide 
   the CORE_TICK_RATE by 100, and add it to the current time.
   currentTime is the core timer clock time at the moment we get
   called
*/
uint32_t MyCallback(uint32_t currentTime) {
  char newLeftA = digitalRead(2);
  char newLeftB = digitalRead(20);
  
  position += (newLeftA ^ lastLeftB) - (lastLeftA ^ newLeftB);
  
  if((lastLeftA ^ newLeftA) & (lastLeftB ^ newLeftB))
    {
        errorLeft = true;
    }
  
  lastLeftA = newLeftA;
  lastLeftB = newLeftB;
    
  
  if (counter % 100*pidSampleTime == 0)
  {
    input = position;      
        
    myPID.Compute();
    
    if (output > 0)
    {
      digitalWrite(4,1);
    }
    else
    {
      digitalWrite(4,0);
    }  
    SoftPWMServoPWMWrite(3,abs(output));
    counter = 0;
  }
  counter++;
  
  return (currentTime + CORE_TICK_RATE/100);
}





