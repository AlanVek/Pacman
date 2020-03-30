#include <iostream>
#include "BackProcess.h"
#include "Constants.h"


int main()
{
    ALLEGRO_EVENT myKeyboardEvent;

    bool endOfInput = false;
    bool userExit = false;

    BackProcess g;

    //Sets sound file names for initial sound and death sound.
    g.getSoundControl().setDeathSoundName("pacman_death.wav");
    g.getSoundControl().setInitialSoundName("pacman_beginning.wav");

    //Sets font name.
    g.getGraphicControl().setFontName("BOSQUE.ttf");

    //Initializes display, events,timers, etc.
    if (!g.initialize_()) {
        cout << "Failed to initialize game\n";
        g.destroyAll();
        return -1;
    }

    //Sets game colors and shows main menu.
    g.getGraphicControl().setColors();
    g.getGraphicControl().printInitialMessage();

    al_flip_display();

    //Initial screen.
    while (!endOfInput)
    {
        //Checks for keyboard keys pressed.
        g.getEventControl().getNextKeyboardEvent();
        myKeyboardEvent = g.getEventControl().getEvent();
        if (myKeyboardEvent.type == ALLEGRO_EVENT_KEY_DOWN) {

            //If [ESC] or [2] were pressed, it exits the game.
            if (myKeyboardEvent.keyboard.keycode == ALLEGRO_KEY_2 ||
                myKeyboardEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                endOfInput = true;
                userExit = true;
            }

            //If [1] was pressed, it goes into the actual game.
            else if (myKeyboardEvent.keyboard.keycode == ALLEGRO_KEY_1) {
                userExit = false;
                endOfInput = true;
            }
        }
    }
    //Game graphic setup.
    if (!userExit) {

        //Sets initial configuration.
        g.initialConfiguration();
    }
    while (!userExit) {

       //If key was pressed...
        if (g.getEventControl().getNextKeyboardEvent() == ALLEGRO_EVENT_KEY_DOWN) {

            //Starts timer.
            if(g.startingFlag) {
                g.getTimeControl().startTimer();
                g.startingFlag = false;
            }

            /*Enters read/write loop. Returns true if either user pressed [ESC],
             all the fruits have been eaten or Pacman bumped into ghost.*/
            userExit = g.readWriteLoop();
        }


       //If game is unpaused...
       if (!g.gamePaused && !g.startingFlag) {
           /*If timer made a lap, ghostPosition gets updated and drawn.
           Then checks if the game has been lost. */
           if (g.getEventControl().getNextGeneralEvent() == ALLEGRO_EVENT_TIMER) {
               g.getLogicControl().updateGhostPosition(g.getCurrentGhostPosition());
               g.drawItAll();
               userExit = g.getLogicControl().checkIfLost(g.getCurrentPosition(), g.getCurrentGhostPosition());
               
               //If game's been lost...
               if (userExit) {
                   //Stops game music.
                   g.getSoundControl().stopSound(g.getSoundControl().initialSampleID);

                   //Plays death sound.
                   g.getSoundControl().playSoundOnce(g.getSoundControl().getDeathSound());

                   //Clears screen to red and waits before exiting.
                   g.getGraphicControl().gameLost();
               }
           }
       }
    
    }
    
    //Frees memory.
    g.destroyAll();
    return 0;
}