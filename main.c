
#include <stdio.h> 
#include <stdlib.h> 
#define SCREEM_SIZE 128
#define SCREEM_HEIGHT 8
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
int wayGenerator(char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int gameFeatures(int* clock, int* on, char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int wayUpdater(char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int wayPrinter(char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int printBord();
int clearScream();
int createNewCol(char way [SCREEM_SIZE][SCREEM_HEIGHT], char new_way [SCREEM_HEIGHT]);

//code
int clearScream()
{
    system(CLEAR);
}
int gameRum(int* clock)
{
    int lastclock = 0;
    int on = 1;
    char way [SCREEM_SIZE][SCREEM_HEIGHT];
    wayGenerator(way);
    while (on)
    {
        if (*clock != lastclock)
        {
            clearScream();
            lastclock = *clock;

            //o que vai acontecer
            gameFeatures(clock, &on, way);
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
    printf("\033[33m");
    char c = 205;
    for (size_t i = 0; i < SCREEM_SIZE; i++)
    {
            printf("%c", c);
    }
    printf("\n\033[0m");
}

int gameFeatures(int* clock, int* on, char way [SCREEM_SIZE][SCREEM_HEIGHT])
{
    printBord();
    wayUpdater(way);
    wayPrinter(way);
    printBord();
};

int wayGenerator(char way [SCREEM_SIZE][SCREEM_HEIGHT])
{
    for (size_t i = 0; i < SCREEM_SIZE; i++)
    {
        if (i == 0)
        {
            for (size_t j = 0; j < SCREEM_HEIGHT; j++)
            {
                way[i][j] = '|';
            }
        }else{
            for (size_t j = 0; j < SCREEM_HEIGHT; j++)
            {
                way[i][j] = ' ';
            }
        }
    }
    for (size_t i = 0; i < SCREEM_SIZE/2; i++)
    {
        wayUpdater(way);
    }
    
}
int wayUpdater(char way [SCREEM_SIZE][SCREEM_HEIGHT])
{
    //walk way
    for (size_t i = 1; i < SCREEM_SIZE-1; i++)
    {
        for (size_t j = 0; j < SCREEM_HEIGHT; j++)
        {
            way[i][j] = way[(i+1)][j];
        }
    }
    //create new col

    char new_way [SCREEM_HEIGHT];
    createNewCol(way, new_way);
    

    //implemente the new col
    for (size_t i = 0; i < SCREEM_HEIGHT; i++)
    {
        way[(SCREEM_SIZE-1)][i] = new_way[i];
    }
};

int createNewCol(char way [SCREEM_SIZE][SCREEM_HEIGHT], char new_way [SCREEM_HEIGHT])
{
    int pass_col = 0;
    for (size_t i = 0; i < SCREEM_HEIGHT; i++)
    {

        int r =(rand() % ((int)2));
        if (r == 0)
        {
            pass_col++;
            new_way[i] = ' ';
        }else
        {
            new_way[i] = 219;
        }
    }

    if (pass_col == 0)
    {
        new_way[(rand() % SCREEM_HEIGHT)] = ' ';
    }
    
    for (size_t i = 1; i < SCREEM_HEIGHT-1; i++)
    {
        if (new_way[(i+1)] != ' ' && new_way[(i+1)] != ' ')
        {
            if (rand() % 2 == 0)
            {
                new_way[(i+1)] = ' ';
            }
            else
            {
                new_way[(i-1)] = ' ';
            }
        }
    }

}

int wayPrinter(char way [SCREEM_SIZE][SCREEM_HEIGHT])
{
    for (size_t i = 0; i < SCREEM_HEIGHT; i++)
    {
        for (size_t j = 0; j < SCREEM_SIZE; j++)
        {
            printf("%c", way[j][i]);
        }
        printf("\n");
    }
    
}

int main()
{
    int clock;
    gameRum(&clock);

    return 1;
}