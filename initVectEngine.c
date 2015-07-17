#include "vectorAPI.h"
#include "vectorData.h"

typedef unsigned char char_u;

#define FALSE 0
#define TRUE 1

void initVect(unsigned int ssizex, unsigned int ssizey)
{
    /*
     * NCurses initialisation business
     */
    char* locale;
    locale = setlocale(LC_ALL,"");

    initscr();
    cbreak();
    nodelay(stdscr,TRUE);
    keypad(stdscr,TRUE);
    curs_set(0);
    scrollok(stdscr,FALSE);
    noecho();

    if(has_colors() == FALSE)
    {
        endwin();
        printf("Terminal lacks color support.\n");
    }
    else
        start_color();

    /*
     * Vector initialisation things from here on
     *
     * SSIZE vars indicate screen size
     * local screen is initally the same as 
     */
    collisionOccurred = 0;
    SSIZEX = ssizex;
    SSIZEY = ssizey;

    localX = 0;
    localY = 0;
    localXSize = SSIZEX;
    localYSize = SSIZEY;

    /*
     * Create & initialise global screen
     */
    
    globalScreen = (char**)malloc(SSIZEX * sizeof(char*));
    int i;
    for(i = 0;i < SSIZEX;i++)
        globalScreen[i] = (char*)malloc(SSIZEY * sizeof(char));

    int j;
    for(i = 0;i < SSIZEX;i++)
    {
        for(j = 0; j < SSIZEY;j++)
        {
            globalScreen[i][j] = (char)0x20;
        }
    }

    /*
     * Create and initialise vectorData datastructure 
     * for vectors to live in
     */
    vectorData = (vectorObjects*) malloc(sizeof(vectorObjects));
    if(vectorData != NULL)
    {
        vectorData->numLines = 0;
        vectorData->numLinesAlloc = 10;
        vectorData->lines = (lineVector**) malloc(10 * sizeof(lineVector*));
        
        vectorData->numCircles = 0;
        vectorData->numCirclesAlloc = 10;
        vectorData->circles = (circleVector**) malloc(10 * sizeof(circleVector*));
        
        vectorData->numRectangles = 0;
        vectorData->numRectanglesAlloc = 10;
        vectorData->rectangles = (rectVector**) malloc(10 * sizeof(rectVector*));

        vectorData->numTexts = 0;
        vectorData->numTextsAlloc = 10;
        vectorData->texts = (textVector**) malloc(10 * sizeof(textVector*));
    }

    printScreen = addText(createText("",60,5));

    printw("%c",globalScreen[0][0]);
}

void exitVect()
{   int i;
    endwin();
    curs_set(1);

    for(i = 0;i < vectorData->numLinesAlloc;i++)
        free(vectorData->lines[i]);
    for(i = 0;i < vectorData->numCirclesAlloc;i++)
        free(vectorData->circles[i]);
    for(i = 0;i < vectorData->numRectanglesAlloc;i++)
        free(vectorData->rectangles[i]);
    for(i = 0;i < vectorData->numTextsAlloc;i++)
        free(vectorData->texts[i]);

    for(i = 0;i < SSIZEX;i++)
        free(globalScreen[i]);
}
