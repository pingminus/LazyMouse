#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
/*
    Configure start values
*/
float CURSOR_SPEED = 0.0008f;
float SCROLL_SPEED = 0.04f;
short DEADZONE = 7849;

void loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cout << "Config file not found, using defaults\n";
        return; 
    }

    std::string line;
    while(std::getline(file, line)) {
        if(line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string key;
        if(!std::getline(ss, key, '=')) continue;
        std::string value;
        if(!std::getline(ss, value)) continue;

        if(key == "CURSOR_SPEED") CURSOR_SPEED = std::stof(value);
        else if(key == "SCROLL_SPEED") SCROLL_SPEED = std::stof(value);
        else if(key == "DEADZONE") DEADZONE = static_cast<short>(std::stoi(value));
    }
}
