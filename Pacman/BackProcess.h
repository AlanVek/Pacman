#pragma once
#include "EventClass.h"
#include "SoundClass.h"
#include "TimeClass.h"
#include "EventClass.h"
#include "GraphicClass.h"
#include "GameLogic.h"


/* Nota: No se definió constructor copiador, ya que se utilizará el constructor
copiador por defecto. Lo mismo para destructor.*/

//Definiciones de parámetros por defecto.

#define defaultDisplay false
#define circleAmount 148

class BackProcess {
public:

	BackProcess();
	bool setSimulation(bool displayCreation = defaultDisplay);

	void destroyAll();

	bool setAllegro(void);

	Position& getCurrentPosition(void);
	Position& getCurrentGhostPosition(void);
	GraphicClass& getGraphicControl(void);
	TimeClass& getTimeControl(void);
	EventClass& getEventControl(void);
	SoundClass& getSoundControl(void);
	GameLogic& getLogicControl(void);
	vector<Position>& getCircleVector(void);
	bool readWriteLoop(void);
	void initialConfiguration(void);
	bool initialize_(void);

	void drawItAll(void);

	bool gamePaused;
	bool startingFlag;

private:

	//Datos miembro de BackProcess.
	GraphicClass graphicControl;
	TimeClass timeControl;
	SoundClass soundControl;
	EventClass eventControl;
	GameLogic logicControl;
	std::vector <Position> circlePositions;
	Position pacmanPosition;
	Position ghostPosition;
};