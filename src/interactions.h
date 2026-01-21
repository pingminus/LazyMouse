#pragma once
#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <map>
#include <string>
void updateMorse(const XINPUT_STATE &state);
void moveMouse(int dx, int dy);
void interactButtons(short buttons, bool debugMode = false);
void updateScroll(short RX, short RY, bool debugMode = false);
void updateMouse(short LX, short LY, bool debugMode = false);

/*   short Button = state.Gamepad.wButtons;
            std::cout << Button << "\n";
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
            std::cout << "A pressed\n";
            }*/
