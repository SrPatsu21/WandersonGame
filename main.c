
#include <stdio.h> 
#include <stdlib.h> 
#define SCREEM_SIZE 128
#define SCREEM_HEIGHT 8
#define CHAR_FREE ' '
#define CHAR_WALL '|'
#define CHAR_AIR_PLANE '@'

#ifdef __linux__ 
    #include<unistd.h>
    #define CLEAR "clear"
    #define SLEEP_TIME 0.5
    #define CHAR_BORD '>'
    #define CHAR_BLOCK '#'

#elif _WIN32
    #include<windows.h>
    #define CLEAR "cls"
    #define SLEEP_TIME 500
    #define CHAR_BORD 205
    #define CHAR_BLOCK 219

    void sleep(int time)
    {
        Sleep(time);
    }
#else

#endif

typedef struct Plane
{
    int x, y;
} AVIAO;

//n mexer no que ta certo
int gameRum(int* clock);
int clearScream();
int printBord();
//arrumar
int gameFeatures(int* clock, int* on, char way [SCREEM_SIZE][SCREEM_HEIGHT], AVIAO* aviao);
int wayGenerator(char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int wayUpdater(char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int wayPrinter(char way [SCREEM_SIZE][SCREEM_HEIGHT], AVIAO* aviao);
int createNewCol(char way [SCREEM_SIZE][SCREEM_HEIGHT], char new_way [SCREEM_HEIGHT]);
int isColliding(char way [SCREEM_SIZE][SCREEM_HEIGHT], AVIAO* aviao);

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
    //aviao init
    AVIAO aviao;
    aviao.x = 2;
    aviao.y = ((int)SCREEM_HEIGHT/2);
    while (on)
    {
        if (*clock != lastclock)
        {
            clearScream();
            lastclock = *clock;

            //o que vai acontecer
            gameFeatures(clock, &on, way, &aviao);
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
    for (size_t i = 0; i < SCREEM_SIZE; i++)
    {
            printf("%c", ((char)CHAR_BORD));
    }
    printf("\n\033[0m");
}

int gameFeatures(int* clock, int* on, char way [SCREEM_SIZE][SCREEM_HEIGHT], AVIAO* aviao)
{
    //server
    wayUpdater(way);
    *on = isColliding(way, aviao);
    //client
    printBord();
    wayPrinter(way, aviao);
    printBord();
};

int wayGenerator(char way [SCREEM_SIZE][SCREEM_HEIGHT])
{
    //wall
    for (size_t j = 0; j < SCREEM_HEIGHT; j++)
    {
        way[0][j] = CHAR_WALL;
    }
    //pista
    for (size_t i = 1; i < SCREEM_SIZE; i++)
    {
        for (size_t j = 0; j < SCREEM_HEIGHT; j++)
        {
            way[i][j] = CHAR_FREE;
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

        int r =(rand() % 2);
        if (r == 0)
        {
            pass_col++;
            new_way[i] = CHAR_FREE;
        }else
        {
            new_way[i] = ((char)CHAR_BLOCK);
        }
    }

    if (pass_col == 0)
    {
        new_way[(rand() % SCREEM_HEIGHT)] = CHAR_FREE;
    }
    
    for (size_t i = 1; i < SCREEM_HEIGHT-1; i++)
    {
        if (new_way[(i+1)] != CHAR_FREE && new_way[(i+1)] != CHAR_FREE)
        {
            if (rand() % 2 == 0)
            {
                new_way[(i+1)] = CHAR_FREE;
            }
            else
            {
                new_way[(i-1)] = CHAR_FREE;
            }
        }
    }

}

int wayPrinter(char way [SCREEM_SIZE][SCREEM_HEIGHT], AVIAO* aviao)
{
    for (size_t i = 0; i < SCREEM_HEIGHT; i++)
    {
        for (size_t j = 0; j < SCREEM_SIZE; j++)
        {
            //print plane
            if (i == aviao->y && j == aviao->x)
            {

                    printf("\033[31m");
                    printf("%c", CHAR_AIR_PLANE);
                    printf("\033[0m");
            }else
            {
                printf("%c", way[j][i]);
            }
        }
        printf("\n");
    }
}

int isColliding(char way [SCREEM_SIZE][SCREEM_HEIGHT], AVIAO* aviao)
{
    if (((char) way[aviao->x][aviao->y]) == ((char) CHAR_BLOCK))
    {
        return 0;
    }else
    {
        return 1;
    }    
}

int main()
{
    int clock;

    char nome[20];

    printf("\033[32mSeja bem vindo(a) ao nosso jogo!!!\033[0m\n");
    printf("\033[36mPor favor, digite o seu nome: \033[0m\n");
    scanf("%s", nome);

    gameRum(&clock);

    printf("Game Over\n %s: fez um total de %i pontos", nome, clock);
    return 1;
}