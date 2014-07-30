//===================================================
// Turn LED on/off via commands from USB
//---------------------------------------------------
//  space = TOGGLE
//      z = ON
//      x = OFF
//      b = BLINK
//      r = REBOOT
//===================================================
 
#define DEBUG
#define LED_ON_BOARD 0
#define ON  1
#define OFF 0
 
//----------------------------------------------------
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
//----------------------------------------------------
int led = 13;

//----------------------------------------------------
// Define some variables
//----------------------------------------------------
int USB = 0;
int state = 0;
int blink = 0;
int intervall = 500;
int lastmillis = 0;

void LEDblink() {
    int now = millis();
    if( now - lastmillis >= intervall ) {
      state = !state;
      lastmillis = now;
      Serial.println("<BLINK>");
      digitalWrite(led, state);
#if LED_ON_BOARD
      Serial.print("State: ");
      Serial.println(state?"ON":"OFF");
#endif
    }
}


void software_Reboot()
{
  USB = 0;
  state = 0;
  blink = 0;
  Serial.print("Rebooting in 2 seconds...");
  
  delay(1500);
  
  Serial.println(" now");
  
  delay(500);

}

void PrintHELP()
{
  Serial.println("--------------------------------------");
  Serial.println("Turn LED on/off via commands from USB");
  Serial.println("    space = TOGGLE");
  Serial.println("        z = ON");
  Serial.println("        x = OFF");
  Serial.println("        b = BLINK");
  Serial.println("      any = HELP (this)");
  Serial.println("--------------------------------------");
}

//----------------------------------------------------
// the setup routine runs once when you press reset:
//----------------------------------------------------
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);

  
}

//-----------------------------------------------------
// the loop routine runs over and over again forever:
//-----------------------------------------------------
void loop() {
    
  if( Serial.available() ) {
    USB = Serial.read();

    switch( USB ) {
      case 32:
		//------------------------------
		// TOGGLE (space)
		//------------------------------
                blink = OFF;
                state = !state;
                digitalWrite(led, state==0?LOW:HIGH);
#if defined DEBUG
                Serial.print("State: ");
                Serial.println(state?"ON":"OFF");
#endif
                break;
                
      case 122:
		//------------------------------
		// ON (z)
		//------------------------------
                blink = OFF;
                if( state != 1 ) {
                  digitalWrite(led, HIGH);
#if defined DEBUG
                  Serial.println("State: ON");
#endif
                }
                state = 1;

                break;
      case 120:
		//------------------------------
		// OFF (x)
		//------------------------------
                blink = OFF;
                if( state != 0 ) {
                  digitalWrite(led, LOW);
#if defined DEBUG
                  Serial.println("State: OFF");
#endif
                }
                state = 0;
                break;
       case 98:
		//------------------------------
		// BLINK (b)
		//------------------------------
#if defined DEBUG
		Serial.println("Turning blink ON");
#endif
                blink = ON;
                break;
        case 114:
                software_Reboot();
                break;
        default:
                PrintHELP();
                break;
     }
  }
  //------------------------------
  // Blink
  //------------------------------
  if( blink == ON ) {
	LEDblink();
  }
}
