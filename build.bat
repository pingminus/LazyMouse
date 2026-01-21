@cd src

@g++ main.cpp handlemorse.cpp config.cpp interactions.cpp -o main.exe -lxinput

@copy main.exe ..
@del main.exe 
@cd ..
echo succes


