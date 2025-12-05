#ifndef ROOM7_H
#define ROOM7_H

#include <State.h>
#include "StateManager.h"
#include "Room1.h"
#include "Enemy.h"
#include "Player.h"
#include "Items.h"
#include "IronArrowhead.h"
#include "Tacos.h"
class Room6;


class Room7: public State
{
    private:
        sf::RenderWindow& app;  // Membre pour stocker l'instance de sf::RenderWindow

        sf::Texture enemyTexture; // Déclaration de la texture pour la porte

        StateManager& stateManager;
        Player& p1;
        std::vector<Enemy> enemies;
        int numDeadEnemies1 = 0;
        const int WINDOW_WIDTH = 1920;
        const int WINDOW_HEIGHT = 1080;
        const int WALL_THICKNESS = 25;
        bool tmpRoom7=true;

    public:
        Room7(sf::RenderWindow& app,StateManager& stateManager,Player& p1);
        virtual ~Room7();
        void setState(State* newState);
        void update();
        void render();
        void handleInput();

        void handleEnemyCollision(Enemy& ene1, Enemy& ene2);
        bool areRectanglesColliding(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);

        bool isProjectileCollidingWithEnemy(const sf::CircleShape& projectile, const sf::RectangleShape& enemy);
        bool isPlayerCollidingWithEnemy(const sf::CircleShape& player, const sf::RectangleShape& enemy);
        int getNumDeadBoss();
        bool gettmpRoom7();
};

#endif // ROOM7_H
