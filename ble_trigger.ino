#include "src/esp32kbd/BleKeyboard.h"
BleKeyboard bleKeyboard("Photobooth trigger", "Metropo", 100);

const int buttonPin = 13;     // the number of the pushbutton pin
const int ledPin =  2;      // the number of the LED pin
const int buttonIgnoreTime = 1000; // Ignore presses within x milli seconds after first press

int buttonState = 0;         // variable for reading the pushbutton status
// unsigned long lastPress = 0;

//void IRAM_ATTR TriggerButtonIsr() {
//  Serial.print("ISR");
//  unsigned long now = millis();
//  if (now > buttonIgnoreTime + lastPress)
//  {
//    Serial.print("Trigger");
//    bleKeyboard.print("a");
//    lastPress = now;
//  }
//}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
//  attachInterrupt(buttonPin, TriggerButtonIsr, CHANGE);
  //esp_light_sleep_start();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    // read the state of the pushbutton value:
    int newButtonState = digitalRead(buttonPin);
    if(buttonState != newButtonState)
    {
        buttonState = newButtonState;
        if (buttonState == HIGH) {
          Serial.println("Sending Trigger ...");
          bleKeyboard.print("a");
          digitalWrite(ledPin, HIGH);
        }
        else if (buttonState == LOW) {
          digitalWrite(ledPin, LOW);
        }
        delay(200);
    }
  }
}
