
#include <stdio.h> 
#include <stdlib.h> 

#ifdef __linux__ 
    #include<unistd.h>
    #define SLEEP_TIME 1
#elif _WIN32
    #include<windows.h>
    #define SLEEP_TIME 1000
    void sleep(int time){
        Sleep(time);
    }
#else

#endif



int GameRum(int* clock);
int GameFeatures(int* clock);

//code
int GameRum(int* clock)
{
    int lastclock = 0;
    int on = 1;
    while (on)
    {
        if (*clock != lastclock)
        {
            lastclock = *clock;

            //o que vai acontecer
            GameFeatures(clock);
        }else
        {
            sleep(SLEEP_TIME);
            *clock += 1;
        }
    }

    return 1;
}

int GameFeatures(int* clock)
{
    printf("%i %s",*clock, "\n");
};

int main()
{
    int clock;
    GameRum(&clock);

    return 1;
}