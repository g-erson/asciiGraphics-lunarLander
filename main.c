#include "vectorAPI.h"
#include "lunarLander.h"

#include <math.h>
#include <unistd.h>

int mainLoop();

lineVector *line1, *line2, *line3, *platform1, *platform2;
textVector *score, *fuel;

int main(int argc, char** argv)
{
    initVect(120,40);

    /*
     * Building level 
     */

    initLander();
    

    addLine(createLine(0,20,10,25));
    addLine(createLine(10,24,17,29));
    addLine(createLine(17,29,23,35));

    platform1 = addLine(createLine(22,35,32,35)); // <- first platform

    addLine(createLine(32,34,40,30));
    line1 = addLine(createLine(40,30,43,20));
    addLine(createLine(43,20,48,15));
    line3 = addLine(createLine(48,15,58,20));
    addLine(createLine(57,20,75,18));
    line2 = addLine(createLine(75,18,85,26));

    platform2 = addLine(createLine(84,26,94,26)); // <- second platform
    addLine(createLine(94,25,105,15));
    addLine(createLine(105,14,120,11));

    addText(createText("3X Score",24,36));
    addText(createText("2X Score",86,27));

    addText(createText("SCORE: ",1,1));
    addText(createText("FUEL: ",2,2));
    score = addText(createText("0",7,1));
    fuel = addText(createText("1000",7,2));

    mainLoop();

    return 0;
}

int mainLoop()
{   
    wchar_t ch = 0;
    int running = 1;
    int roundEnd = 0;

    int i = 0;
    while(running)
    {
        ch = getChar();
        if(ch == 27)
           break;

        /*
         * Rotates specified lines the
         * specified amount (in radians
         */
        rotateLine(line1,M_PI/1000);
        rotateLine(line2,M_PI/900);
        rotateLine(line3,-M_PI/900);

        /*
         * Firethruster handles input
         */
        fireThruster(ch);
        moveLander();

        /*
         * Time to sleep between frames
         */
        usleep(1000);

        if(roundEnd)
        {
            roundEnd = 0;
            clearPrintScreen();
            usleep(1000000);
            if(fuel < 0)
                running = 0;
        }

        /*
         * Convert fuel int to string 
         * and add to textVector
         */
        char fuelstr[7];
        sprintf(fuelstr,"%d",fuel_int);
        changeText(fuel,fuelstr);
        char scorestr[7];
        sprintf(scorestr,"%d",score_int);
        changeText(score,scorestr);

        draw();

        switch(detectWin(platform1,platform2))
        {
            case 0:
                break;
            case 1:
                printToScreen("Crashed!");
                draw();
                resetLander();
                roundEnd = 1;
                break;
            case 21:
                printToScreen("Landed too hard :( -100 fuel");
                score_int += 50;
                fuel_int -= 100;
                draw();
                resetLander();
                roundEnd = 1;
                break;
            case 22:
                printToScreen("Landed too hard :( -100 fuel");
                score_int += 75;
                fuel_int -= 100;
                draw();
                resetLander();
                roundEnd = 1;
                break;
            case 31:
                printToScreen("PERFECT LANDING!");
                score_int += 300;
                draw();
                resetLander();
                roundEnd = 1;
                break;
            case 32:
                printToScreen("PERFECT LANDING!");
                score_int += 200;
                draw();
                resetLander();
                roundEnd = 1;
                break;
            case 4:
                printToScreen("Out of fuel!");
                draw();
                resetLander();
                roundEnd = 1;
        }

    }
    exitVect();
    return 0;
}
