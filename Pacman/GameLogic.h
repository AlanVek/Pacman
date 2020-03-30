#pragma once
#include <iostream>
#include <vector>
#include "Constants.h"

class GameLogic
{
public:
	bool canMove(Position nextPosition);

	void eatCircle(std::vector <Position>& circlePositions_, Position currentPosition);

	bool checkGameStatus(std::vector<Position> circlePositions_);

	void updateGhostPosition(Position& ghostCurrentPosition);

	bool checkIfLost(Position pacmanPosition, Position ghostPosition);
};

