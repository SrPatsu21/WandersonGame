#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>

#define CHAR_FREE ' '
#define CHAR_WALL '|'

    #ifdef __linux__ 
        #include<unistd.h> //* sleep

        //* get char
        #include <termios.h> 
        #include <unistd.h> 
        #include <stdio.h> 

        #define CLEAR "clear"
        #define SLEEP_TIME 100000
        #define CHAR_BORD '>'
        #define CHAR_BLOCK '#'
        void static clearScreen()
        {
            std::system(CLEAR);
        }

        int static getch(void) 
        { 
            struct termios oldattr, newattr; 
            int ch; 
            tcgetattr(STDIN_FILENO, &oldattr); 
            newattr = oldattr; 
            newattr.c_lflag &= ~(ICANON | ECHO); 
            tcsetattr(STDIN_FILENO, TCSANOW, &newattr); 
            ch = getchar(); 
            tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); 
            return ch; 
        } /* reads from keypress, echoes */ 
        int static getche(void) 
        { 
            struct termios oldattr, newattr; 
            int ch; 
            tcgetattr(STDIN_FILENO, &oldattr); 
            newattr = oldattr; 
            newattr.c_lflag &= ~(ICANON); 
            tcsetattr(STDIN_FILENO, TCSANOW, &newattr); 
            ch = getchar(); 
            tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); 
            return ch; 
        }

        int static getKeyChar(void)
        {
            // 1 for echo, 0 for no echo
            return getch();
        }

    #elif _WIN32

        #include <windows.h> //* sleep
        #include <conio.h> //* getchar & getch
        #define CLEAR "cls"
        #define SLEEP_TIME 100
        #define CHAR_BORD 205
        #define CHAR_BLOCK 219    

        //how it works? i have no idia
        void static clearScreen()
        {
            HANDLE hOut;
            COORD Position;

            hOut = GetStdHandle(STD_OUTPUT_HANDLE);

            Position.X = 0;
            Position.Y = 0;
            SetConsoleCursorPosition(hOut, Position);
        }

        void static usleep(int time)
        {
            Sleep(time);
        };

        int static getKeyChar(void)
        {
            return getch();
        }
    #endif



#endif