#pragma once
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "Constants.h"

#define defaultPaint false
class GraphicClass {
public:
	GraphicClass(unsigned int width = defaultWidth, unsigned int height = defaultHeight, ALLEGRO_DISPLAY* display_ = NULL);

	bool createDisplay(void);

	void setColors(void);
	void printInitialMessage(void);

	ALLEGRO_DISPLAY* getDisplay(void);

	void clearToColor(void);

	void drawGameLayout(void);
	void drawPacman(Position currentPosition);
	void drawCircles(vector <Position> circlePositions_);
	void drawGhost(Position ghostPosition);

	void destroyGraphics(void);
	void drawAll(Position currentPacmanPosition, Position currentGhostPosition, vector<Position> circlePositions);

	void setFontName(std::string fontName_);
	bool loadFont(void);

	void gameWon(void);
	void gameLost(void);

private:

	ALLEGRO_DISPLAY* display;
	ALLEGRO_COLOR backgroundColor, pacmanColor, ghostColor;
	ALLEGRO_COLOR eyeColor, mouthColor;
	ALLEGRO_FONT* font;
	ALLEGRO_COLOR fontColor,circleColor, ghostEyeColor,cageColor;
	unsigned int width;
	unsigned int height;
	std::string fontName;
};