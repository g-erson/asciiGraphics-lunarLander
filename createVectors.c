#include "vectorAPI.h"
#include "vectorData.h"

/* 
 * Functions simply to create vectors
 */

lineVector* createLine(float x1, float y1, float x2, float y2)
{
    lineVector* line = (lineVector*) malloc(sizeof(lineVector));
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    return line;
}

circleVector* createCircle(int_u radius, int_u x, int_u y)
{
    circleVector* circle = (circleVector*) malloc(sizeof(circleVector));
    circle->radius = radius;
    circle->x = x;
    circle->y = y;
    return circle;
}

rectVector* createRectangle(int_u x1, int_u y1, int_u x2, int_u y2)
{
    rectVector* rectangle = (rectVector*) malloc(sizeof(rectVector));
    rectangle->x1 = x1;
    rectangle->y1 = y1;
    rectangle->x2 = x2;
    rectangle->y2 = y2;
    return rectangle;
}

textVector* createText(char* textChars, float x, float y)
{
    textVector* text = (textVector*) malloc(sizeof(textVector));
    text->x = x;
    text->y = y;
    text->text = textChars;
    return text;
}


/*
 * Adds each type of vector to data buffer
 *
 *
 * in realloc vectorData->lines is not allocated yet
 *
 */

lineVector* addLine(lineVector* line)
{
    if(vectorData->numLines >= vectorData->numLinesAlloc)
    {
        lineVector** moreLines = (lineVector**) realloc(vectorData->lines, 
                        (2 * vectorData->numLinesAlloc ) * sizeof(lineVector*));
        vectorData->lines = moreLines;
        vectorData->numLinesAlloc = 2*vectorData->numLinesAlloc;
    }
    vectorData->lines[vectorData->numLines] = line;
    vectorData->numLines++;

    return line;
}

circleVector* addCircle(circleVector* circle)
{
    if(vectorData->numCircles >= vectorData->numCirclesAlloc)
    {
        circleVector** moreCircles = (circleVector**) realloc(vectorData->circles, 
                        (2 * vectorData->numCirclesAlloc) * sizeof(circleVector*));
        vectorData->circles = moreCircles;
        vectorData->numCirclesAlloc = 2*vectorData->numCirclesAlloc;
    }
    vectorData->circles[vectorData->numCircles] = circle;
    vectorData->numCircles++;

    return circle;
}

rectVector* addRectangle(rectVector* rect)
{
    if(vectorData->numLines >= vectorData->numLinesAlloc)
    {
        rectVector** moreRectangles = (rectVector**) realloc(vectorData->rectangles, 
                        (2 * vectorData->numRectanglesAlloc) * sizeof(rectVector*));
        vectorData->rectangles = moreRectangles;
        vectorData->numRectanglesAlloc = 2*vectorData->numRectanglesAlloc;
    }
    vectorData->rectangles[vectorData->numRectangles] = rect;
    vectorData->numRectangles++;

    return rect;
}

textVector* addText(textVector* text)
{
    if(vectorData->numLines >= vectorData->numLinesAlloc)
    {
        textVector** moreTexts = (textVector**) realloc(vectorData->texts, 
                        (2 * vectorData->numTextsAlloc) * sizeof(textVector*));
        vectorData->texts = moreTexts;
        vectorData->numTextsAlloc = 2*vectorData->numTextsAlloc;
    }
    vectorData->texts[vectorData->numTexts] = text;
    vectorData->numTexts++;

    return text;
}
