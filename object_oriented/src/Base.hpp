#ifndef BASE_HPP
#define BASE_HPP

// #include <time.h>//rand
// #include <pthread.h> // Multithreading
#define CHAR_FREE ' '
#define CHAR_WALL '|'

#ifdef __linux__ 
    #define CLEAR "clear"
    #define SLEEP_TIME 500000
    #define KEY_SLEEP_TIME 100000
    #define CHAR_BORD '>'
    #define CHAR_BLOCK '#'

#elif _WIN32
    // #include <windows.h>
    // #include <conio.h>
    #define CLEAR "cls"
    #define SLEEP_TIME 500
    #define KEY_SLEEP_TIME 100
    #define CHAR_BORD 205
    #define CHAR_BLOCK 219    

    // int getKeyChar()
    // {
    //     return getch();
    // }
    // void usleep(int time)
    // {
    //     Sleep(time);
    // };
#else

#endif



#endif