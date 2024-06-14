#ifndef BASE_HPP
#define BASE_HPP

#define CHAR_FREE ' '
#define CHAR_WALL '|'

#ifdef __linux__ 
    #include<unistd.h> //* sleep
    #define CLEAR "clear"
    #define SLEEP_TIME 100000
    #define CHAR_BORD '>'
    #define CHAR_BLOCK '#'
    clearScreen()
    {
        system(CLEAR);
    };

#elif _WIN32

    #include <windows.h> //* sleep
    #include <conio.h> //* getchar & getch
    #define CLEAR "cls"
    #define SLEEP_TIME 100
    #define CHAR_BORD 205
    #define CHAR_BLOCK 219    

    //how it works? i have no idia
    void clearScreen()
    {
        HANDLE hOut;
        COORD Position;

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        Position.X = 0;
        Position.Y = 0;
        SetConsoleCursorPosition(hOut, Position);
    }

    void usleep(int time)
    {
        Sleep(time);
    };

    int getKeyChar(void)
    {
        return getch();
    }
#else

#endif



#endif