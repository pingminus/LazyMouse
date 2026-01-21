# LazyMouse (A Harvard CS 50 Final Project by Niklas)

#### Description:

**LazyMouse** is a Windows application that converts Xbox controller input into mouse and keyboard events and was submitted as CS50 Final Project. This project demonstrates the use of the XInput API to interface with gaming hardware and translate analog inputs into precision cursor control. Additionally it supports text/keyboard input via morse code.

## Features

- **Mouse Movement**: Control mouse cursor with the left analog stick
- **Mouse Scrolling**: Scroll using the right analog stick
- **Button Interactions**: Map Xbox buttons to mouse clicks and keyboard actions
- **Morse Code Mode**: Toggle between mouse control and Morse code text input via the Y button
- **Debug Mode**: Real-time display of controller input values for development

## Technologies Used

- **Language**: C++
- **API**: XInput (Windows)
- **Libraries**: Windows API, standard C++ libraries
- **Platform**: Windows

## How to Build

### req. C++17 and g++ compiler

```bash
./build.bat
```

## How to Run

```bash
# Normal mode
./build/main.exe

# Debug mode (displays controller input values)
./build/main.exe -debug
```

## Changes

You can manually adjust the Cursor Speed, Scroll Speed, and Deadzone in the config.ini file by modifying the corresponding values to suit your preferences.

## Controls

- **Left Stick**: Move mouse cursor
- **Right Stick**: Scroll
- **Y Button**: Toggle between mouse mode and Morse code mode
- **Other Buttons**: Mouse clicks and keyboard interactions (see `interactions.cpp`)

## Requirements

- Windows OS
- Xbox controller connected via USB
- C++ compiler (Visual Studio recommended)
