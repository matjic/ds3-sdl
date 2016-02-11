//
//  ps3controller.h
//  ps3host
//
//  Created by Mathew Jacob on 11/5/15.
//  Copyright © 2015 Mathew Jacob. All rights reserved.
//

#ifndef ps3controller_h
#define ps3controller_h

#include <iostream>
#include <SDL2/SDL.h>

class PS3_Controller
{
public:
    PS3_Controller(int sdl_index);
    PS3_Controller(PS3_Controller& other);
    PS3_Controller& operator=(const PS3_Controller& other);
    ~PS3_Controller();
    
    bool isValid();
    
    std::string getName() const;
    SDL_Joystick* getController() const;
    void update(SDL_Event event);
    int getNumAxes() const;
    int getNumButtons() const;
    int getButtonState(int button) const;

    enum btn_constants
    {
        SELECT = 0,
        L3,
        R3,
        START,
        UP,
        RIGHT,
        DOWN,
        LEFT,
        L2,
        R2,
        L1,
        R1,
        TRIANGLE,
        CIRCLE,
        X,
        SQUARE,
        PS
    };
        
    
    const int BUTTON_DOWN = -1;
    const int BUTTON_UP = 1;
    const int BUTTON_NEUTRAL = 0;
    
private:
    void init(SDL_Joystick* controller);
    void erase();
    PS3_Controller& copy(const PS3_Controller& other);
    
    bool valid;
    SDL_Joystick* controller;
    int numAxes;
    int numButtons;
    int* axisValues;
    int* buttonStates;
    std::string name;
    
    
};


#endif
