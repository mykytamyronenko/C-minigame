#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy2.h"
//#include "StateManager.h"

class Enemy2;

class Enemy
{
    private:
        int health;
        bool alive;
        bool alive2=true;
        bool finaldeath=true;
        sf::RectangleShape shape;
        sf::Vector2f velocity;
        //StateManager& stateManager;

    public:
        Enemy(float x, float y, const sf::Texture& texture/*,StateManager& stateManager*/, int health=100, bool alive=true);
        virtual ~Enemy();
        void update(const sf::Vector2f& playerPosition);
        sf::RectangleShape getEne()const;
        sf::Sprite getEneSlime();

        void setShapeColor(const sf::Color& color);

        // Méthode pour décrémenter les points de vie
        void decreaseHealth(int amount);

        bool isAlive()const;

        void destroy();
        void setSizeEne(int nb1,int nb2);

        void avoidCollision(const Enemy& other);
        void avoidCollision2(Enemy2& other);

        // Gestion de la collision entre l'enemie et un obstacle
        void moveOppositeDirection();
};

#endif // ENEMY_H
