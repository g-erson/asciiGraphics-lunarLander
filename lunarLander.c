#include "lunarLander.h"

/*
 * Initialisation
 */
void initLander()
{
    lander = addText(createText("A",90,24));
    xSpeed = 0;
    ySpeed = 0.001;
    timePassed = 0;
    landed = 0;
    fuel_int = 1000;
    score_int = 0;
}

/*
 * Detectwin tests whether the lander has collided with
 * anything and if the thing it has collided with is a 
 * valid landing pad. Also considers the speed of impact
 */
int detectWin(lineVector *platform1, lineVector *platform2)
{   int i;
    if(collisionOccurred)
    {
        for(i = 0; i < 10;i++)
        {
            if( textCollisions[i] == lander)
            {
                landed = 1;
                if( (lineCollisions[i] == platform1) ||
                    (lineCollisions[i] == platform2))
                {
                    if(ySpeed < 0.005)
                    {
                        if(lineCollisions[i] == platform1)
                            return 31;
                        if(lineCollisions[i] == platform2)
                            return 32;
                    }
                        //perfect landing
                    else
                    {
                        if(lineCollisions[i] == platform1)
                            return 21;
                        if(lineCollisions[i] == platform2)
                            return 22;
                    }
                        //landed too hard
                }
                else
                    return 1;
                //crashed
            }
        }
    }
    if(fuel_int < 0)
        return 4;
    return 0;
    //no collision
}

/*
 * Resets lander to the starting position 
 */
void resetLander()
{
    lander->x = 50;
    lander->y = 4;
    xSpeed = 0;
    ySpeed = 0;
    timePassed = 0;
    landed = 0;
}

/* 
 * Moves lander according to gravity and current
 * thrusters
 */
void moveLander()
{
    timePassed++;
    if(landed == 0)
    {
        ySpeed = ySpeed + timePassed * GRAVITY;
        if(ySpeed > MAXSPEED)
            ySpeed = MAXSPEED;
        
        moveText(lander,xSpeed,ySpeed);
    }
}

/*
 * Controls which thrusters are fired from a
 * given input, and decreases fuel
 */
void fireThruster(char c)
{
    if(fuel_int > 0)
    {
        switch(c)
        {
            case 'a':
                xSpeed += -0.0005;
                fuel_int -= 5;
                break;
            case 'd':
                xSpeed += 0.0005;
                fuel_int -= 5;
                break;
            case 'w':
                ySpeed -= 0.0005;
                fuel_int -= 5;
                break;
        }
    }
}
