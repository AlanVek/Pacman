#include "SoundClass.h"

//SoundClass constructor.
SoundClass::SoundClass(ALLEGRO_SAMPLE* deathSound_, ALLEGRO_SAMPLE* initialSound_,
	std::string deathSoundName_, std::string initialSoundName_):

	deathSound(deathSound_),
	initialSound(initialSound_),
	initialSoundName(initialSoundName_),
	deathSoundName(deathSoundName_)
{};

//Class setters.
void SoundClass::setDeathSoundName(std::string Dsound) { deathSoundName = Dsound; }
void SoundClass::setInitialSoundName(std::string Isound) { initialSoundName = Isound; }

//Class getters.
std::string SoundClass::getDeathSoundName(void) { return deathSoundName; }
std::string SoundClass::getInitialSoundName(void) { return initialSoundName; }
ALLEGRO_SAMPLE* SoundClass::getInitialSound(void) { return initialSound; }
ALLEGRO_SAMPLE* SoundClass::getDeathSound(void) { return deathSound; }

//Creates sound samples. Returns false if unsuccessful.
bool SoundClass::createSounds(void) {
	bool resultado = false;
	char* validDeathSoundName = new (std::nothrow) char[deathSoundName.length() + 1];
	char* validInitialSoundName = new (std::nothrow) char[initialSoundName.length() + 1];

	strcpy(validDeathSoundName, deathSoundName.c_str());
	strcpy(validInitialSoundName, initialSoundName.c_str());

	if ((deathSound = al_load_sample(validDeathSoundName)) && (initialSound = al_load_sample(validInitialSoundName)))
		resultado = true;

	delete[] validDeathSoundName;
	delete[] validInitialSoundName;

	return resultado;
}

//Frees memory.
void SoundClass::destroySounds(void) {
	if (initialSound)
		al_destroy_sample(initialSound);
	if (deathSound)
		al_destroy_sample(deathSound);
}

//Plays sample once.
void SoundClass::playSoundOnce(ALLEGRO_SAMPLE* thisSample) {
	al_play_sample(thisSample,1.0,0,1,ALLEGRO_PLAYMODE_ONCE,0);
}

//Stops sample.
void SoundClass::stopSound(ALLEGRO_SAMPLE_ID& thisSampleID) {
	al_stop_sample(&thisSampleID);
}
