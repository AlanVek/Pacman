#include "GraphicClass.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define FONTSIZE defaultWidth/20
#define WAIT_TIME 2
#define mouthThickness (defaultWidth/200)
#define eyeRadius (defaultWidth/300)
#define eyeDistanceX (defaultWidth/85)
#define eyeDistanceY eyeRadius
#define mouthDistanceX (defaultWidth/85)
#define mouthDistanceY (defaultWidth/120)
#define mouthLenght (defaultWidth/100)
#define ghostEyeXDistance (defaultWidth/150)
#define ghostEyeYDistance (defaultWidth/600)
#define ghostEyeRadius (defaultWidth/300)

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

    al_draw_rectangle(borderWidth, borderWidth, defaultWidth / 2 - borderWidth / 2, 
        secondRowStartY-borderWidth,cageColor,lineThickness);
   
    al_draw_rectangle(defaultWidth/2 + borderWidth/2, borderWidth, defaultWidth - borderWidth, 
        secondRowStartY-borderWidth, cageColor, lineThickness);
    
    al_draw_rectangle(borderWidth, secondRowStartY, secondRowStartX-borderWidth,
        thirdRowStartY-borderWidth, cageColor, lineThickness);
    
    al_draw_rectangle(secondRowStartX,secondRowStartY,thirdRowStartX-borderWidth,
        thirdRowStartY-borderWidth,cageColor, lineThickness);
    
    al_draw_rectangle(thirdRowStartX,secondRowStartY,defaultWidth-borderWidth, 
        thirdRowStartY-borderWidth, cageColor, lineThickness);
    
    al_draw_rectangle(borderWidth, thirdRowStartY, defaultWidth - borderWidth, 
        defaultHeight - borderWidth,cageColor,lineThickness);
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
    drawCircles(circlePositions);
    drawPacman(currentPacmanPosition);
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