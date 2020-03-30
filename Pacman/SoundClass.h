#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
class SoundClass
{
public:
	//SoundClass constructor.
	SoundClass(ALLEGRO_SAMPLE* deathSound_ = NULL, ALLEGRO_SAMPLE* initialSound_ = NULL,
	std::string deathSoundName_ = "", std::string initialSoundName_ = "");

	bool createSounds(void);
	void setDeathSoundName(std::string Dsound);
	void setInitialSoundName(std::string Isound);
	std::string getDeathSoundName(void);
	std::string getInitialSoundName(void);

	ALLEGRO_SAMPLE* getInitialSound(void);
	ALLEGRO_SAMPLE* getDeathSound(void);

	void destroySounds(void);
	void playSoundOnce(ALLEGRO_SAMPLE* thisSample);
	void stopSound(ALLEGRO_SAMPLE_ID& thisSampleID);

	ALLEGRO_SAMPLE_ID deathSampleID;
	ALLEGRO_SAMPLE_ID initialSampleID;
	
private:
	std::string deathSoundName, initialSoundName;
	ALLEGRO_SAMPLE* deathSound, * initialSound;
	
};

