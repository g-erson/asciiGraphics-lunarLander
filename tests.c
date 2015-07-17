#include "vectorAPI.h"
#include "vectorData.h"

/*
 * Take care with this function, as it does not do any bounds 
 * checking when accessing data
 */
void printVectorData()
{
    int i;
    for(i = 0;i < vectorData->numLines;i++)
    {
    printw("Lines: %f %f %f %f \n",
            vectorData->lines[i]->x1,vectorData->lines[i]->y1,
            vectorData->lines[i]->x2,vectorData->lines[i]->y2
            );
    }

    for(i = 0;i < vectorData->numCircles;i++)
    {
    printw("Circles: %d %d %d \n",
            vectorData->circles[i]->x,vectorData->circles[i]->y,
            vectorData->circles[i]->radius
            );
    }

}
