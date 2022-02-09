/***************************************************************************************
 * 
 *     ____  _       __          ____   ______            __             ____         
 *    / __ \(_)___  / /_  ____ _/ / /  / ____/___  ____  / /__________  / / /__  _____
 *   / /_/ / / __ \/ __ \/ __ `/ / /  / /   / __ \/ __ \/ __/ ___/ __ \/ / / _ \/ ___/
 *  / ____/ / / / / /_/ / /_/ / / /  / /___/ /_/ / / / / /_/ /  / /_/ / / /  __/ /    
 * /_/   /_/_/ /_/_.___/\__,_/_/_/   \____/\____/_/ /_/\__/_/   \____/_/_/\___/_/     
 * 
 * Pinball Controller for Arduino Leonardo                                                                                                                                              
 * Author: Ed de Tollenaer
 * 
 * Pin                      Key             Var buttonPin
 * ------------------------------------------------------
 * Pin 2: Right Flipper     (Right Shift)   (0)
 * Pin 3: Left Flipper      (Left Shift)    (1)
 * Pin 4: Insert Coin       (5)             (2)
 * Pin 5: Start Game        (1)             (3)
 * Pin 6: Press Plunger     (Enter)         (4)
 * Pin 7: Quit Game         (Esc)           (5)
 * Pin 8: Right Magna Save  (Right Control) (6)
 * Pin 9: Left Magna Save   (Left Control)  (7)
 * Pin 10: Front Nudge      (Space)         (8)
 * Pin 11: Right Nudge      (/)             (9)
 * Pin 12: Left Nudge       (Z)             (10)
 * 
 * The latest version can be found at https://github.com/smarthomejunkie/PinballController
 **************************************************************************************/
 
#include "Keyboard.h"

const int buttonPin[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int pinCount = 11;
int buttonState[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int prevButtonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
long lastDebounceTime[] = {0,0,0,0,0,0,0,0,0,0,0};

long debounceDelay = 10;

void setup() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(buttonPin[thisPin], INPUT_PULLUP);
    digitalWrite(buttonPin[thisPin], HIGH);
  }
  Keyboard.begin();
}

int outputAction(int currentButton) {
  switch (currentButton) {
    case 0: // Right Flipper
      if (buttonState[currentButton] == LOW) {
        Keyboard.press(KEY_RIGHT_SHIFT); 
        delay(10);
      } else {
        Keyboard.release(KEY_RIGHT_SHIFT);
      }
      break;
    case 1: // Left Flipper
      if (buttonState[currentButton] == LOW) {
        Keyboard.press(KEY_LEFT_SHIFT); 
        delay(10);
      } else {
        Keyboard.release(KEY_LEFT_SHIFT);
      }
      break;
    case 2: // Insert Coin
      if (buttonState[currentButton] == LOW) {
        Keyboard.press('5'); 
        delay(10);
      } else {
        Keyboard.release('5');
      }
      break; 
    case 3: // Start Game
      if (buttonState[currentButton] == LOW) {
        Keyboard.press('1'); 
        delay(10);
      } else {
        Keyboard.release('1');
      }
      break; 
    case 4: // Press Plunger
      if (buttonState[currentButton] == LOW) {
        Keyboard.press(KEY_RETURN); 
        delay(10);
      } else {
        Keyboard.release(KEY_RETURN);
      }
      break;    
    case 5: // Quit Game
      if (buttonState[currentButton] == LOW) {
        Keyboard.press(KEY_ESC); 
        delay(10);
      } else {
        Keyboard.release(KEY_ESC);
      }
      break;  
    case 6: // Right Magna Save
      if (buttonState[currentButton] == LOW) {
        Keyboard.press(KEY_RIGHT_CTRL); 
        delay(10);
      } else {
        Keyboard.release(KEY_RIGHT_CTRL);
      }
      break; 
    case 7: // Left Magna Save
      if (buttonState[currentButton] == LOW) {
        Keyboard.press(KEY_LEFT_CTRL); 
        delay(10);
      } else {
        Keyboard.release(KEY_LEFT_CTRL);
      }
      break;    
    case 8: // Front Nudge
      if (buttonState[currentButton] == LOW) {
        Keyboard.press(' '); 
        delay(10);
      } else {
        Keyboard.release(' ');
      }
      break;  
    case 9: // Right Nudge
      if (buttonState[currentButton] == LOW) {
        Keyboard.press('/'); 
        delay(10);
      } else {
        Keyboard.release('/');
      }
      break; 
    case 10: // Left Nudge
      if (buttonState[currentButton] == LOW) {
        Keyboard.press('z'); 
        delay(10);
      } else {
        Keyboard.release('z');
      }
      break;       
    default:
      break;
  }
  prevButtonState[currentButton] = buttonState[currentButton];
}

void loop() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    buttonState[thisPin] = digitalRead(buttonPin[thisPin]);
    if (buttonState[thisPin] != prevButtonState[thisPin]) {
      if ((millis() - lastDebounceTime[thisPin]) > debounceDelay) {
        lastDebounceTime[thisPin] = millis();
        outputAction(thisPin);
      }
    }
  }
}
