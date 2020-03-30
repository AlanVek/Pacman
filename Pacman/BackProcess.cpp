#include "BackProcess.h"
#include <allegro5\allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

int posit_x[] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,580,580,580,580,580,580,
580,580,580,580,580,580,580,580,580,580,580,580,580,580,300,300,300,300,300,300,300,300,300,300,300,300,20,
48,76,104,132,160,188,216,244,272,300,328,356,384,412,440,468,496,524,552,580,20,48,76,104,132,160,188,216,
244,272,300,328,356,384,412,440,468,496,524,552,580,20,48,76,104,132,160,188,216,244,272,300,328,356,384,
412,440,468,496,524,552,580,20,48,76,104,132,160,188,216,244,272,300,328,356,384,412,440,468,496,524,552,
580,216,216,216,216,216,216,412,412,412,412,412,412 };

int posit_y[] = { 20,43,66,89,112,135,158,181,204,227,250,273,296,319,342,365,388,411,434,457,
20,43,66,89,112,135,158,181,204,227,250,273,296,319,342,365,388,411,434,457,20,43,66,89,112,135,
342,365,388,411,434,457,480,480,480,480,480,480,480,480,480,480,480,480,480,480,480,480,480,480,
480,480,480,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,158,158,158,158,158,158,
158,158,158,158,158,158,158,158,158,158,158,158,158,158,158,319,319,319,319,319,319,319,319,319,319,
319,319,319,319,319,319,319,319,319,319,319,181,204,227,250,273,296,181,204,227,250,273,296 };


//BackProcess constructor.
BackProcess::BackProcess(void) {

	Position myPosition;

	for (int i = 0; i < circleAmount; i++) {
		myPosition.x = posit_x[i];
		myPosition.y = posit_y[i];
		circlePositions.push_back(myPosition);
	}

	//Sets initial Pacman position to its radius.
	pacmanPosition.x = pacmanRadius;
	pacmanPosition.y = pacmanRadius;

	//Sets initial ghost position to its radius.
	ghostPosition.x = defaultWidth - ghostRadius;
	ghostPosition.y = defaultHeight - ghostRadius;

	//Sets fag variables.
	gamePaused = false;
	startingFlag = true;
}

bool BackProcess::initialize_(void) {
	bool result = true;

	/*Allegro initialization error check*/
	if (!setAllegro()) {
		cout << "Failed to initialize Allegro.\n";
		result = false;
	}

	//Sets timer to  default FPS.
	timeControl.setTimer();

	/*Initialization of graphic resources. Checks for errors.
	True parameter indicates to create a new display. */
	if (!setSimulation(true)) {
		cout << "Failed to set simulation.\n";
		result = false;
	}

	return result;
}

//Initializes Allegro.
bool BackProcess::setAllegro(void) {
	if (!(al_init()
		&& al_install_keyboard()
		&& al_install_audio()
		&& al_init_primitives_addon()
		&& al_init_acodec_addon()
		&& al_init_font_addon()
		&& al_init_ttf_addon()))
		return false;
	
	return true;
}

/*Creates needed resources and checks for initialization errors.
If there's been one, returns false. If not, returns true. 
If parameter display is true, creates a new display.*/
bool BackProcess::setSimulation(bool displayCreation) {

	al_reserve_samples(2);

	//Creates resources.
	if (!(
		eventControl.createEventQueue()
		&& timeControl.createTimer()
		&& soundControl.createSounds()
		&& graphicControl.loadFont()))
		return false;

	//Creates display.
	if (displayCreation) {
		if (!graphicControl.createDisplay())
			return false;
	}

	//Sets event sources.
	al_register_event_source(eventControl.getKeyboardQueue(), al_get_keyboard_event_source());
	al_register_event_source(eventControl.getGeneralQueue(), al_get_timer_event_source(timeControl.getTimer()));
	
	graphicControl.clearToColor();

	return true;
}

//Frees memory.
void BackProcess::destroyAll() {
	soundControl.destroySounds();
	graphicControl.destroyGraphics();
	eventControl.destroyEventQueue();
	timeControl.destroyTimer();
}

//Class getters.
GraphicClass& BackProcess::getGraphicControl(void) { return graphicControl; }
TimeClass& BackProcess::getTimeControl(void) { return timeControl; }
EventClass& BackProcess::getEventControl(void) { return eventControl; }
SoundClass& BackProcess::getSoundControl(void) { return soundControl; }
GameLogic& BackProcess::getLogicControl(void) { return logicControl; }
vector<Position>& BackProcess::getCircleVector(void) { return circlePositions; }
Position& BackProcess::getCurrentPosition(void) { return pacmanPosition; }
Position& BackProcess::getCurrentGhostPosition(void) { return ghostPosition; }


//Calls GraphicClass::drawAll().
void BackProcess::drawItAll(void) {
	graphicControl.drawAll(pacmanPosition, ghostPosition, circlePositions);
}

/*Reads keyboard. If a key was pressed, it enters a drawing
loop until it is released. */
bool BackProcess::readWriteLoop(void){

	//Read next event.
	ALLEGRO_EVENT myKeyboardEvent, myTimerEvent;
	myKeyboardEvent = eventControl.getEvent();

	//While the key hasn't been released...
	while (myKeyboardEvent.type != ALLEGRO_EVENT_KEY_UP) {
		
		//If the timer has completed one lap...
		if (eventControl.getNextGeneralEvent() == ALLEGRO_EVENT_TIMER) {
			
			if (!gamePaused)
				//Updates ghost position.
				logicControl.updateGhostPosition(ghostPosition);

			//Does action depending on key pressed. If true, then [ESC] was pressed.
			if (eventControl.keyboardEvent(logicControl, pacmanPosition, myKeyboardEvent, circlePositions, gamePaused))
				return true;
			
			//If game is unpaused...
			if (!gamePaused){
						
				//Draws game with new parameters.					
				drawItAll();

				//Checks if game has ended (fruits eaten or ghost bumped into Pacman).
				if (logicControl.checkGameStatus(circlePositions)) {
					graphicControl.gameWon();
					startingFlag = true;
					return true;
				}
				//If Pacman bumped into ghost...
				if (logicControl.checkIfLost(pacmanPosition, ghostPosition)) {
					//Stops game music.
					soundControl.stopSound(soundControl.initialSampleID);

					//Plays death sound.
					soundControl.playSoundOnce(soundControl.getDeathSound());

					//Clears screen to red and waits before exiting.
					graphicControl.gameLost();
					startingFlag = true;
					return true;
				}
			}
		}
		//Updates keyboard status.
		myKeyboardEvent.type = eventControl.getNextKeyboardEvent();
	}
	return false;
}

void BackProcess::initialConfiguration(void) {
	//Clears screen to background color.
	graphicControl.clearToColor();

	/*Draws game layout, draws ghost, draws pacman,
	draws circles (fruits).*/
	drawItAll();

	//Shows drawings.
	al_flip_display();

	//Plays initial song.
	al_play_sample(soundControl.getInitialSound(), 1.0, 0, 1, ALLEGRO_PLAYMODE_LOOP, &soundControl.initialSampleID);
}