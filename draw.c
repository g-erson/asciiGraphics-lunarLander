#include "vectorAPI.h"
#include "vectorData.h"


void clearScreen()
{
    clear();
}

void printToScreen(char *s)
{
    changeText(printScreen,s);
}

void clearPrintScreen()
{
    changeText(printScreen,"");
}

/*
 * Prints globalScreen to the actual screen
 * TODO allow printing of parts of globalScreen
 */
void drawLocalScreen()
{
    if( localX == 0 && localY == 0 &&
        localXSize == SSIZEX && 
        localYSize == SSIZEY)
    {
        int i;
        int j;
        for(i = 0;i < SSIZEX;i++)
        {
            for(j = 0;j < SSIZEY;j++)
                mvaddch(j,i,globalScreen[i][j]);
        }
    }
}

/*
 * Selects the most appropriate character to use
 * for a line given its gradient, and the current
 * error in bresenham's algorithm
 */
char selectChar(float gradient, float error)
{
    float grad = fabsf(gradient);

    if(grad >= 0 && grad < 1)
    {
        if(gradient >= 0)
        {
            if(error < grad/2)
                return 0x27;
            if(error > grad )
                return '.';
            else 
                return '-';
        }
        else
        {
            if(error < grad/2)
                return '.';
            if(error > grad )
                return 0x27;
            else 
                return '-';
        }
    }
    else if(grad >= 1 && grad < 2)
    {
        return '|';
    }
    else if(grad >= 2)
    {
        return '|';
    }
    return '#';
}

/*
 * This rasterises the line using Bresenham's 
 * line algorithm
 */
void drawLineToGlobalScreen(lineVector* line)
{

    /*
     * TODO doesn't draw correctly when coordinate outside X 
     * range
     */
    
    int_u x1 = (int_u)(line->x1 - 0.5);
    int_u y1 = (int_u)(line->y1 - 0.5);
    int_u x2 = (int_u)(line->x2 - 0.5);
    int_u y2 = (int_u)(line->y2 - 0.5);
    int_u tmp;

    int deltax = (int)(x2) - (int)(x1);
    int deltay = (int)(y2) - (int)(y1);

    float gradient = (float) deltay / (float) deltax;
    float error = 0;


    /*
     * Changes coordinates around so they are printed correctly
     */
    if((x1 > x2 && gradient > 0) || (x1 < x2 && gradient < 0))
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;

        tmp = y1;
        y1 = y2;
        y2 = tmp;

        deltax = -deltax;
        deltay = -deltay;
    }

    int i,j;

    if(deltax == 0)
    {
        /*
         * vertical line
         */
        for(i = 0;i < abs(deltay);i++)
        {
            if(deltay < 0 && y2 + i < SSIZEY && x2 < SSIZEX)
                globalScreen[x2][y2 + i] = '|';
            else if(y2 - i < SSIZEY)
                globalScreen[x2][y2 - i] = '|';
        }
    }
    if(deltay == 0)
    {
        for(i = 0;i < abs(deltax);i++)
        {
            if(deltax < 0 && x2 + i < SSIZEX && y2 < SSIZEY)
                globalScreen[x2 + i][y2] = '-';
            else if(x2 - i < SSIZEX)
                globalScreen[x2 - i][y2] = '-';
        }
    }
    else
    {
        int y = 0;
        int x = 0;

        for(x = 0;x < abs(deltax);x++)
        {
            error += gradient;

            if(gradient > 0)
            {
                while(error >= 0.5)
                {
                    if(x1 + x < SSIZEX && y1 + y < SSIZEY)
                        globalScreen[x1 + x][y1 + y] = selectChar(gradient,error);

                    if(deltay < 0)
                        y--;
                    else
                        y++;
                    error--; 
                }
                if(x1 + x < SSIZEX && y1 + y < SSIZEY)
                    globalScreen[x1 + x][y1 + y] = selectChar(gradient,error);
            }
            else
            {
                while(error <= 0.5)
                {
                    if(x1 - x < SSIZEX && y1 + y < SSIZEY)
                        globalScreen[x1 - x][y1 + y] = selectChar(gradient,error);

                    if(deltay < 0)
                        y--;
                    else
                        y++;
                    error++; 
                }
                if(x1 - x < SSIZEX && y1 + y < SSIZEY)
                    globalScreen[x1 - x][y1 + y] = selectChar(gradient,error);
            }
        }
    }
}

/*
 * Draws text to screen at its location
 * and calls collision function if a 
 * collision has occurred
 */
void drawTextToGlobalScreen(textVector* text)
{
    int_u x = (int_u)(text->x - 0.5);
    int_u y = (int_u)(text->y - 0.5);

    int i = 0;
    while(text->text[i] != '\0')
    {
        if( x + i < SSIZEX && y < SSIZEY)
        {
            if(globalScreen[x + i][y] != ' ')
                textCollisionOccurred(text);
                
            globalScreen[x + i][y] = text->text[i];
        }
        i++;
    }

}

/* 
 * Clears screen and gets all vectors from the
 * global data structure and calls the appropriate
 * draw function on each.
 * Calls draw function on each call and updates
 */
void draw()
{
    clearCollisions();

    int i,j;
    for(i = 0;i < SSIZEX;i++)
    {
        for(j = 0;j < SSIZEY;j++)
            globalScreen[i][j] = ' ';
    }

    for(i = 0;i < vectorData->numLines;i++)
        drawLineToGlobalScreen(vectorData->lines[i]);
/*
    for(i = 0;i < vectorData->numCircles;i++)
        //draw circles;

    for(i = 0;i < vectorData->numRectangles;i++)
        //draw rectangles;

*/
    for(i = 0;i < vectorData->numTexts;i++)
        drawTextToGlobalScreen(vectorData->texts[i]);

    drawLocalScreen();
}
