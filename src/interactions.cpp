#include "interactions.h"
#include "config.h"

/*
    Everything that is related to mouse activity this includes:
        -left/right clicking
        -mouse movement
        -scrolling
        ...

*/

// for the compiler ya
extern float CURSOR_SPEED;
extern float SCROLL_SPEED;
extern short DEADZONE;


void moveMouse(int dx, int dy) {
    POINT p; 
    GetCursorPos(&p);
    SetCursorPos(p.x + dx, p.y + dy);
} 
void LeftClick(){
    INPUT input = {0};

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}
void RightClick(){
    INPUT input = {0};

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}
void WindowsClick(){
 INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_LWIN;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    

    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_LWIN;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
bool bPressedLast = false;
bool ePressedLast = false;

bool aPressedLast = false;
bool dragging = false; 

//Manage ALL buttons that are pressed like A B and Select
void interactButtons(short buttons, bool debugMode){
    bool aPressed = (buttons & 4096) != 0;
    bool bPressed = (buttons & XINPUT_GAMEPAD_B) != 0;
    bool ePressed = (buttons & XINPUT_GAMEPAD_START) != 0;

    if(aPressed && !aPressedLast){
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(INPUT));
        dragging = true;
        if(debugMode) std::cout << "A pressed (drag start)\n";
    }

    if(!aPressed && aPressedLast){
      
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
        dragging = false;
        if(debugMode) std::cout << "A released (drag end)\n";
    }

    aPressedLast = aPressed;


    if(bPressed && !bPressedLast){
        RightClick();
        if(debugMode) std::cout << "B pressed ";
    }
    bPressedLast = bPressed;

    if(ePressed && !ePressedLast){
        WindowsClick();
        if(debugMode) std::cout << "Windows Button pressed ";
    }
    ePressedLast = ePressed;
}


// Manage scrolling from the second stick
void updateScroll(short RX, short RY, bool debugMode) {
    static float smoothRY = 0.0f;

    if(abs(RY) < DEADZONE) RY = 0;

    smoothRY = smoothRY * 0.7f + RY * 0.3f;

    int scrollAmount = static_cast<int>(smoothRY * SCROLL_SPEED);
    
    if(scrollAmount != 0) {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        input.mi.mouseData = scrollAmount;
        SendInput(1, &input, sizeof(INPUT));
        if(debugMode) std::cout << "Scrolling Up/Down: " << scrollAmount << " ";
    }
}

// Manage Cursor by using first xbox stick
void updateMouse(short LX, short LY, bool debugMode) {
    const short DEADZONE = 7849;
    static float smoothX = 0.0f;
    static float smoothY = 0.0f;

    if(abs(LX) < DEADZONE) LX = 0;
    if(abs(LY) < DEADZONE) LY = 0;

    smoothX = smoothX * 0.7f + LX * 0.3f;
    smoothY = smoothY * 0.7f + LY * 0.3f;

    if(debugMode)
        std::cout << "X: " << LX << " Y: " << LY << "\n";

    POINT p;
    GetCursorPos(&p);
    SetCursorPos(
        p.x + static_cast<int>(smoothX * CURSOR_SPEED),
        p.y - static_cast<int>(smoothY * CURSOR_SPEED)  // invert Y
    );
}
