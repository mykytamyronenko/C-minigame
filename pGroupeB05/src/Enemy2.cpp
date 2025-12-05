#include "Enemy2.h"

Enemy2::Enemy2(float x, float y, const sf::Texture& texture, int health, bool alive):health(health), alive(alive),totalTimer()
{
    shape.setSize(sf::Vector2f(40, 40));
    shape.setTexture(&texture);
    shape.setPosition(x, y);

    velocity = sf::Vector2f(0.0f, 0.0f);
}

Enemy2::~Enemy2()
{
    //dtor
}

void Enemy2::update(const sf::Vector2f& playerPosition) {
    float elapsedTotalTime = totalTimer.getElapsedTime().asSeconds();

    // Définition de la durée de la charge et de la pause
    const float chargeDuration = 3.0f;
    const float pauseDuration = 1.0f;

    // Divise le temps total en cycles de charge et de pause
    int cycleCount = static_cast<int>(elapsedTotalTime / (chargeDuration + pauseDuration));
    float timeInCycle = fmod(elapsedTotalTime, chargeDuration + pauseDuration);

    if (timeInCycle < chargeDuration) {
        // Charge vers le joueur
        sf::Vector2f direction = playerPosition - shape.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0.1f) {
            direction /= length;
            velocity = direction * enemySpeed;
        }
    } else {
        // En pause, arrête le mouvement
        velocity = sf::Vector2f(0.0f, 0.0f);
    }
    if(!isAlive())
    {
        velocity = sf::Vector2f(0.0f, 0.0f); // Définit la vitesse à zéro si l'ennemi n'est pas vivant
    }

    shape.move(velocity);
}

sf::RectangleShape Enemy2::getEne()const
{
    return shape;
}


void Enemy2::setShapeColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

void Enemy2::decreaseHealth(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;  // Assurer que les PV ne deviennent pas négatifs
        alive = false;
    }
}

bool Enemy2::isAlive()const {
    return alive;
}

void Enemy2::destroy() {
    shape.setPosition(-1000, -1000); // Positionne l'ennemi hors de l'écran (ou autre action pour le faire disparaître)
}

void Enemy2::avoidCollision(const Enemy2& other)
{
    // Calculez la direction entre les ennemis
    sf::Vector2f direction = shape.getPosition() - other.shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.1f) {  // Éviter la division par zéro
        direction /= length;
        shape.move(direction * 5.0f);  // Ajuster la position de l'ennemi
    }
}

void Enemy2::avoidCollision2(Enemy& other)
{
    sf::Vector2f direction = shape.getPosition() - other.getEne().getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.1f) {  // Éviter la division par zéro
        direction /= length;
        shape.move(direction * 5.0f);  // Ajuster la position de l'ennemi
    }
}

void Enemy2::moveOppositeDirection()
{
    shape.move(-velocity * 2.0f);
}
