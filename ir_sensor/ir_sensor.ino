#include "IRremote.h"

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
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT); //Initiates Brake Channel A pin
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
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
    forwardA();
    forwardB();
    break;
  case 0xFF7A85: Serial.println(" 6");    break;
  case 0xFF10EF: Serial.println(" LEFT");    break;
  case 0xFF38C7: Serial.println(" -OK-");    break;
  case 0xFF5AA5: Serial.println(" RIGHT");    break;
  case 0xFF42BD: Serial.println(" *");    break;
  case 0xFF4AB5:
    Serial.println(" REVERSE");
    reverseA();
    reverseB();
    break;
  case 0xFF52AD: Serial.println(" #");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} 

void forwardA() {
  //forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
}

void stopA() {
  digitalWrite(12, HIGH);//Establishes forward direction of Channel A
  digitalWrite(9, HIGH); //Engage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
}

void reverseA() {
  digitalWrite(12, LOW); //Establishes reverse direction of Channel A
  digitalWrite(9, LOW);  //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
}

void forwardB() {
  //forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
}

void stopB() {
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
}

void reverseB() {
  digitalWrite(13, LOW); //Establishes reverse direction of Channel A
  digitalWrite(8, LOW);  //Disengage the Brake for Channel A
  analogWrite(11, 255);   //Spins the motor on Channel A at full speed
}






















