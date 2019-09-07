//
//  input.cpp
//  GAME
//
//  Created by Gabriel Z on 2019/5/3.
//  Copyright © 2019 Gabriel. All rights reserved.
//

#include <termios.h>
#include <unistd.h>

struct termios terminalSettings;

void input_on()
{
    struct termios newTerminalSettings;
    
    tcgetattr( STDIN_FILENO, &terminalSettings );
    
    newTerminalSettings = terminalSettings;
    
    newTerminalSettings.c_lflag &= ~( ICANON | ECHO );
    newTerminalSettings.c_cc[VTIME] = 0;
    newTerminalSettings.c_cc[VMIN] = 1;
    
    tcsetattr( STDIN_FILENO, TCSANOW, &newTerminalSettings );
}

void input_off()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &terminalSettings);
}

