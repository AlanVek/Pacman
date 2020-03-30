#pragma once
#include <allegro5/allegro.h>
#include "GraphicClass.h"
#include "GameLogic.h"

class EventClass {
public:
	EventClass(ALLEGRO_EVENT_QUEUE* generalQueue_ = NULL);
	bool createEventQueue(void);
	bool keyboardEvent(GameLogic& logic, Position& currentPosition, ALLEGRO_EVENT Event_, vector <Position>& circlePositions,bool& gamePaused_);

	int getNextGeneralEvent();
	ALLEGRO_EVENT_QUEUE* getGeneralQueue(void);
	ALLEGRO_EVENT_QUEUE* getKeyboardQueue(void);
	void destroyEventQueue(void);
	int getNextKeyboardEvent(void);
	ALLEGRO_EVENT getEvent();
private:
	ALLEGRO_EVENT thisEvent;
	ALLEGRO_EVENT_QUEUE* generalQueue;
	ALLEGRO_EVENT_QUEUE* keyboardQueue;
};