#ifndef ROOM1_H
#define ROOM1_H

#include <State.h>
#include "StateManager.h"
#include "Room2.h"
#include <vector>
#include "Enemy.h"
#include "Player.h"

class Room2;

const int NUM_OBSTACLES = 5;
const int NUM_ENEMIES = 3;

class Room1 : public State
{
    private:
        sf::RenderWindow& app;  // Membre pour stocker l'instance de sf::RenderWindow
        sf::RectangleShape door;
        sf::RectangleShape obstacles[NUM_OBSTACLES]; // création d'un obstacle
        StateManager& stateManager;
        sf::Sprite doorSprite; // Déclaration du sprite pour la porte
        sf::Texture doorTexture; // Déclaration de la texture pour la porte

        sf::Texture obstaclesTexture; // Déclaration de la texture pour la porte

        sf::Texture enemyTexture; // Déclaration de la texture pour la porte

        const int WINDOW_WIDTH = 1920;
        const int WINDOW_HEIGHT = 1080;
        const int WALL_THICKNESS = 25;
        std::vector<Enemy> enemies;
        int numDeadEnemies = 0;
        Player& p1;
    public:
        Room1(sf::RenderWindow& app,StateManager& stateManager,Player& p1);
        virtual ~Room1();
        void setState(State* newState);
        void update();
        void render();
        void handleInput();

        // Gestion des collisions
        bool isCollidingWithObstacle(float x, float y, float radius);

        void handleEnemyCollision(Enemy& ene1, Enemy& ene2);
        bool areRectanglesColliding(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);

        bool isProjectileCollidingWithEnemy(const sf::CircleShape& projectile, const sf::RectangleShape& enemy);
        bool isEnemyCollidingWithObstacle(const Enemy& enemy, const sf::RectangleShape& obstacle);

        bool isPlayerObstacle(const sf::CircleShape& player, const sf::RectangleShape& obstacle);

};

#endif // ROOM1_H
