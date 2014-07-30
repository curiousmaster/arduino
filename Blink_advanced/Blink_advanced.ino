/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly without blocking the loop()
  */
 
 #define DEBUG
 
//----------------------------------------------------
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
//----------------------------------------------------
int led = 13;
int button01 = 2;
int button02 = 3;
int USB = 0;

//----------------------------------------------------
// Define some variables
//----------------------------------------------------
int lastmillis = 0;
int intervall = 5000;
int state = 0;

//----------------------------------------------------
// the setup routine runs once when you press reset:
//----------------------------------------------------
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  pinMode(button01, INPUT);
  pinMode(button02, INPUT);

#if defined DEBUG
  Serial.begin(9600);
  Serial.println("START");
#endif
  
}

//-----------------------------------------------------
// the loop routine runs over and over again forever:
//-----------------------------------------------------
void loop() {
  
  int now = millis(); // milliseconds since last reset, will wrapp after 70 days
  
  USB = Serial.read();
  
  if ( now - lastmillis >= intervall || USB == 1 ) {
    lastmillis = now;
    
    state = !state;

#if defined DEBUG
    Serial.println(state==0?"OFF":"ON");
    Serial.println(USB, DEC);
#endif
    digitalWrite(led, state);

  }
}
