#include "TimeClass.h"


//TimeClass constructor.
TimeClass::TimeClass(ALLEGRO_TIMER* timer_, double FPS_) : Timer(timer_), FPS(FPS_) {};

//Starts timer.
void TimeClass::startTimer(void) { al_start_timer(Timer);}

//Class setter.
void TimeClass::setTimer(double FPS_) { FPS = FPS_; }

//Class getter.
ALLEGRO_TIMER* TimeClass::getTimer(void) { return Timer; }

//Creates timer.
bool TimeClass::createTimer(void) {
	if ((Timer = al_create_timer(1 / FPS)))
		return true;
	return false;
}

//Frees memory.
void TimeClass::destroyTimer(void) { 
	if (Timer) 
		al_destroy_timer(Timer); 
}



