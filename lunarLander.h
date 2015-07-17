#ifndef _LANDER_H_
    #define _LANDER_H_

#include "vectorAPI.h"

#define MAXSPEED 0.02
#define GRAVITY 0.0000000005

int score_int;
int fuel_int;

int landed;

int timePassed;
float ySpeed;
float xSpeed;
float direction;
float xAcceleration;
float yAcceleration;

textVector *lander;

void initLander();
int detectWin(lineVector* platform1,lineVector *platform2);
void moveLander();
void fireThruster(char c);
void resetLander();

#endif
