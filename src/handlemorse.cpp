
#include "handlemorse.h"



// Morse Table
std::map<std::string, char> morseTable = {
    {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
    {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
    {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
    {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
    {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
    {"--..", 'Z'}, {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
    {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'},
    {"----.", '9'}
};

// Globals
bool morseMode = false;
std::string currentMorse = "";
std::string typedText = "";
DWORD pressStart = 0;
bool buttonPressed = false;

void displayText(const std::string &text) {
    static std::string lastText = "";
    if(text != lastText) {
        std::cout << "\r" << std::string(80, ' ') << "\r"; 
        std::cout << "Text: " << text << std::flush;
        lastText = text;
    }
}
//sendkey to Windows
void sendKey(char c) {
    if(c >= 'a' && c <= 'z') c = c - 'a' + 'A';

    SHORT vk = 0;

    if(c >= 'A' && c <= 'Z') vk = 0x41 + (c - 'A'); // A-Z
    else if(c >= '0' && c <= '9') vk = 0x30 + (c - '0'); // 0-9
    else if(c == '\n') vk = VK_RETURN;
    else if(c == ' ') vk = VK_SPACE;
    else if(c == '\b') vk = VK_BACK; 
    else return;

    INPUT input[2] = {};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = vk;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = vk;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}
// Track and manage morse code
void updateMorse(const XINPUT_STATE &state) {
    static DWORD lastBackspaceTime = 0;
    static DWORD lastEnterTime = 0;
    static DWORD lastInputTime = 0;
    static bool buttonPressed = false;
    static DWORD pressStart = 0;

    bool APressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
    DWORD now = GetTickCount();

    if (APressed && !buttonPressed) {
        buttonPressed = true;
        pressStart = now;
    }

    if (!APressed && buttonPressed) {
        buttonPressed = false;
        DWORD duration = now - pressStart;
        if(duration < 250) currentMorse += ".";
        else currentMorse += "-";

        // Haptic feedback
        XINPUT_VIBRATION vibration = {};
        vibration.wLeftMotorSpeed = 5000;
        XInputSetState(0, &vibration);
        Sleep(50);
        vibration.wLeftMotorSpeed = 0;
        XInputSetState(0, &vibration);

        lastInputTime = now;
    }
    // COnvert to input after 600ms
    if (!currentMorse.empty() && now - lastInputTime > 1000) {
        if(morseTable.find(currentMorse) != morseTable.end()) {
            typedText += morseTable[currentMorse];
            sendKey(morseTable[currentMorse]);
        }
        currentMorse = "";
    }

    if(state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
        if(now - lastBackspaceTime > 300 && !typedText.empty()) {
            typedText.pop_back();   // Lokal 
            sendKey('\b');          
            lastBackspaceTime = now;
        }
    }
    if(state.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
        if(now - lastEnterTime > 300) {
            typedText += '\n';
            lastEnterTime = now;
        }
    }
    // Display in terminal
    displayText(typedText);
}