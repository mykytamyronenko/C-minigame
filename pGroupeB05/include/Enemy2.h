#ifndef ENEMY2_H
#define ENEMY2_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy.h"

class Enemy;

class Enemy2
{
     private:
        int health;
        bool alive;
        sf::RectangleShape shape;
        sf::Vector2f velocity;
        sf::Clock totalTimer;
        sf::Clock chargeTimer; // Chronomètre pour contrôler la période de charge
        sf::Clock pauseTimer;  // Chronomètre pour contrôler la période de pause
        bool isCharging;       // Indicateur pour savoir si l'ennemi est en train de charger ou non

        float enemySpeed = 11.0f;     // Vitesse de déplacement de l'ennemi

         sf::Vector2f getPosition() const;


    public:
        Enemy2(float x, float y, const sf::Texture& texture, int health=100, bool alive=true);
        virtual ~Enemy2();
        void update(const sf::Vector2f& playerPosition);
        sf::RectangleShape getEne()const;
        void setShapeColor(const sf::Color& color);

        // Méthode pour décrémenter les points de vie
        void decreaseHealth(int amount);
        bool isAlive()const;
        void destroy();
        void avoidCollision(const Enemy2& other);
        void avoidCollision2(Enemy& other);
        // Gestion de la collision entre l'enemie et un obstacle
        void moveOppositeDirection();

};

#endif // ENEMY2_H
