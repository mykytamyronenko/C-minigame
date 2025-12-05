#include "StateManager.h"

StateManager::StateManager(sf::RenderWindow& app):app(app)
{
    //currentState = nullptr;
}

StateManager::~StateManager()
{
    //dtor
}
void StateManager::setState(State* newState)
{
    currentState = newState;
}

void StateManager::update()
{
    currentState->update();
}

State* StateManager::getCurrentState()
{
    return currentState;
}

void StateManager::setStateRoom1()
{
    StateRoom1 = this->getCurrentState();
}

void StateManager::setStateRoom2()
{
    StateRoom2 = this->getCurrentState();
}

void StateManager::setStateRoom3()
{
    StateRoom3 = this->getCurrentState();
}

void StateManager::setStateRoom4()
{
    StateRoom4 = this->getCurrentState();
}

void StateManager::setStateRoom5()
{
    StateRoom5 = this->getCurrentState();
}

void StateManager::setStateRoom6()
{
    StateRoom6 = this->getCurrentState();
}

void StateManager::setStateRoom7()
{
    StateRoom7 = this->getCurrentState();
}

State* StateManager::getStateRoom1()
{
    return StateRoom1;
}
State* StateManager::getStateRoom2()
{
    return StateRoom2;
}

State* StateManager::getStateRoom3()
{
    return StateRoom3;
}

State* StateManager::getStateRoom4()
{
    return StateRoom4;
}

State* StateManager::getStateRoom5()
{
    return StateRoom5;
}

State* StateManager::getStateRoom6()
{
    return StateRoom6;
}

State* StateManager::getStateRoom7()
{
    return StateRoom7;
}

void StateManager::render()
{
    app.clear();
    if (currentState) {
        currentState->render();
    }
    app.display();
}

void StateManager::handleInput()
{
    sf::Event event;
    while (app.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            app.close();
        }
    }

    if (currentState) {
        currentState->handleInput();
    }
}
