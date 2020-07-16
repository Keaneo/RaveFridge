int RED_LED = 7;
int BLUE_LED = 5;
int GREEN_LED = 9;

int brightness = 255;
int gBright = 0;
int rBright = 0;
int bBright = 0;

int fadeSpeed = 5;

int buttonPin = 11;// the number of the pushbutton pin
int greenLedPin = 12;
int redLedPin = 13; // the number of the LED pin

int speakerOut = 3;

// variables will change:
int buttonState = 0; // variable for reading the pushbutton status

bool lightsOn = false;

//Tones
#define c 3830    // 261 Hz
#define d 3400    // 294 Hz
#define e 3038    // 329 Hz
#define f 2864    // 349 Hz
#define g 2550    // 392 Hz
#define a 2272    // 440 Hz
#define b 2028    // 493 Hz 
#define C 1912    // 523 Hz
// Define a special note, 'R', to represent a rest
#define  R     0

int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 50;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

int iLoopCount = 0;

void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                
}


//void TurnOn() {
//   lightsOn = true;
//  if(brightness < 256){
//   //for (int i = 0; i < 256; i++) {
//       analogWrite(RED_LED, rBright);
//       rBright +=1;
//       delay(fadeSpeed);
//   //}
// 
//   //for (int i = 0; i < 256; i++) {
//       analogWrite(BLUE_LED, bBright);
//       bBright += 1;
//       delay(fadeSpeed);
//   //} 
//
//   //for (int i = 0; i < 256; i++) {
//       analogWrite(GREEN_LED, gBright);
//       gBright +=1;
//       delay(fadeSpeed);
//       brightness += 1;
//  }
//  
//   //} 
//}

//void TurnOff() {
//  lightsOn = false;
//   //for (int i = 0; i < 256; i++) {
//   if(brightness > 0){
//       analogWrite(GREEN_LED, brightness);
//       analogWrite(RED_LED, brightness);
//       analogWrite(BLUE_LED, brightness);
// 
//       brightness -= 1;
//       delay(fadeSpeed);
//   }
//   //}
//}

void TurnOff(){
  analogWrite(GREEN_LED, 0);
  analogWrite(RED_LED, 0);
  analogWrite(BLUE_LED, 0);
}

void SongMethod(int i){
  tone_ = melody[i];
  beat = beats[i];

  duration = beat * tempo; // Set up timing

  playTone();
  // A pause between notes...
  iLoopCount++;
  delayMicroseconds(pause);

}


void RandomFlash(){
  int gLed = random();
  int rLed = random();
  int bLed = random();

  analogWrite(GREEN_LED, gLed);
  analogWrite(RED_LED, rLed);
  analogWrite(BLUE_LED, bLed);

  //tone(speakerOut, 1000);  
  
  SongMethod(iLoopCount);

  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  pinMode(speakerOut, OUTPUT);
  pinMode(6, OUTPUT);


  Serial.begin(9600);
  //while(true){
   //TurnOn();  
   //delay(5000);
   //TurnOff();
  //} 
}

void loop() {
  Serial.println(brightness);
  if(MAX_COUNT == iLoopCount){
    iLoopCount = 0;
  }
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  if (buttonState == LOW) {
    // turn LED on:
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    //if(!lightsOn){
      
      TurnOff();
    //}    
  } else {
    // turn LED off:
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    //if(lightsOn){
      RandomFlash();
    //}    
  }
}
