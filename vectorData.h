#ifndef _VECTORDATA_H_
    #define _VECTORDATA_H_
#include "vectorAPI.h"

#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>
#include <math.h>


/* Only globalScreen is declared here as localScreen 
* would only be a smaller portion of globalScreen.
* This will simply be printed by ncurses
*/

int_u SSIZEX;
int_u SSIZEY;

char** globalScreen;

int_u localX;
int_u localY;
int_u localXSize;
int_u localYSize;


/*
 * Struct containing pointers to all objects in the global screen
 */
typedef struct {
    int_u numLines;
    int_u numLinesAlloc;
    lineVector** lines;

    int_u numCircles;
    int_u numCirclesAlloc;
    circleVector** circles;

    int_u numRectangles;
    int_u numRectanglesAlloc;
    rectVector** rectangles;

    int_u numTexts;
    int_u numTextsAlloc;
    textVector** texts;

} vectorObjects;

vectorObjects* vectorData;

textVector *printScreen;

#endif
