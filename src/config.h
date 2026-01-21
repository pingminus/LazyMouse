#pragma once
#include <string>
#include <windows.h>

extern float CURSOR_SPEED;
extern float SCROLL_SPEED;
extern short DEADZONE;

void loadConfig(const std::string& filename);

