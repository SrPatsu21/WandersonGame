#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> // Multithreading
#define SCREEM_SIZE 128
#define SCREEM_HEIGHT 8
#define CHAR_FREE ' '
#define CHAR_WALL '|'
#define CHAR_AIR_PLANE '@'

#ifdef __linux__ 
    #include <termios.h> // For changing terminal mode
    #include <unistd.h>  // For changing terminal mode
    #define CLEAR "clear"
    #define SLEEP_TIME 500000
    #define CHAR_BORD '>'
    #define CHAR_BLOCK '#'
    struct termios original; // A struct to save the original state of terminal

    int getKeyChar(void)
    {
        return getchar();
    }

#elif _WIN32
    #include <windows.h>
    #include <conio.h>
    #define CLEAR "cls"
    #define SLEEP_TIME 500
    #define CHAR_BORD 205
    #define CHAR_BLOCK 219    

    int getKeyChar(void)
    {
        return getch();
    }
    void usleep(int time)
    {
        Sleep(time);
    };
#else

#endif

typedef struct GameInfo
{
    int pos_x, pos_y, clock, runing;
    char way [SCREEM_SIZE][SCREEM_HEIGHT];
} GAME_INFO;

//n mexer no que ta certo
void* gameRun(void * game_info);
void* keyGet(void* game_info);
int clearScream();
int printBord();
//arrumar
int gameFeatures(GAME_INFO * game);
int wayGenerator(char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int wayUpdater(char way [SCREEM_SIZE][SCREEM_HEIGHT]);
int wayPrinter(char way [SCREEM_SIZE][SCREEM_HEIGHT], int x, int y);
int createNewCol(char way [SCREEM_SIZE][SCREEM_HEIGHT], char new_way [SCREEM_HEIGHT]);
int isColliding(char way [SCREEM_SIZE][SCREEM_HEIGHT], int x, int y, int is);
void enableRAWMode();
void disableRAWMode();
//code

int main()
{
    enableRAWMode();
    //game
    GAME_INFO game;

    game.clock = 0;
    game.pos_x = 2;
    game.pos_y = ((int)SCREEM_HEIGHT/2);
    game.runing = 1;    

    //thread
    pthread_t id_gameRun, id_keyGet;

    //name
    disableRAWMode();
    
    char nome[20];

    printf("\033[32mSeja bem vindo(a) ao nosso jogo!!!\033[0m\n");
    printf("\033[36mPor favor, digite o seu nome: \033[0m\n");
    scanf("%s", nome);

    //run
    pthread_create(&id_gameRun, NULL, gameRun, &game);
    pthread_create(&id_keyGet, NULL, keyGet, &game);
    pthread_join(id_gameRun, NULL);
    pthread_join(id_keyGet, NULL);

    disableRAWMode();
    //end
    printf("Game Over\n%s: fez um total de %i pontos \n", nome, game.clock);
    return 1;
};

void* gameRun(void* game_info)
{
    GAME_INFO * game = (GAME_INFO *) (game_info);
    int lastclock = 0;
    wayGenerator(game->way);

    while (game->runing)
    {
        if (game->clock != lastclock)
        {
            clearScream();
            lastclock = game->clock;

            //o que vai acontecer
            gameFeatures(game);
            game->runing = isColliding(game->way, game->pos_x, game->pos_y, game->runing);
        }else
        {
            usleep(SLEEP_TIME);
            game->clock += 1;
        }
    }
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
    return 1;
};
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
    return 1;
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
    return 1;
};
int clearScream()
{
    system(CLEAR);
    return 1;
}
int gameFeatures(GAME_INFO* game)
{
    //server
    wayUpdater(game->way);
    //client
    printBord();
    wayPrinter(game->way, game->pos_x, game->pos_y);
    printBord();
    return 1;
};
int isColliding(char way [SCREEM_SIZE][SCREEM_HEIGHT], int x, int y, int is)
{
    if (((char) way[x][y]) == ((char) CHAR_BLOCK) || ((char) way[x][y]) == ((char) CHAR_WALL) )
    {
        return 0;
    }else
    {
        return is;
    }    
};
int printBord()
{
    printf("\033[33m");
    for (size_t i = 0; i < SCREEM_SIZE; i++)
    {
            printf("%c", ((char)CHAR_BORD));
    }
    printf("\n\033[0m");
    return 1;
};
int wayPrinter(char way [SCREEM_SIZE][SCREEM_HEIGHT], int x, int y)
{
    for (size_t i = 0; i < SCREEM_HEIGHT; i++)
    {
        for (size_t j = 0; j < SCREEM_SIZE; j++)
        {
            //print plane
            if (i == y && j == x)
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
    return 1;
};

void* keyGet(void* game_info)
{
    GAME_INFO * game = (GAME_INFO *) (game_info);
    enableRAWMode();
    char ch = '\0';
    while (game->runing)
    {
        ch = getKeyChar();
        if (ch != '\0')
        {
            if ('w' == ch || 'W' == ch)
            {
                if (0 < game->pos_y)
                {
                    game->pos_y--;
                }
            }else if ('s' == ch || 'S' == ch)
            {
                if (SCREEM_HEIGHT-1 > game->pos_y)
                {
                    game->pos_y++;
                }
            }else if('a' == ch || 'A' == ch)
            {
                if (0 < game->pos_x)
                {
                    game->pos_x--;
                }
            }else if('d' == ch || 'D' == ch)
            {
                if (SCREEM_SIZE > game->pos_x)
                {
                    game->pos_x++;
                }
            }
            //update all
            game->runing = isColliding(game->way, game->pos_x, game->pos_y, game->runing);
            clearScream();
            printBord();
            wayPrinter(game->way, game->pos_x, game->pos_y);
            printBord();
            ch = '\0';
        }
    }
};

#ifdef __linux__
    /// This function enables RAW mode for terminal.
    void enableRAWMode() 
    {
        struct termios raw;
        tcgetattr(STDIN_FILENO, &raw);
        tcgetattr(STDIN_FILENO, &original);
        atexit(&disableRAWMode);
        raw.c_lflag &= ~(ECHO | ICANON);

        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    };

    void disableRAWMode() 
    {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    };
#elif _WIN32
    /// This function enables RAW mode for terminal.
    void enableRAWMode() 
    {
    };

    void disableRAWMode() 
    {
    };

#endif