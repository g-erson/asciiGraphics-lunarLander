#include "vectorData.h"
#include "vectorAPI.h"


/* 
 * Revised collision mechanism
 * called from draw function if text
 * is drawn over something else
 * Finds closest line to text which has 
 * collided and adds that to line 
 * collision array
 */

void textCollisionOccurred(textVector* text)
{   int i;
    /*
     * Find out what it collided with 
     */
    collisionOccurred = 1;
    
    float lastDistance = 0;
    float distance = 0; 
    lineVector *closestLine;

    for(i = 0;i < vectorData->numLines;i++)
    {
        float deltax = fabsf(text->x - (vectorData->lines[i]->x1 +
                                        vectorData->lines[i]->x2)/2);
        float deltay = fabsf(text->y - (vectorData->lines[i]->y1 +
                                        vectorData->lines[i]->y2)/2);

        if(i == 0)
        {
            lastDistance = sqrtf(deltax * deltax + deltay * deltay);
            continue;
        }

        distance = sqrtf(deltax * deltax + deltay * deltay);

        if(distance < lastDistance)
        {
            lastDistance = distance;
            closestLine = vectorData->lines[i];
        }
    }
    for(i = 0;i < 10;i++)
    {
        if(lineCollisions[i] == NULL)
            lineCollisions[i] = closestLine;
    }
    for(i = 0;i < 10;i++)
    {
        if(textCollisions[i] == NULL)
            textCollisions[i] = text;
    }

}

/*
 * Clears previous collisions.
 * Will not handle more than 10 
 * collisions of each type
 */
void clearCollisions()
{ int i;

    for(i = 0;i < 10;i++)
    {
        lineCollisions[i] = NULL;
        rectCollisions[i] = NULL;
        circleCollisions[i] = NULL;
        textCollisions[i] = NULL;
    }
    collisionOccurred = 0;
}
