#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "State.h"
#include <SFML/Graphics.hpp>


class StateManager
{
    private:
        State* currentState;
        State* StateRoom1;
        State* StateRoom2;
        State* StateRoom3;
        State* StateRoom4;
        State* StateRoom5;
        State* StateRoom6;
        State* StateRoom7;

        sf::RenderWindow& app;



    public:
        StateManager(sf::RenderWindow& app);
        virtual ~StateManager();
        State* getCurrentState();
        void setState(State* newState);

        void setStateRoom1();
        void setStateRoom2();
        void setStateRoom3();
        void setStateRoom4();
        void setStateRoom5();
        void setStateRoom6();
        void setStateRoom7();

        State* getStateRoom1();
        State* getStateRoom2();
        State* getStateRoom3();
        State* getStateRoom4();
        State* getStateRoom5();
        State* getStateRoom6();
        State* getStateRoom7();

        void update();
        void render();
        void handleInput();

};

#endif // STATEMANAGER_H

