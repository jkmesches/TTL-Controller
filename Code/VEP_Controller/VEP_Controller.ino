// constants won't change. They're used here to set pin numbers:
const int buttonPin = 10;    // the number of the pushbutton pin
const int FETPin = 5;      // the number of the MOSFET Gate pin
const int OutputLEDPin = 11;       // the number of the output indicator LED pin
const int OnboardLEDPin = 13;
const int TTLPin = 9;          // TTL pin
const int iNumTrials = 100;  // number of trials to run for each condition
const int iDelayBetweenConditions = 5000 ; //delay between each condition in ms

// Define trial condition arrays

int iPulseWidth[] = {10, 5, 20};                 // array of the pulse widths
int iRate[] = {1000, 500, 333, 2000, 1000};  // array of the trial frequency (rate) for each condition
 

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
bool ready_to_go = false;
bool go = false;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int i,j,k;                   // counter vars        

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(FETPin, OUTPUT);
  pinMode(TTLPin, OUTPUT);
  pinMode(OutputLEDPin, OUTPUT);
  pinMode(OnboardLEDPin, OUTPUT);
}

void loop() {

  ready_to_go = true;
  
  if(ready_to_go) {
    digitalWrite(OnboardLEDPin, HIGH);
  }
  else {
    digitalWrite(OnboardLEDPin, LOW);
  }
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from HIGH to LOW), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        go = true;
      }
    }
  }

  // Set the outputs (LED strip and TTL out):
  if(go) {
    ready_to_go = false;
    digitalWrite(OnboardLEDPin, LOW);
    for (i = 0; i < 5; i++) {                  // loop through the Rates array (e.g., 1000, 500, 333, 2000, 1000 ms)
       for (j = 0; j < 3; j++) {               // loop through the Pulse Widths array (e.g., 10, 5, 20 ms)
          for (k = 0; k < iNumTrials; k++) {   // perform iNumTrials of each condition
             digitalWrite(TTLPin, HIGH);       // start TTL pulse
             digitalWrite(OutputLEDPin, HIGH);
             digitalWrite(FETPin, HIGH);       // start stimulus
             delay(iPulseWidth[j]);            // Set stimulus duration
             digitalWrite(FETPin, LOW);        // end light stimulus
             digitalWrite(TTLPin, LOW);
             digitalWrite(OutputLEDPin, LOW);
            // delay(50-iPulseWidth[j]);         // end TTL pulse (50 ms total duration)
             delay(iRate[i] - 50);            // Calculate interstimulus interval
     
          }                                  // end k loop
            delay(iDelayBetweenConditions);  // delay between sets of trials
        }                                    // end j loop
     }                                       // end i loop 
  }                                          // end go loop
  
  go = false;                                 // wait for next button press before re-entering go loop
  ready_to_go = true;
  
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}  // end loop
