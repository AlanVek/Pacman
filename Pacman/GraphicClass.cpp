#include "GraphicClass.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define FONTSIZE 30
#define WAIT_TIME 2

//GraphicClass constructor.
GraphicClass::GraphicClass(unsigned int width_, unsigned int height_, ALLEGRO_DISPLAY* display_) :
	height(height_),
	width(width_),
	display(display_)
{};

//Attempts to create display. Returns true if successful. 
bool GraphicClass::createDisplay(void) {
	display = al_create_display(width,height);
	if (!display)
		return false;
	return true;
}

//Clears display to background color.
void GraphicClass::clearToColor(void) {
	al_clear_to_color(backgroundColor);
}

//Shows initial message.
void GraphicClass::printInitialMessage() {
	
	al_draw_text(font, fontColor, width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "PACMAN");

	al_draw_text(font, fontColor, width / 2, height / 2 + FONTSIZE*2, ALLEGRO_ALIGN_CENTER, "1.- INICIAR");

	al_draw_text(font, fontColor, width / 2, height / 2 + FONTSIZE*3, ALLEGRO_ALIGN_CENTER, "2.- SALIR");
}

//Draws game layout.
void GraphicClass::drawGameLayout()
{
    al_draw_rectangle(50, 50, 275, 100, cageColor, lineThickness);
    al_draw_rectangle(235, 180, 380, 280, cageColor, lineThickness);
    al_draw_rectangle(330, 50, 550, 100, cageColor, lineThickness);
    al_draw_rectangle(50, 180, 180, 280, cageColor, lineThickness);
    al_draw_rectangle(430, 180, 550, 280, cageColor, lineThickness);
    al_draw_rectangle(330, 350, 550, 450, cageColor, lineThickness);
    al_draw_rectangle(50, 350, 275, 450, cageColor, lineThickness);
}

//Draws Pacman.
void GraphicClass::drawPacman(Position currentPosition){
    al_draw_filled_circle(currentPosition.x, currentPosition.y, pacmanRadius,pacmanColor);
    al_draw_filled_circle(currentPosition.x + eyeDistanceX, currentPosition.y - eyeDistanceY, eyeRadius, eyeColor);
    al_draw_rectangle(currentPosition.x + mouthDistanceX, currentPosition.y + mouthDistanceY, currentPosition.x + mouthDistanceX + mouthLenght, currentPosition.y + mouthDistanceY, mouthColor,mouthThickness);
}

//Draws fruits.
void GraphicClass::drawCircles(vector <Position> circlePositions_){
    for (int i = 0; i < circlePositions_.size(); i++)
        al_draw_filled_circle(circlePositions_[i].x, circlePositions_[i].y, circleRadius, circleColor);
}

//Draws ghost.
void GraphicClass::drawGhost(Position ghostPosition) {

    al_draw_filled_circle(ghostPosition.x, ghostPosition.y, ghostRadius, ghostColor);
    al_draw_filled_circle(ghostPosition.x + ghostEyeXDistance, ghostPosition.y - ghostEyeYDistance, ghostEyeRadius,ghostEyeColor);
    al_draw_filled_circle(ghostPosition.x - ghostEyeXDistance, ghostPosition.y - ghostEyeYDistance, ghostEyeRadius,ghostEyeColor);
    //al_draw_rectangleline(a - 3, b + 5, a + 3, b + 5, makecol(0, 0, 0));
}

/*Class setters*/

//Sets different colors.
void GraphicClass::setColors(void) {
    circleColor = al_map_rgb(255, 255, 255);
    pacmanColor = al_map_rgb(255, 255, 0);
    fontColor = al_map_rgb(255,255,255);
    eyeColor = al_map_rgb(0, 0, 0);
    mouthColor = al_map_rgb(255, 0, 0);
    ghostColor = al_map_rgb(255, 0, 0);
    ghostEyeColor = al_map_rgb(255, 255, 255);
    cageColor = al_map_rgb(0, 0, 255);
}


//Sets font name.
void GraphicClass::setFontName(std::string fontName_) { fontName = fontName_; }

/*End of Class setters.*/

//Frees memory.
void GraphicClass::destroyGraphics(void) {
    if (font)
        al_destroy_font(font);
    if (display)
        al_destroy_display(display);
}

//Loads font for messages. Returns false if unsuccessful.
bool GraphicClass::loadFont(void) {
    bool resultado = false;
    
    char* validFontName = new (std::nothrow) char[fontName.length() + 1];

    strcpy(validFontName, fontName.c_str());

    if ((font = al_load_ttf_font(validFontName,FONTSIZE,0)))
        resultado = true;
    
    delete []validFontName;
    return resultado;
}

//Class getters.
ALLEGRO_DISPLAY* GraphicClass::getDisplay(void) { return display; }

//Calls all the draw methods.
void GraphicClass::drawAll(Position currentPacmanPosition, Position currentGhostPosition, vector<Position> circlePositions) {
    al_clear_to_color(backgroundColor);
    drawPacman(currentPacmanPosition);
    drawCircles(circlePositions);
    drawGameLayout();
    drawGhost(currentGhostPosition);
    al_flip_display();
}

//Lost-game graphics.
void GraphicClass::gameLost() {
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_flip_display();
    al_rest(WAIT_TIME);
}

//Won-game graphics.
void GraphicClass::gameWon() {
    al_clear_to_color(al_map_rgb(0, 255, 0));
    al_flip_display();
    al_rest(WAIT_TIME);
}