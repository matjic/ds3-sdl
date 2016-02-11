//
//  main.cpp
//  ps3host
//
//  Created by Mathew Jacob on 11/5/15.
//  Copyright © 2015 Mathew Jacob. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "ps3controller.h"
#include "callbacks.h"
 

void loop(PS3_Controller& controller, std::unordered_map<uint, void(*)()>& buttonMap);

void addMapping(uint controllerKey, void (*func)(), std::unordered_map<uint, void(*)()>& buttonMap);
void initMappings(std::unordered_map<uint, void(*)()>& buttonMap);

int kodi(std::string key, std::unordered_map<uint, void(*)()>& buttonMap);


int main(int argc, const char * argv[]) {
    std::unordered_map<uint, void(*)()> buttonMap;
    initMappings(buttonMap);
    
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
    
    uint numJoysticks = SDL_NumJoysticks();

    if( numJoysticks < 1 )
    {
        std::cout << "No controllers available." << std::endl;
        return -1;
    }

    std::cout << numJoysticks << " controllers available." << std::endl;
    SDL_JoystickEventState(SDL_ENABLE);
    
    PS3_Controller controller(0);
    
    if( !controller.isValid() )
    {
        std::cout << "Controller not initialized properly." << std::endl;
        return -1;
    }

    std::cout << controller.getName() << " initialized." << std::endl;

    loop(controller, buttonMap);
    
    SDL_Quit();
    return 0;
}

void loop(PS3_Controller& controller, std::unordered_map<uint, void(*)()>& buttonMap)
{

    SDL_Event event;
    
    bool quit = false;
    while ( !quit )
    {
        SDL_WaitEvent(&event);
        controller.update(event);
        
        for(auto& keyPair : buttonMap)
        {
            if( controller.getButtonState(keyPair.first) ==  controller.BUTTON_DOWN )
            {
                (buttonMap[keyPair.first])();
            }
        }

        if(event.type == SDL_QUIT)
        {
            quit = true;
        }
    }
    

}

void initMappings(std::unordered_map<uint, void(*)()>& buttonMap)
{
    //std::unordered_map ps3 inputs to Kodi's JSON requests
    addMapping( PS3_Controller::DOWN, &InputDown, buttonMap );
    addMapping( PS3_Controller::LEFT, &InputLeft, buttonMap );
    addMapping( PS3_Controller::UP, &InputUp, buttonMap );
    addMapping( PS3_Controller::RIGHT, &InputRight, buttonMap );
    addMapping( PS3_Controller::CIRCLE, &InputBack, buttonMap );
    addMapping( PS3_Controller::X, &InputSelect, buttonMap );
    addMapping( PS3_Controller::TRIANGLE, &InputHome, buttonMap );
    addMapping( PS3_Controller::START, &PlayPause, buttonMap );
    addMapping( PS3_Controller::SQUARE, &Stop, buttonMap );
    addMapping( PS3_Controller::L2, &SlowDown, buttonMap );
    addMapping( PS3_Controller::R2, &SpeedUp, buttonMap );
    addMapping( PS3_Controller::L1, &VolumeDown, buttonMap );
    addMapping( PS3_Controller::R1, &VolumeUp, buttonMap );
    addMapping( PS3_Controller::PS, &Home, buttonMap );
}

void addMapping(uint controllerKey, void (*func)(), std::unordered_map<uint, void(*)()>& buttonMap)
{
    buttonMap.insert( std::pair<uint,void(*)()>(controllerKey, func) );
}