#include "Enemy.h"

Enemy::Enemy(float x, float y, const sf::Texture& texture/*,StateManager& stateManager*/, int health, bool alive):/*stateManager(stateManager),*/health(health), alive(alive)
{
    shape.setSize(sf::Vector2f(40, 40));
    shape.setTexture(&texture);
    shape.setPosition(x, y);

    velocity = sf::Vector2f(0.0f, 0.0f);
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::update(const sf::Vector2f& playerPosition) {
    sf::Vector2f direction = playerPosition - shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.1f) {  // Évite la division par zéro
        direction /= length;
        velocity = direction * 5.0f;  // le 5.0 c'est la speed de l'enemie
    }

    if (!alive) {
        velocity = sf::Vector2f(0.0f, 0.0f); // Définit la vitesse à zéro si l'ennemi n'est pas vivant
    }
    if(finaldeath)
    {
        if(!alive && (shape.getSize() == sf::Vector2f(160,160) || shape.getSize() == sf::Vector2f(80,80)))
        {
            if(shape.getSize() == sf::Vector2f(80,80))
            {
                alive2 = false;
            }
            alive = true;
            shape.setSize(sf::Vector2f(80,80));
            shape.setPosition(800, 100);
            health = 100;

            if(!alive2)
            {
                shape.setSize(sf::Vector2f(45,45));
                shape.setPosition(800, 100);
                health = 100;
                finaldeath=false;
            }

        }
    }
    shape.move(velocity);
}

sf::RectangleShape Enemy::getEne()const
{
    return shape;
}

void Enemy::setShapeColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

void Enemy::decreaseHealth(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;  // Assurer que les PV ne deviennent pas négatifs
        alive = false;
    }
}

bool Enemy::isAlive()const {
    return alive;
}

void Enemy::destroy() {
    shape.setPosition(-1000, -1000); // Positionne l'ennemi hors de l'écran (ou autre action pour le faire disparaître)
}

void Enemy::setSizeEne(int nb1,int nb2)
{
    shape.setSize(sf::Vector2f(nb1,nb2));
}

void Enemy::avoidCollision(const Enemy& other)
{
    // Calculez la direction entre les ennemis
    sf::Vector2f direction = shape.getPosition() - other.shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.1f) {  // Éviter la division par zéro
        direction /= length;
        shape.move(direction * 5.0f);  // Ajuster la position de l'ennemi
    }
}

void Enemy::avoidCollision2(Enemy2& other)
{
    sf::Vector2f direction = shape.getPosition() - other.getEne().getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.1f) {  // Éviter la division par zéro
        direction /= length;
        shape.move(direction * 5.0f);  // Ajuster la position de l'ennemi
    }
}

void Enemy::moveOppositeDirection()
{
    shape.move(-velocity * 2.0f);
}
