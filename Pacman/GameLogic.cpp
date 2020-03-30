#include "GameLogic.h"
#include "Constants.h"
#include <allegro5/allegro.h>
#include <math.h>
#include <cmath>

#define xLim1

//Returns true if the new position solicited is a valid one.
bool GameLogic::canMove(Position nextPosition)
{
    if (!((nextPosition.x > 32 && nextPosition.x < 293) && (nextPosition.y > 32 && nextPosition.y < 118) || (nextPosition.x > 217 && nextPosition.x < 398) && (nextPosition.y > 162 && nextPosition.y < 298) || (nextPosition.x > 310 && nextPosition.x < 568) && (nextPosition.y > 32 && nextPosition.y < 118) || (nextPosition.x > 32 && nextPosition.x < 198) && (nextPosition.y > 162 && nextPosition.y < 298) || (nextPosition.x > 412 && nextPosition.x < 568) && (nextPosition.y > 162 && nextPosition.y < 298) || (nextPosition.x > 310 && nextPosition.x < 568) && (nextPosition.y > 332 && nextPosition.y < 468) || (nextPosition.x > 32 && nextPosition.x < 293) && (nextPosition.y > 332 && nextPosition.y < 468)))
        return true;
    return false;
}

//If Pacman went over a fruit, it deletes it.
void GameLogic::eatCircle(std::vector <Position>& circlePositions_, Position currentPosition){
    for (int i= 0;i< circlePositions_.size(); i++)
    {
        if (circlePositions_[i].x < currentPosition.x + pacmanRadius && circlePositions_[i].x > currentPosition.x - pacmanRadius
        && circlePositions_[i].y < currentPosition.y + pacmanRadius && circlePositions_[i].y > currentPosition.y - pacmanRadius)
            
            circlePositions_.erase(circlePositions_.begin() + i);
    }
}
//If there are no more fruits, the game has been won.
bool GameLogic::checkGameStatus(vector <Position> circlePositions_)
{
    if (circlePositions_.size() != 0)
        return false;
    return true;
}

//Updates ghost position.
void GameLogic::updateGhostPosition(Position& ghostCurrentPosition) {
    static int step = 0;
    if (step == 0){
        if (ghostCurrentPosition.x > 25)
            ghostCurrentPosition.x -= ghostPase;
        else if (ghostCurrentPosition.y > 15)
            ghostCurrentPosition.y -= ghostPase;
        else
            step++;
    }
    else if (step == 1){
        if (ghostCurrentPosition.x < 580)
            ghostCurrentPosition.x = ghostCurrentPosition.x + ghostPase;
        else if (ghostCurrentPosition.y < 300)
            ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    else if (step == 2){
        if (ghostCurrentPosition.x > 226)
            ghostCurrentPosition.x = ghostCurrentPosition.x - ghostPase;
        else if (ghostCurrentPosition.y > 158)
            ghostCurrentPosition.y -= ghostPase;
        else
            step++;
    }
    else if (step == 3){
        if (ghostCurrentPosition.x< 300)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y > 20)
            ghostCurrentPosition.y = ghostCurrentPosition.y - ghostPase;
        else
            step++;
    }
    else if (step == 4){
        if (ghostCurrentPosition.x< 580)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y < 165)
            ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    else if (step == 5){
        if (ghostCurrentPosition.x > 20)
            ghostCurrentPosition.x -= ghostPase;
        else if (ghostCurrentPosition.y < 315)
            ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    else if (step == 6){
        if (ghostCurrentPosition.x< 580)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y < 480)
            ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    else if (step == 7){
        if (ghostCurrentPosition.x> 20)
            ghostCurrentPosition.x-= ghostPase;
        else if (ghostCurrentPosition.y > 315)
            ghostCurrentPosition.y -= ghostPase;
        else
            step++;
    }
    else if (step == 8){
        if (ghostCurrentPosition.x< 395)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y > 165)
            ghostCurrentPosition.y -= ghostPase;
        else
            step++;
    }
    else if (step == 9){
        if (ghostCurrentPosition.x> 220)
            ghostCurrentPosition.x-= ghostPase;    
        else if (ghostCurrentPosition.y < 315)
            ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    else if (step == 10){
        if (ghostCurrentPosition.x< 580)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y < 480)
            ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    if (step == 11){
        if (ghostCurrentPosition.x> 310)
            ghostCurrentPosition.x-= ghostPase;
        else if (ghostCurrentPosition.y > 315)
            ghostCurrentPosition.y -= ghostPase;
        else
            step++;
    }
    else if (step == 12){
        if (ghostCurrentPosition.x< 395)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y > 158)
            ghostCurrentPosition.y -= ghostPase;
        else
            step++;
    }
    else if (step == 13){
        if (ghostCurrentPosition.x> 216)
            ghostCurrentPosition.x-= ghostPase;
        else if (ghostCurrentPosition.y < 315)
                ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    else if (step == 14){
        if (ghostCurrentPosition.x> 20)
            ghostCurrentPosition.x-= ghostPase;
            
        else if (ghostCurrentPosition.y > 20)
            ghostCurrentPosition.y -= ghostPase;
        else
            step++;
    }
    else if (step == 15){
        if (ghostCurrentPosition.x< 295)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y < 158)
            ghostCurrentPosition.y += ghostPase;
        else
            step++;
    }
    else if (step == 16){
        if (ghostCurrentPosition.x< 580)
            ghostCurrentPosition.x+= ghostPase;
        else if (ghostCurrentPosition.y < 480)
            ghostCurrentPosition.y += ghostPase;
        else
            step = 0;
    }
}

bool GameLogic::checkIfLost(Position pacmanPosition, Position ghostPosition) {
    if (abs((int)(pacmanPosition.x - ghostPosition.x)) <= (pacmanRadius+ghostRadius) 
        && abs((int)(pacmanPosition.y - ghostPosition.y)) <= (pacmanRadius+ghostRadius))
        return true;

    return false;
}
