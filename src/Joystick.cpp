#include "Joystick.hpp"
#include <Arduino.h>

Joystick::Joystick(int cpin_X, int cpin_Y, int cbutton): 
    pin_X(cpin_X), pin_Y(cpin_Y), button(cbutton){
        pinMode(pin_X,INPUT);
        pinMode(pin_Y,INPUT);
        pinMode(button,INPUT_PULLUP);
        pinNumber = 3;
}

Joystick::Joystick(int cpin_X, int cbutton): 
    pin_X(cpin_X), button(cbutton){
        pinMode(pin_X,INPUT);
        pinMode(button,INPUT_PULLUP);
        pinNumber = 2;
}

int Joystick::get_X(){
    this->X = (abs(((analogRead(pin_X))/20.475)-100)<DEAD_ZONE)? 0 : (((analogRead(pin_X))/20.475)-100);
    return this->X;
}

int Joystick::get_Y(){
    switch(pinNumber){
        case 3:
            this->Y = (abs(((analogRead(pin_Y))/20.475)-100)<DEAD_ZONE)? 0 : (((analogRead(pin_Y))/20.475)-100);
            return this->Y;
            break;            
        case 2:
            return 0;
            break;
    }
}

bool Joystick::get_button(){
    return !digitalRead(button);
}

bool Joystick::Y_asButtonUp(){
    if(get_Y() > 0){
        return true;
    }
    else if(get_Y() <= 0){
        return false;
    }
}

bool Joystick::Y_asButtonDown(){
    if(get_Y() < 0){
        return true;
    }
    else if(get_Y() >= 0){
        return false;
    }
}

bool Joystick::X_asButtonRight(){
    if(get_X() > 0){
        return true;
    }
    else if(get_X() <= 0){
        return false;
    }
}

bool Joystick::X_asButtonLeft(){
    if(get_X() < 0){
        return true;
    }
    else if(get_X() >= 0){
        return false;
    }
}



bool Joystick::Y_asButtonUpDebounced(){    
    int buttonState;
    int lastButtonState = false;
    bool output = false;

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 10 + (DEBOUNCE_DELAY-(DEBOUNCE_DELAY*(get_Y()/100)));

    int reading = Y_asButtonUp();

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState == true) {
                output != output;
            }
        }
    }

  lastButtonState = reading;
  return output;
}

bool Joystick::Y_asButtonDownDebounced(){
    int buttonState;
    int lastButtonState = false;
    bool output = false;

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 10 + (DEBOUNCE_DELAY-(DEBOUNCE_DELAY*(get_Y()/100)));

    int reading = Y_asButtonDown();

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState == true) {
                output != output;
            }
        }
    }

  lastButtonState = reading;
  return output;

}

bool Joystick::X_asButtonRightDebounced(){
    int buttonState;
    int lastButtonState = false;
    bool output = false;

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 10 + (DEBOUNCE_DELAY-(DEBOUNCE_DELAY*(get_X()/100)));

    int reading = X_asButtonRight();

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState == true) {
                output != output;
            }
        }
    }

  lastButtonState = reading;
  return output;

}

bool Joystick::X_asButtonLeftDebounced(){
    int buttonState;
    int lastButtonState = false;
    bool output = false;

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 10 + (DEBOUNCE_DELAY-(DEBOUNCE_DELAY*(get_X()/100)));

    int reading = X_asButtonLeft();

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState == true) {
                output != output;
            }
        }
    }

  lastButtonState = reading;
  return output;
    
}