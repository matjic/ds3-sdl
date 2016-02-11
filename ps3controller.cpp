//
//  ps3controller.cpp
//  ps3host
//
//  Created by Mathew Jacob on 11/5/15.
//  Copyright © 2015 Mathew Jacob. All rights reserved.
//

#include "ps3controller.h"

PS3_Controller::PS3_Controller(int sdl_index)
{
    valid = false;
    axisValues = nullptr;
    buttonStates = nullptr;
    controller = nullptr;
    
    if( sdl_index >= SDL_NumJoysticks() )
    {
        return;
    }
    
    controller = SDL_JoystickOpen(sdl_index);
    init(controller);
    
}

PS3_Controller::PS3_Controller(PS3_Controller& other)
{
    copy(other);
}

PS3_Controller& PS3_Controller::operator= (const PS3_Controller& other)
{
    return copy(other);
}

PS3_Controller::~PS3_Controller()
{
    erase();
}

void PS3_Controller::update(SDL_Event event)
{
    int axis = -1;
    int button = -1;
    for(int i = 0; i < numButtons; i++)
    {
        buttonStates[i] = BUTTON_NEUTRAL;
    }
    
    switch (event.type)
    {
        case SDL_JOYAXISMOTION:
            axis = (int)event.jaxis.axis;
            axisValues[axis] = event.jaxis.value;
            break;
            
        case SDL_JOYBUTTONDOWN:
            button = (int)event.jbutton.button;
            buttonStates[button] = BUTTON_DOWN;
            break;
            
            
        case SDL_JOYBUTTONUP:
            button = (int)event.jbutton.button;
            buttonStates[button] = BUTTON_UP;
            break;
    }
}

int PS3_Controller::getButtonState(int button) const
{
    if (button > numButtons)
    {
        return INT32_MIN;
    }
    
    return buttonStates[button];
}

void PS3_Controller::init(SDL_Joystick* controller)
{
    valid = false;
    axisValues = nullptr;
    buttonStates = nullptr;

    name = SDL_JoystickName(controller);
    
    numAxes = SDL_JoystickNumAxes(controller);
    axisValues = new int[numAxes];
    
    numButtons = SDL_JoystickNumButtons(controller);
    buttonStates = new int[numButtons];
    
    for(int i = 0; i < numAxes; i++)
    {
        axisValues[i] = 0;
    }
    
    for(int i = 0; i < numButtons; i++)
    {
        buttonStates[i] = 0;
    }
    
    valid = true;
}

void PS3_Controller::erase()
{
    if( !isValid() )
    {
        return;
    }
    if ( SDL_JoystickGetAttached(controller) )
    {
        SDL_JoystickClose(controller);
    }
    controller = nullptr;
    
    delete[] axisValues;
    delete[] buttonStates;
    axisValues = nullptr;
    buttonStates = nullptr;
    
    numAxes = -1;
    numButtons = -1;
    
    name = "";
    
    valid = false;
}

PS3_Controller& PS3_Controller::copy(const PS3_Controller& other)
{
    erase();
    
    controller = other.getController();
    
    init(controller);
    
    return *this;
}

bool PS3_Controller::isValid()
{
    return valid;
}

int PS3_Controller::getNumAxes() const
{
    return numAxes;
}

int PS3_Controller::getNumButtons() const
{
    return numButtons;
}

SDL_Joystick* PS3_Controller::getController() const
{
    return controller;
}

std::string PS3_Controller::getName() const
{
    return name;
}
