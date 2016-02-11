# ds3-sdl
Interfaces with the Dualshock 3 (possibly Dualshock 4 as well) using the SDL library.

## What is it?
It turns the PS3 Controller into a bluetooth remote for Kodi. 

## How does it work?
Mac easily connects to the PS3 controller via Bluetooth. I then used the SDL library to connect the controller. I have created a PS3Controller class (ps3controller.cpp/h) to simplify the interface. In main.cpp, I hook functions to each button I want to use. The functions (in callbacks.cpp/h) use libcurl to send JSONs to the Kodi server corresponding to each action.

This is made for Mac and may not compile on Linux