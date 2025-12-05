#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Enemy2.h"
#include <iostream>
#include <sstream>
#include "Animation.h"

const int MAX_PROJECTILES = 1;

class Player
{
    private:
        sf::CircleShape circle;
        int life;
        bool alive;
        int damage;
        float moveSpeed;
        float animationSpeed;
        const int WINDOW_WIDTH = 1920;
        const int WINDOW_HEIGHT = 1080;
        const int WALL_THICKNESS = 5;

        sf::CircleShape projectiles[MAX_PROJECTILES];
        sf::Vector2f projectileDirections[MAX_PROJECTILES];
        sf::Texture arrowTexture_;
        sf::RectangleShape body;
        int currentProjectileIndex;
        bool projectileInFlight[MAX_PROJECTILES];
        float projectileSpeed;

        bool canReceiveDamage;
        sf::Clock damageTimer;
        Animation animation;
        unsigned int row;

    public:
        Player(sf::Color,int life,bool alive,int damage, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float moveSpeed);
        virtual ~Player();
        sf::CircleShape& getCircle();
        int getLife();
        void setLife(int lif);
        int getDamage();
        void setDamage(int dmg);
        void update();
        void animationUpdate(float deltaTime);
        sf::CircleShape* getProjectiles();
        sf::Vector2f* getProjectileDirections();
        int getCurrentProjectileIndex();
        bool* getProjectileInFlight();
        float getProjectileSpeed();
        void setProjectileInFlight(bool truefalse);

        void decreaseHealth(int amount);
        bool isAlive()const;

        void applyDamage(std::vector<Enemy>& enemies);
        void applyDamageRoom2(std::vector<Enemy>& enemies, std::vector<Enemy2> enemies2);
        bool isPlayerCollidingWithEnemy(const sf::CircleShape& player, const sf::RectangleShape& enemy);
        void drawHealthAndDamage(sf::RenderWindow& window);

        void Draw(sf::RenderWindow& window);

};

#endif // PLAYER_H
