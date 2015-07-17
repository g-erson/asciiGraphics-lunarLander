#include "vectorAPI.h"
#include "vectorData.h"

/*
 * Move functions, these move the vector by the 
 * vector (x,y)
 */

void moveLine(lineVector* line, float x, float y)
{  
    line->lastx1 = line->x1;
    line->lasty1 = line->y1;
    line->lastx2 = line->x2;
    line->lasty2 = line->y2;
    line->x1 += x;
    line->x2 += x;
    line->y1 += y;
    line->y2 += y;
}

void moveRect(rectVector* rectangle, int_u x, int_u y)
{
    rectangle->x1 += x;
    rectangle->x2 += x;
    rectangle->y1 += y;
    rectangle->y2 += y;
}

void moveCircle(circleVector* circle, int_u x, int_u y)
{
    circle->x += x;
    circle->y += y;
}

void moveText(textVector* text, float x, float y)
{
    text->lastx = text->x;
    text->lasty = text->y;
    text->x += x;
    text->y += y;
}


/*
 * Rotate functions. 
 * TODO Lines get steadily shorter
 * probably due to truncation somewhere.
 */
void rotateLine(lineVector* line, float degrees)
{
    float cosx = cosf(degrees);
    float sinx = sinf(degrees);

    float midx = (line->x2 + line->x1)/2;
    float midy = (line->y2 + line->y1)/2;

    line->x1 =  ((line->x1 - midx) * cosx) - 
                ((line->y1 - midy) * sinx) + midx;
    line->y1 =  ((line->x1 - midx) * sinx) + 
                ((line->y1 - midy) * cosx) + midy;
    line->x2 =  ((line->x2 - midx) * cosx) - 
                ((line->y2 - midy) * sinx) + midx;
    line->y2 =  ((line->x2 - midx) * sinx) + 
                ((line->y2 - midy) * cosx) + midy;
}

void rotateRect(rectVector* rectangle, float degrees)
{
}

void rotateCircle(circleVector* circle, float degrees)
{
}

void rotateText(textVector* text, float degrees)
{
}

void changeText(textVector* text, char* newText)
{
    text->text = newText;
}
