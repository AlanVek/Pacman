#include "GameLogic.h"
#include "Constants.h"
#include <allegro5/allegro.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <algorithm>


//Returns true if the new position solicited is a valid one.
bool GameLogic::canMove(Position nextPosition, int radius)
{
    if (nextPosition.y > borderWidth - radius && nextPosition.y < secondRowStartY -
        borderWidth + radius) {

        if (
            (nextPosition.x > borderWidth - radius && nextPosition.x < defaultWidth / 2 -
                borderWidth / 2 + radius)

            ||

            ((nextPosition.x > defaultWidth / 2 + borderWidth / 2 - radius &&
                nextPosition.x < defaultWidth - borderWidth + radius))
            )
            return false;
    }
    if (nextPosition.y > secondRowStartY - radius &&
        nextPosition.y < thirdRowStartY - borderWidth + radius) {

        if (
            (nextPosition.x > borderWidth - radius &&
                nextPosition.x < secondRowStartX - borderWidth + radius)

            ||

            (nextPosition.x > secondRowStartX - radius &&
                nextPosition.x < thirdRowStartX - borderWidth + radius)

            ||

            (nextPosition.x > thirdRowStartX - radius &&
                nextPosition.x < defaultWidth - borderWidth + radius))

            return false;
    }

    if (nextPosition.y > thirdRowStartY - radius &&
        nextPosition.y < defaultHeight - borderWidth + radius) {

        if (nextPosition.x > borderWidth - radius &&
            nextPosition.x < defaultWidth - borderWidth + radius)
            return false;


        return true;
    }
}

//If Pacman went over a fruit, it deletes it.
void GameLogic::eatCircle(std::vector <Position>& circlePositions_, Position currentPosition) {
    for (int i = 0; i < circlePositions_.size(); i++)
    {
        if (circlePositions_[i].x < currentPosition.x + pacmanRadius && circlePositions_[i].x > currentPosition.x - pacmanRadius
            && circlePositions_[i].y < currentPosition.y + pacmanRadius && circlePositions_[i].y > currentPosition.y - pacmanRadius)

            circlePositions_.erase(circlePositions_.begin() + i);
    }
}

//If there are no more fruits, the game has been won.
bool GameLogic::checkGameStatus(vector <Position> circlePositions_) {
    if (circlePositions_.size() != 0)
        return false;
    return true;
}

//Updates ghost position.
void GameLogic::updateGhostPosition(Position& ghostCurrentPosition, Position pacmanCurrentPosition) {
    static int step = 0;

    switch (step) {

    case 0:
        if (ghostCurrentPosition.x > borderWidth / 2)
            ghostCurrentPosition.x -= ghostPace;

        else if (ghostCurrentPosition.y > borderWidth / 2)
            ghostCurrentPosition.y -= ghostPace;
        else
            step++;
        break;

    case 1:
        if (ghostCurrentPosition.x < defaultWidth - borderWidth / 2)
            ghostCurrentPosition.x = ghostCurrentPosition.x + ghostPace;
        else if (ghostCurrentPosition.y < thirdRowStartY - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 2:
        if (ghostCurrentPosition.x > secondRowStartX - borderWidth / 2)
            ghostCurrentPosition.x = ghostCurrentPosition.x - ghostPace;
        else if (ghostCurrentPosition.y > secondRowStartY - borderWidth / 2)
            ghostCurrentPosition.y -= ghostPace;
        else
            step++;
        break;

    case 3:
        if (ghostCurrentPosition.x < defaultWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y > borderWidth / 2)
            ghostCurrentPosition.y = ghostCurrentPosition.y - ghostPace;
        else
            step++;
        break;

    case 4:
        if (ghostCurrentPosition.x < defaultWidth - borderWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y < secondRowStartY - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 5:
        if (ghostCurrentPosition.x > borderWidth / 2)
            ghostCurrentPosition.x -= ghostPace;
        else if (ghostCurrentPosition.y < thirdRowStartY - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 6:
        if (ghostCurrentPosition.x < defaultWidth - borderWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y < defaultHeight - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 7:
        if (ghostCurrentPosition.x > borderWidth / 2)
            ghostCurrentPosition.x -= ghostPace;
        else if (ghostCurrentPosition.y > thirdRowStartY - borderWidth / 2)
            ghostCurrentPosition.y -= ghostPace;
        else
            step++;
        break;

    case 8:
        if (ghostCurrentPosition.x < thirdRowStartX - borderWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y > secondRowStartY - borderWidth / 2)
            ghostCurrentPosition.y -= ghostPace;
        else
            step++;
        break;

    case 9:
        if (ghostCurrentPosition.x > secondRowStartX - borderWidth / 2)
            ghostCurrentPosition.x -= ghostPace;
        else if (ghostCurrentPosition.y < thirdRowStartY - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 10:
        if (ghostCurrentPosition.x < defaultWidth - borderWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y < defaultHeight - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 11:
        if (ghostCurrentPosition.x > thirdRowStartX - borderWidth / 2)
            ghostCurrentPosition.x -= ghostPace;
        else if (ghostCurrentPosition.y > thirdRowStartY - borderWidth / 2)
            ghostCurrentPosition.y -= ghostPace;
        else
            step++;
        break;

    case 12:
        if (ghostCurrentPosition.x < thirdRowStartX - borderWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y > secondRowStartY - borderWidth / 2)
            ghostCurrentPosition.y -= ghostPace;
        else
            step++;
        break;

    case 13:
        if (ghostCurrentPosition.x > secondRowStartX - borderWidth / 2)
            ghostCurrentPosition.x -= ghostPace;
        else if (ghostCurrentPosition.y < thirdRowStartY - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 14:
        if (ghostCurrentPosition.x > borderWidth / 2)
            ghostCurrentPosition.x -= ghostPace;

        else if (ghostCurrentPosition.y > borderWidth / 2)
            ghostCurrentPosition.y -= ghostPace;
        else
            step++;
        break;

    case 15:
        if (ghostCurrentPosition.x < defaultWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y < secondRowStartY - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step++;
        break;

    case 16:
        if (ghostCurrentPosition.x < defaultWidth - borderWidth / 2)
            ghostCurrentPosition.x += ghostPace;
        else if (ghostCurrentPosition.y < defaultHeight - borderWidth / 2)
            ghostCurrentPosition.y += ghostPace;
        else
            step = 0;
        break;
    }
}
    


bool GameLogic::checkIfLost(Position pacmanPosition, Position ghostPosition) {
    if (abs((int)(pacmanPosition.x - ghostPosition.x)) <= (pacmanRadius + ghostRadius)
        && abs((int)(pacmanPosition.y - ghostPosition.y)) <= (pacmanRadius + ghostRadius))
        return true;

    return false;
}

void GameLogic::correctPosition(Position& currentPosition, int radius) {

    if (currentPosition.x >= (defaultWidth + radius))
        currentPosition.x -= defaultWidth;
    else if (currentPosition.x < radius)
        currentPosition.x += defaultWidth;
    if (currentPosition.y < radius)
        currentPosition.y += defaultHeight;
    else if (currentPosition.y >= (defaultHeight + radius))
        currentPosition.y -= defaultHeight;
}