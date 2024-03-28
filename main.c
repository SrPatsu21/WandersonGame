
#include <stdio.h> 
#include <stdlib.h> 

#ifdef __linux__ 
    #include<unistd.h>
    #define CLEAR "clear"
    #define SLEEP_TIME 1

#elif _WIN32
    #include<windows.h>
    #define CLEAR "cls"
    #define SLEEP_TIME 1000

    void sleep(int time)
    {
        Sleep(time);
    }
#else

#endif


int gameRum(int* clock);
int gameFeatures(int* clock);
int printBord();
int clearScream();

//code
int clearScream()
{
    system(CLEAR);
}
int gameRum(int* clock)
{
    int lastclock = 0;
    int on = 1;
    while (on)
    {
        if (*clock != lastclock)
        {
            clearScream();
            lastclock = *clock;

            //o que vai acontecer
            gameFeatures(clock);
        }else
        {
            sleep(SLEEP_TIME);
            *clock += 1;
        }
    }

    return 1;
}

int printBord()
{
    printf("\033[33m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\033[0m");
}

int gameFeatures(int* clock)
{
    printBord();
    printf("\033[33m+\n\033[33m");
    printf("\033[33m+\n\033[33m");
    printf("\033[33m+\033[33m");
    printf("%i %s",*clock, "\n");
    printf("\033[33m+\n\033[33m");
    printf("\033[33m+\n\033[33m");
    printBord();
};

int main()
{
    int clock;
    gameRum(&clock);

    return 1;
}