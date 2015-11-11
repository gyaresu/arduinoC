// adding some printf functionality
#include <Servo.h>
#include <stdarg.h>

Servo firstServo;
int pos = 0;

void beep(unsigned char delayms){
  analogWrite(20, 1);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(20, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  

void p(char *fmt, ... ) {
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  Serial.print(buf);
}

void p(const __FlashStringHelper *fmt, ... ) {
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt);
#ifdef __AVR__
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
#else
  vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
#endif
  va_end(args);
  Serial.print(buf);
}

const int ledPin =  8;      // the number of the LED pin
int speakerOut = 20;        // piezo speaker
int DEBUG = 1;              // Debugging on/off

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 530;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pins as output:
  firstServo.attach(13);
  pinMode(speakerOut, OUTPUT);
  pinMode(ledPin, OUTPUT);
  beep(50);
  beep(50);
  beep(50);
  if (DEBUG) {
    Serial.begin(9600);
  }
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    p("The current milliseconds since start is: %ul\nAnd the current Servo position is: %i\n", currentMillis, pos);
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // Move the servo
    if (pos < 180) {
      beep(200);
      firstServo.write(pos);
      pos = pos + 6;
    } else if (pos == 180)  {
      beep(50);
      beep(50);
      beep(50);
      firstServo.write(pos);
      pos = 0;
    }

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    digitalWrite(speakerOut, ledState);
  }
}
