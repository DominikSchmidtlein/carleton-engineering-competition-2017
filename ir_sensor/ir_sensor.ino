#include "IRremote.h"
int motorAold = 0;
int motorBold = 0;
int motorA = 0;
int motorB = 0;

int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

  //Setup Channel A - MOTOR 1
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B - MOTOR 2
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT); //Initiates Brake Channel B pin
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR();
    updateMotors();
    delay(50); // Do not get immediate repeat
    irrecv.resume(); // receive the next value
  } else {
    motorA = 0;
    motorB = 0;
    updateMotors();
  }
}/* --(end main loop )-- */

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {

  case 0xFF629D: Serial.println(" 2"); break;
  case 0xFF22DD: Serial.println(" 4");    break;
  case 0xFF02FD: Serial.println(" 5");    break;
  case 0xFFC23D: Serial.println(" 6");   break;
  case 0xFFA857: Serial.println(" 8"); break;
  case 0xFF6897: Serial.println(" *");    break;
  case 0xFF9867: Serial.println(" 0");    break;
  case 0xFFB04F: Serial.println(" #");    break;
  case 0xFF30CF: Serial.println(" 4");    break;
  case 0xFF18E7:
    Serial.println(" FORWARD");
    motorA = 1;
    motorB = -1;
    motorAold = 1;
    motorBold = -1;
    break;
  case 0xFF7A85: Serial.println(" 6");    break;
  case 0xFF10EF:
    Serial.println(" LEFT");
    motorA = -1;
    motorB = -1;
    motorAold = -1;
    motorBold = -1;
    break;
  case 0xFF38C7:
    Serial.println(" -OK-");
    break;
  case 0xFF5AA5:
    Serial.println(" RIGHT");
    motorA = 1;
    motorB = 1;
    motorAold = 1;
    motorBold = 1;
    break;
  case 0xFF42BD: Serial.println(" *");    break;
  case 0xFF4AB5:
    Serial.println(" REVERSE");
    motorA = -1;
    motorB = 1;
    motorAold = -1;
    motorBold = 1;
    break;
  case 0xFF52AD: Serial.println(" #");    break;
  case 0xFFFFFFFF: 
    Serial.println(" REPEAT");
    motorA = motorAold;
    motorB = motorBold;
    break;  

  default: 
    Serial.println(" other button   ");

  }// End Case
}

void updateMotors() {
  updateMotor(12, 9, 3, motorA);
  updateMotor(13, 8, 11, motorB);
}

void updateMotor(int dirPin, int brakePin, int speedPin, int value) {
  if (value < 0) {
    digitalWrite(dirPin, LOW);
    digitalWrite(brakePin, LOW);
    analogWrite(speedPin, 255);
  } else if (value > 0) {
    digitalWrite(dirPin, HIGH);
    digitalWrite(brakePin, LOW);
    analogWrite(speedPin, 255);
  } else {
    digitalWrite(dirPin, LOW);
    digitalWrite(brakePin, HIGH);
    analogWrite(speedPin, 255);
  }
}


















