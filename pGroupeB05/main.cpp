#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "StateManager.h"
#include "Room1.h"
#include "Room3.h"
#include "Room4.h"
#include "Room5.h"
#include "Room6.h"
#include "Room7.h"
#include "Enemy.h"
#include "Player.h"
#include "Animation.h"

int main() {
    sf::RenderWindow app(sf::VideoMode(1920, 1080), "SFML window",sf::Style::Fullscreen);
    app.setFramerateLimit(60);

    bool inMainMenu = true;
    bool inPlayingState = false;
    bool inResetState = false;
    bool inGameOver = false;
    bool inWinState = false;

    sf::Texture playerTexture_;
    playerTexture_.loadFromFile("Images/zeldaAnimation.png");

    sf::RectangleShape playButton(sf::Vector2f(80, 50));
    playButton.setFillColor(sf::Color::Blue);
    playButton.setPosition((1920/2)-40, 540);

    sf::RectangleShape resetButton(sf::Vector2f(80, 50));
    resetButton.setFillColor(sf::Color::Green);
    resetButton.setPosition((1920/2)-40, 540);

    sf::RectangleShape continueButton(sf::Vector2f(200, 50));
    continueButton.setFillColor(sf::Color::Green);
    continueButton.setPosition((1920/2)-40, 300);

     // Créez l'instance de StateManager en passant app
    StateManager stateManager(app);
    Player p1(sf::Color::Green,100,true,10, &playerTexture_, sf::Vector2u(10,4),0.3f,7.0f);
    Room2 r2(app,stateManager,p1);
    Room1 r1(app,stateManager,p1);
    Room3 r3(app,stateManager,p1);
    Room4 r4(app,stateManager,p1);
    Room5 r5(app,stateManager,p1);
    Room6 r6(app,stateManager,p1);
    Room7 r7(app,stateManager,p1);

    stateManager.setState(&r1);
    stateManager.setStateRoom1();
    stateManager.setState(&r2);
    stateManager.setStateRoom2();
    stateManager.setState(&r3);
    stateManager.setStateRoom3();
    stateManager.setState(&r4);
    stateManager.setStateRoom4();
    stateManager.setState(&r5);
    stateManager.setStateRoom5();
    stateManager.setState(&r6);
    stateManager.setStateRoom6();
    stateManager.setState(&r7);
    stateManager.setStateRoom7();
    stateManager.setState(&r1);

    float deltaTime = 0.0f;
    sf::Clock clock;

    //musique
    /*sf::Music music;
    music.openFromFile("Audio/testos.ogg");
    music.setLoop(true);*/

    app.clear(sf::Color::Cyan);

    sf::Font font;
    if (!font.loadFromFile("font/Arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text playButtonText("Play", font, 40);
    playButtonText.setPosition((1920/2)-40, 540);

    sf::Text quitText("Quit", font, 40);
    quitText.setPosition((1920/2)-40, 540);

    sf::Text continueText("Continue ?",font,40);
    continueText.setPosition((1920/2)-40, 300);

    sf::Text winText("GG ?",font,40);
    winText.setPosition((1920/2)-40, 300);

    sf::Text gameOverText("Game Over",font,40);
    gameOverText.setPosition((1920/2)-40, 450);

     while (app.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                app.close();

            if (inMainMenu && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(app);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (playButton.getGlobalBounds().contains(mousePosF)) {
                    inMainMenu = false;
                    inPlayingState = true;
                   // music.play();
                }
            }

            if (inResetState && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(app);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (resetButton.getGlobalBounds().contains(mousePosF)) {
                    app.close();
                }
                if (continueButton.getGlobalBounds().contains(mousePosF)) {
                    inResetState = false;
                    inPlayingState = true;
                }
            }

            if (inGameOver && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(app);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (resetButton.getGlobalBounds().contains(mousePosF)) {
                    app.close();
                }
            }

            if (inWinState && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(app);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (resetButton.getGlobalBounds().contains(mousePosF)) {
                    app.close();
                }
            }
        }
        p1.animationUpdate(deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (inPlayingState) {
                inResetState = true;
                inPlayingState = false;
            }
        }

        if(r7.getNumDeadBoss() == 9)
        {
            inWinState = true;
            inPlayingState = false;
            inResetState = false;
            inGameOver = false;
            inMainMenu = false;
        }

        app.clear(sf::Color(128, 128, 128));

        if (inResetState) {
            app.draw(resetButton);
            app.draw(quitText);
            app.draw(continueButton);
            app.draw(continueText);
            app.display();
        }

        if(inGameOver)
        {
            app.draw(gameOverText);
            app.draw(resetButton);
            app.draw(quitText);
            app.display();
        }

        if(inWinState)
        {
            app.draw(winText);
            app.draw(resetButton);
            app.draw(quitText);
            app.display();
        }


        if (inMainMenu) {
            app.draw(playButton);
            app.draw(playButtonText);
            app.display();
        } else if (inPlayingState) {
            p1.Draw(app);
            stateManager.update();
            stateManager.handleInput();
            stateManager.render();
            if(!p1.isAlive())
            {
                inGameOver = true;
                inPlayingState = false;
            }
        }

        app.clear(sf::Color::Cyan);
    }
    return 0;
}
