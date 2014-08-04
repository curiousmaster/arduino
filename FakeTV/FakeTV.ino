/*

 An Arduino "Fake TV"
 This is an Arduino simulation of the product called "Fake TV" 
 It simulates the action of a TV being viewd by a person at night.
 The purpose is to fool burglars into thinking someone is at home watching a TV at night.
 Place it near a window behind blinds or curtains so as to not directly show the LEDs.
 You only want the aggragate effect of all the LEDs to be seen.
 
 I used 2 green, 2 red, one bright white and one bright blue.
 I neede more red/green because the apparent brightness of the white and blue is greater than the red/greens
 Use a diffuser over the board such as vellum papar to help scene quality.
 Of course all these parameters can be changed to suit your needs.
 Check at night near a window and adjust to suit your preferences.
 Free to modify, the possible scene algorithms are endless.
 
 */

int blu = 11;
int red2 = 9;
int grn1 = 10;
int grn2 = 3;
int red1 = 6;
int wht = 5;
int randpwm = 0;

void setup() 
{   
  pinMode(red1, OUTPUT);     
  pinMode(red2, OUTPUT);       
  pinMode(grn1, OUTPUT);     
  pinMode(grn2, OUTPUT);     
  pinMode(blu, OUTPUT); 
  pinMode(wht, OUTPUT); 
}

void loop() 
{
  for(int i=0;i<10;i++)  //play scene 1 multiple times
  {
    scene1();
  }
  if (random(2) == 1)  //Possibly call scene 2
  {
    scene2();
  }
  if (random(2) == 1)  //Possibly call scene 3
  {
    scene3();
  }
  if (random(2) == 1)  //Possibly call scene 4
  {
    scene4();
  }
  if (random(4) == 1)  //Possibly do a commercial break
  {
    commercial();
  }
}

/*
These are the main scene algorithms
 */

void scene1()
// Changes random light levels and linger-times 
// of all colors to simulate "normal" TV action
{
  randpwm = random(20,255);
  analogWrite(red1,randpwm); 
  analogWrite(red2,randpwm); 
  randpwm = random(20,255);
  analogWrite(grn1,randpwm); 
  analogWrite(grn2,randpwm); 
  analogWrite(blu,random(10,225)); 
  analogWrite(wht,random(10,175));
  delay(random(500,2000));
}

void scene2()
// Increases intensity of wht,blu (fade-in)
{
  delay(1000);
  for(int i=2;i<255;i++)
  {
    analogWrite(blu,i); 
    analogWrite(wht,i);
    delay(20);
  }
}

void scene3()
// Flickers wht,blu for a flickeriing scene effect
{
  boolean sw = HIGH;
  for(int i=0;i<30;i++)
  {
    digitalWrite(wht,sw);
    digitalWrite(blu,sw);
    sw = !sw;
    delay(random(50,300));
  }
}

void scene4()
// Changes red/grn light levels only
// wht/blu are off
{
  //don't use wht/blu
  digitalWrite(wht,LOW);
  digitalWrite(blu,LOW);
  for(int i=0;i<12;i++)
  {
    randpwm = random(20,255);
    analogWrite(red1,randpwm); 
    analogWrite(red2,randpwm); 
    randpwm = random(20,255);
    analogWrite(grn1,randpwm); 
    analogWrite(grn2,randpwm); 
    delay(random(200,2000));
  }
}

void commercial()
// Simulates a switch to or from a commercial break 
{
  analogWrite(red1,2); 
  analogWrite(red2,2); 
  analogWrite(grn1,2);
  analogWrite(grn2,2);
  analogWrite(blu,0);
  analogWrite(wht,0);
  delay(random(1000,2500));
}
