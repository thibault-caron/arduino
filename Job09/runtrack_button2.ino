
const int buttonPin = 2;  // The pin where the button is connected
const int ledPin = 13;    // The pin where the LED is connected

int buttonState = 0;           // Current state of the button
int lastButtonState = 0;       // Previous state of the button
unsigned long lastPressTime = 0;  // Time of the last button press
unsigned long debounceDelay = 10; // Debounce delay in milliseconds
int pressCount = 0;           // Counter for the number of button presses
unsigned long doublePressWindow = 500; // Time window (in ms) for double press detection
unsigned long longPressThreshold = 1500; // Long press threshold (1.5 seconds)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Set the button pin as input with an internal pull-up resistor
  pinMode(ledPin, OUTPUT);           // Set the LED pin as output
  digitalWrite(ledPin, LOW);         // Ensure the LED is initially off
}

void loop() {
  int reading = digitalRead(buttonPin);  // Read the current state of the button

  // Check if the button state has changed (press or release)
  if (reading != lastButtonState) {
    lastPressTime = millis();  // Update the time of the state change
  }

  // If the button has been pressed (with debounce delay)
  if ((millis() - lastPressTime) > debounceDelay) {
    if (reading == LOW) {  // Button is pressed
      pressCount++;  // Increment the press count
      digitalWrite(ledPin, HIGH);  // Turn the LED on while the button is pressed
    }
  }

  // If the button is held down for a long time (1.5 seconds or more)
  if (reading == LOW && (millis() - lastPressTime >= longPressThreshold)) {
    digitalWrite(ledPin, LOW);  // Turn off the LED after 1.5 seconds
    pressCount = 0;  // Reset press count on long press
  }

  // If button is released (after a press)
  if (reading == HIGH && lastButtonState == LOW) {
    // Single press: Turn the LED off when released
    if (pressCount == 1) {
      digitalWrite(ledPin, LOW);  // Turn the LED off
    }
    // Double press: Keep the LED on
    else if (pressCount == 2) {
      digitalWrite(ledPin, HIGH);  // Keep the LED on
    }

    // Reset press count after a small time window (for double press detection)
    if (millis() - lastPressTime <= doublePressWindow) {
      pressCount = 0;  // Reset the press count after double press time window
    }

    // Reset press count if no double press was detected (time window passed)
    if (millis() - lastPressTime > doublePressWindow) {
      pressCount = 0;  // Reset press count after double press window timeout
    }
  }

  // Save the current button state for next iteration
  lastButtonState = reading;
}
