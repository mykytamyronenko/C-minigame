#ifndef ROOM3_H
#define ROOM3_H

#include <State.h>
#include "StateManager.h"
#include "Room1.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Player.h"
#include "Items.h"
#include "IronArrowhead.h"
#include "Tacos.h"
class Room2;

const int NUM_OBSTACLES3 = 6;
const int NUM_ENEMIES1_ROOM3 = 2;
const int NUM_ENEMIES2_ROOM3 = 1;

class Room3: public State
{
    private:
        sf::RenderWindow& app;  // Membre pour stocker l'instance de sf::RenderWindow
        sf::RectangleShape door;
        sf::RectangleShape doorToR2;
        sf::RectangleShape doorToR5;
        sf::RectangleShape obstacles[NUM_OBSTACLES3];

        StateManager& stateManager;
        Player& p1;
        std::vector<Enemy> enemies;
        int numDeadEnemies1 = 0;
        std::vector<Enemy2> enemies2;
        int numDeadEnemies2 = 0;
        const int WINDOW_WIDTH = 1920;
        const int WINDOW_HEIGHT = 1080;
        const int WALL_THICKNESS = 5;
        sf::Texture enemyTexture; // Déclaration de la texture pour la porte
        sf::Texture enemyTexture2; // Déclaration de la texture pour la porte
    public:
        Room3(sf::RenderWindow& app,StateManager& stateManager,Player& p1);
        virtual ~Room3();
        void setState(State* newState);
        void update();
        void render();
        void handleInput();
        bool isCollidingWithObstacle(float x, float y, float radius);

        void handleEnemyCollision(Enemy& ene1, Enemy& ene2);
        void handleEnemyCollision2(Enemy2& ene1, Enemy2& ene2);
        void handleEnemyCollision3(Enemy& ene1, Enemy2& ene2);
        bool areRectanglesColliding(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);

        bool isProjectileCollidingWithEnemy(const sf::CircleShape& projectile, const sf::RectangleShape& enemy);
        bool isEnemyCollidingWithObstacle(const Enemy2& enemy, const sf::RectangleShape& obstacle);
        bool isPlayerObstacle(const sf::CircleShape& player, const sf::RectangleShape& obstacle);
        bool isPlayerCollidingWithEnemy(const sf::CircleShape& player, const sf::RectangleShape& enemy);

};

#endif // ROOM3_H

