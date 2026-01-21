#include <iostream>
#include <Xinput.h>
#include <windows.h>
#include <map>
#include "interactions.h"
#include "config.h"
#include "handlemorse.h"
#include <chrono>
#include <thread>

#pragma comment(lib, "Xinput.lib")
/*
    Enty point
*/
int main(int argc, char* argv[]) {
    loadConfig("config.ini");
    bool debugMode = false;
    bool morseMode = false;
    
    static DWORD lastYTime = 0;
    bool lastY = false;
    bool YPressed = false;

    //enable debug mode
    if(argc == 2 && std::string(argv[1]) == "-debug") {
        debugMode = true;
        std::cout << "Debug mode enabled.\n";
    }


    //XBOX controller state
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));


    while(true) {
        DWORD result = XInputGetState(0, &state);
        if(result != ERROR_SUCCESS) {
            std::cout << "Controller not connected\n";
            Sleep(1000);
            continue;
        }

        YPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
        DWORD now = GetTickCount();

        // Debounce to avoid spam
        if(YPressed and !lastY and now - lastYTime > 300){
            morseMode = !morseMode; 
            lastYTime = now;
        }
        lastY = YPressed;

        if(morseMode){
            updateMorse(state);
        }else if (!morseMode) {
            updateMouse(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, debugMode);
            updateScroll(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
            interactButtons(state.Gamepad.wButtons, debugMode);
        
        }
        



       
      
            

        if(debugMode) {
            std::cout << "LX: " << state.Gamepad.sThumbLX
                      << " LY: " << state.Gamepad.sThumbLY
                      << " RX: " << state.Gamepad.sThumbRX
                      << " RY: " << state.Gamepad.sThumbRY
                      << " Buttons: " << state.Gamepad.wButtons
                      << "\r" << std::flush;
        }


        //frequency 4ms
        Sleep(4);
    }

    return 0;
}
