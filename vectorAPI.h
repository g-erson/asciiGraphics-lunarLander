#ifndef _VECTORAPI_H_
	#define _VECTORAPI_H_

#include <wchar.h>

/*
 * Vector data type definitions
 */

typedef unsigned int int_u;

typedef struct {
    float x1,y1;
    float x2,y2;
    float lastx1, lasty1;
    float lastx2, lasty2;
}lineVector;

typedef struct {
    int_u radius;
    int_u x, y; 
}circleVector;

typedef struct {
    int_u x1, y1;
    int_u x2, y2;
}rectVector;

typedef struct {
    char* text;	
    float x, y;
    float lastx, lasty;
}textVector;

typedef enum {
    LINE,
    CIRCLE,
    RECTANGLE,
    TEXT
}vectorType;

/*
 * Global arrays of collided objects
 */

lineVector *lineCollisions[10];
rectVector *rectCollisions[10];
circleVector *circleCollisions[10];
textVector *textCollisions[10];
int collisionOccurred;

/*
 * Initialise and exit engine
 */

void initVect();
void exitVect();
/*
 * Set of functions to create  & add vectors to vector 
 * buffer. All these functions use global coordinates to place
 * vector objects.
 */

lineVector* createLine(float x1, float y1, float x2, float y2);
circleVector* createCircle(int_u radius, int_u x, int_u y);
rectVector* createRectangle(int_u x1, int_u y1, int_u x2, int_u y2);
textVector* createText(char* textChars, float x, float y);

lineVector* addLine(lineVector* line);
circleVector* addCircle(circleVector* circle);
rectVector* addRectangle(rectVector* rectangle);
textVector* addText(textVector* text);

/*
 * Functions to move vectors after they have been added to global
 * coordinate space. Each takes coordinate vector to move to, 
 * initial coordinates are the current position of the vector
 * object.
 */

void moveLine(lineVector* line, float x, float y);
void moveRect(rectVector* rectangle, int_u x, int_u y);
void moveCircle(circleVector* circle, int_u x, int_u y);
void moveText(textVector* text, float x, float y);

void rotateLine(lineVector* line, float degrees);
void rotateRect(rectVector* rectangle, float degrees);
void rotateCircle(circleVector* circle, float degrees);
void rotateText(textVector* text, float degrees);

void changeText(textVector* text, char* newText);

/* 
 * Collision detection; sets pointers to objects which
 * have collided in global array of collided vector
 * objects.
 */

void lineCollisionOccurred(lineVector *line);
void rectCollisionOccurred(rectVector *rect);
void circleCollisionOccurred(circleVector *circle);
void textCollisionOccurred(textVector *text);
void clearCollisions();

/*
 * Controlling local screen movement
 */

void changeLocalScreenSize(int_u x1, int_u y1, int_u x2, int_u y2);
void moveLocalScreen(int_u x, int_u y);

/*
 * Draw functions
 */

void draw();
void clearScreen();
void printToScreen();
void clearPrintScreen();

/*
 * Get Input
 */
wchar_t getChar();

/*
 * Testing functions
 *
 */

void printVectorData();


#endif
