#include "BackProcess.h"


EventClass::EventClass(ALLEGRO_EVENT_QUEUE* generalQueue_) : generalQueue(generalQueue_) {};

bool EventClass::createEventQueue(){

	generalQueue = al_create_event_queue();

	keyboardQueue = al_create_event_queue();

	if (!generalQueue || !keyboardQueue)
		return false;

	return true;
}

/*Distinguishes between keyboard events.
Returns true if ESC was pressed. Otherwise, returns false.*/
bool EventClass::keyboardEvent(GameLogic& logic, Position& currentPosition,ALLEGRO_EVENT Event_, vector <Position>& circlePositions,bool& gamePaused_) {

	bool isUserDone = false;
	Position nextPosition = currentPosition;
	bool move = false;

	//If game is paused, it doesn't check key pressed.
	if (gamePaused_) {
		if (Event_.keyboard.keycode != ALLEGRO_KEY_SPACE && Event_.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
			return isUserDone;
	}
	//Action depending on key pressed.
	switch (Event_.keyboard.keycode) {
	case ALLEGRO_KEY_DOWN:
		nextPosition.y += pacmanPace;
		move = true;
		break;
	case ALLEGRO_KEY_UP:
		nextPosition.y -= pacmanPace;
		move = true;
		break;
	case ALLEGRO_KEY_RIGHT:
		nextPosition.x += pacmanPace;
		move = true;
		break;
	case ALLEGRO_KEY_LEFT:
		nextPosition.x -= pacmanPace;
		move = true;
		break;
	case ALLEGRO_KEY_SPACE:
		gamePaused_ = !gamePaused_;
		break;
	case ALLEGRO_KEY_ESCAPE:
		isUserDone = true;
		break;
	default:
		break;
	}

	//If moving key was pressed...
	if (move) {

		//If movement is valid...
		if (logic.canMove(nextPosition,pacmanRadius)) {

			//Changes pacman position.
			currentPosition = nextPosition;

			/*Makes pacman appear out the othe end in case it went out of the screen. */
			logic.correctPosition(currentPosition, pacmanRadius);

			//Checks for eaten fruits.
			logic.eatCircle(circlePositions, currentPosition);
		}
	}

	return isUserDone;
}

//Class getters.
ALLEGRO_EVENT_QUEUE* EventClass::getGeneralQueue(void) { return generalQueue; }
ALLEGRO_EVENT_QUEUE* EventClass::getKeyboardQueue(void) { return keyboardQueue; }
ALLEGRO_EVENT EventClass::getEvent(void) { return thisEvent; }


//Gets next general event.
int EventClass::getNextGeneralEvent() {
	if (al_get_next_event(generalQueue, &thisEvent))
		return thisEvent.type;
	else
		return NULL;
}

//Gets next keyboard event.
int EventClass :: getNextKeyboardEvent() {
	if (al_get_next_event(keyboardQueue, &thisEvent))
		return thisEvent.type;
	else
		return NULL;
}

//Frees memory.
void EventClass::destroyEventQueue(void) {
	if (generalQueue) 
		al_destroy_event_queue(generalQueue);
	if (keyboardQueue)
		al_destroy_event_queue(keyboardQueue);
}

