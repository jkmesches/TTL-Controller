// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int LedPin = 12;      // the number of the LED pin
const int TTLPin = 10;

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
bool go = false;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LedPin, OUTPUT);
  pinMode(TTLPin, OUTPUT);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
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

  // set the LED:
  if(go) {
    digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(LedPin, LOW);
  delay(1000);

  for (int i = 0; i <= 10; i++) {
    digitalWrite(TTLPin, HIGH);
    digitalWrite(LedPin, HIGH);
    delay(5);
    digitalWrite(LedPin, LOW);
    digitalWrite(TTLPin, LOW);
    delay(995);
  }

  digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(LedPin, LOW);
  delay(1000);
  digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(LedPin, LOW);
  delay(1000);

  for (int i = 0; i <= 10; i++) {
    digitalWrite(TTLPin, HIGH);
    digitalWrite(LedPin, HIGH);
    delay(10);
    digitalWrite(LedPin, LOW);
    digitalWrite(TTLPin, LOW);
    delay(990);
  }

  digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(LedPin, LOW);
  delay(1000);
  digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(LedPin, LOW);
  delay(1000);
  digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(LedPin, LOW);
  delay(1000);

  for (int i = 0; i <= 10; i++) {
    digitalWrite(TTLPin, HIGH);
    digitalWrite(LedPin, HIGH);
    delay(20);
    digitalWrite(LedPin, LOW);
    digitalWrite(TTLPin, LOW);
    delay(980);
  }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
