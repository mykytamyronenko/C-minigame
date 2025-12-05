#include "Player.h"
#include "Room1.h"
#include "Animation.h"

Player::Player(sf::Color col, int life, bool alive, int damage, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float moveSpeed):
    life(life), alive(alive), damage(damage),animation(texture, imageCount,switchTime)
{
    circle = sf::CircleShape(20);
    circle.setScale(1.2f, 1.2f);
    circle.setPosition((WINDOW_WIDTH - 2 * circle.getRadius()) / 2, (WINDOW_HEIGHT - 2 * circle.getRadius()) / 2);
    circle.setTexture(texture);

    this->moveSpeed = moveSpeed;
    row = 0;
    animationSpeed = moveSpeed*50;

    projectileSpeed = 10.0f;
    arrowTexture_.loadFromFile("Images/arrow.png");
    for (int i = 0; i < 1; ++i)
    {
        projectiles[i] = sf::CircleShape(10);
        projectiles[i].setFillColor(sf::Color::White);
        projectiles[i].setPosition(-100, -100);
        projectiles[i].setScale(2.0f,2.0f);
        projectiles[i].setTexture(&arrowTexture_);
        projectileDirections[i] = sf::Vector2f(0, 0);
    }
    // Initialisation de tous les états des projectiles à false (non en vol)
    for (int i = 0; i < 1; ++i) {
        projectileInFlight[i] = false;
    }
        bool canReceiveDamage = true;
        damageTimer.restart();

}

Player::~Player()
{
    //dtor
}

sf::CircleShape& Player::getCircle()
{
    return circle;
}
int Player::getLife()
{
    return life;
}
void Player::setLife(int lif)
{
    life += lif;
}
int Player::getDamage()
{
    return damage;
}

void Player::setDamage(int dmg)
{
    damage += dmg;
}


void Player::update()
{
    sf::Vector2f newPosition = circle.getPosition(); // Obtenir la position actuelle

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && newPosition.y > WALL_THICKNESS) {
        newPosition.y -= moveSpeed; // Déplacer vers le haut
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && newPosition.x > WALL_THICKNESS) {
        newPosition.x -= moveSpeed; // Déplacer vers la gauche
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && newPosition.y + 2 * circle.getRadius() < WINDOW_HEIGHT - WALL_THICKNESS) {
        newPosition.y += moveSpeed; // Déplacer vers le bas
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && newPosition.x + 2 * circle.getRadius() < WINDOW_WIDTH - WALL_THICKNESS) {
        newPosition.x += moveSpeed; // Déplacer vers la droite
    }

    circle.setPosition(newPosition); // Mettre à jour la position du cercle


    //projectiles

    // Tir de projectile avec les touches fléchées
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // Trouve le premier projectile inactif
        int inactiveProjectileIndex = -1;
        for (int i = 0; i < 1; ++i)
        {
            projectiles[projectileInFlight[i]].setRotation(90.0f);
            if (!projectileInFlight[i])
            {
                inactiveProjectileIndex = i;
                break;
            }
        }

    // S'il y a un projectile inactif, s'active
    if (inactiveProjectileIndex != -1)
    {
        projectiles[inactiveProjectileIndex].setPosition(circle.getPosition().x + circle.getRadius()*2 ,circle.getPosition().y - circle.getRadius()*0.5);
        projectileDirections[inactiveProjectileIndex] = sf::Vector2f(0, -1);
        projectileInFlight[inactiveProjectileIndex] = true;
    }
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    // Trouve le premier projectile inactif
    int inactiveProjectileIndex = -1;
    for (int i = 0; i < 1; ++i)
    {
        projectiles[projectileInFlight[i]].setRotation(0.0f);
        if (!projectileInFlight[i])
        {
            inactiveProjectileIndex = i;
            break;
        }
    }

    // S'il y a un projectile inactif, s'active
    if (inactiveProjectileIndex != -1)
    {
        projectiles[inactiveProjectileIndex].setPosition(circle.getPosition().x, circle.getPosition().y);
        projectileDirections[inactiveProjectileIndex] = sf::Vector2f(-1, 0);
        projectileInFlight[inactiveProjectileIndex] = true;
    }
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    // Trouve le premier projectile inactif
    int inactiveProjectileIndex = -1;
    for (int i = 0; i < 1; ++i)
    {
        projectiles[projectileInFlight[i]].setRotation(180.0f);
        if (!projectileInFlight[i])
        {
            inactiveProjectileIndex = i;
            break;
        }
    }

    // S'il y a un projectile inactif, s'active
    if (inactiveProjectileIndex != -1)
    {
        projectiles[inactiveProjectileIndex].setPosition(circle.getPosition().x + circle.getRadius()*2, circle.getPosition().y - circle.getRadius()*-2);
        projectileDirections[inactiveProjectileIndex] = sf::Vector2f(1, 0);
        projectileInFlight[inactiveProjectileIndex] = true;
    }
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
{
    // Trouve le premier projectile inactif
    int inactiveProjectileIndex = -1;
    for (int i = 0; i < 1; ++i)
    {
        projectiles[projectileInFlight[i]].setRotation(270.0f);
        if (!projectileInFlight[i])
        {
            inactiveProjectileIndex = i;
            break;
        }
    }

    // S'il y a un projectile inactif, s'active
    if (inactiveProjectileIndex != -1)
    {
        projectiles[inactiveProjectileIndex].setPosition(circle.getPosition().x, circle.getPosition().y - circle.getRadius()*-2);
        projectileDirections[inactiveProjectileIndex] = sf::Vector2f(0, 1);
        projectileInFlight[inactiveProjectileIndex] = true;
    }
}



}

sf::CircleShape* Player::getProjectiles() {
    return projectiles;
}


sf::Vector2f* Player::getProjectileDirections()
{
    return projectileDirections;
}

int Player::getCurrentProjectileIndex()
{
    return currentProjectileIndex;
}

bool* Player::getProjectileInFlight()
{
    return projectileInFlight;
}

float Player::getProjectileSpeed()
{
    return projectileSpeed;
}

void Player::setProjectileInFlight(bool truefalse)
{
    projectileInFlight[0] = truefalse;
}

void Player::decreaseHealth(int amount) {
    life -= amount;
    if (life <= 0) {
        life = 0;  // Assure que les PV ne deviennent pas négatifs
        alive = false;
    }
}

bool Player::isAlive()const {
    return alive;
}


void Player::applyDamage(std::vector<Enemy>& enemies) {
    float elapsedTotalTime = damageTimer.getElapsedTime().asSeconds();

    if (canReceiveDamage && elapsedTotalTime >= 2.0f) {
        for (int i=0;i<NUM_ENEMIES;i++) {
            if (isPlayerCollidingWithEnemy(circle, enemies[i].getEne())) {
                decreaseHealth(10);
                enemies[i].moveOppositeDirection();
                canReceiveDamage = false;
                damageTimer.restart();
                break;
            }
        }
    }
    for (int i=0;i<NUM_ENEMIES;i++) {
        if (isPlayerCollidingWithEnemy(circle, enemies[i].getEne())) {
            enemies[i].moveOppositeDirection();
        }
    }

    // Contrôler le délai de 10 secondes
    elapsedTotalTime = damageTimer.getElapsedTime().asSeconds();
    if (!canReceiveDamage && elapsedTotalTime >= 2.0f) {
        canReceiveDamage = true; // Réactive la possibilité de subir des dégâts après 10 secondes
    }

    // Vérifier la mort du joueur ici et prendre des mesures si nécessaire
    if (!isAlive()) {
        // Action à effectuer si le joueur est mort
        circle.setPosition(500, 200);
    }
}

void Player::applyDamageRoom2(std::vector<Enemy>& enemies, std::vector<Enemy2> enemies2) {
    float elapsedTotalTime = damageTimer.getElapsedTime().asSeconds();

    if (canReceiveDamage && elapsedTotalTime >= 2.0f) {
        for (int i=0;i<NUM_ENEMIES1_ROOM2;i++) {
            if (isPlayerCollidingWithEnemy(circle, enemies[i].getEne())) {
                decreaseHealth(10);
                enemies[i].moveOppositeDirection();
                canReceiveDamage = false;
                damageTimer.restart();
                break;
            }
        }
        for (int i=0;i<NUM_ENEMIES2_ROOM2;i++) {
            if (isPlayerCollidingWithEnemy(circle, enemies2[i].getEne())) {
                decreaseHealth(10);
                enemies2[i].moveOppositeDirection();
                canReceiveDamage = false;
                damageTimer.restart();
                break;
            }
        }
    }
    for (int i=0;i<NUM_ENEMIES1_ROOM2;i++) {
        if (isPlayerCollidingWithEnemy(circle, enemies[i].getEne())) {
            enemies[i].moveOppositeDirection();
        }
    }
    for (int i=0;i<NUM_ENEMIES2_ROOM2;i++) {
        if (isPlayerCollidingWithEnemy(circle, enemies2[i].getEne())) {
            enemies2[i].moveOppositeDirection();
        }
    }

    // Contrôler le délai de 10 secondes
    elapsedTotalTime = damageTimer.getElapsedTime().asSeconds();
    if (!canReceiveDamage && elapsedTotalTime >= 2.0f) {
        canReceiveDamage = true; // Réactive la possibilité de subir des dégâts après 10 secondes
    }

    // Vérifier la mort du joueur ici et prendre des mesures si nécessaire
    if (!isAlive()) {
        // Action à effectuer si le joueur est mort
        circle.setPosition(500, 200);
    }
}



bool Player::isPlayerCollidingWithEnemy(const sf::CircleShape& player, const sf::RectangleShape& enemy)
{
    // Calcule les coordonnées du centre du cercle du player
    float centerX = player.getPosition().x + player.getRadius();
    float centerY = player.getPosition().y + player.getRadius();

    // Calcule les coordonnées du rectangle de l'ennemi
    float rectLeft = enemy.getPosition().x;
    float rectRight = enemy.getPosition().x + enemy.getSize().x;
    float rectTop = enemy.getPosition().y;
    float rectBottom = enemy.getPosition().y + enemy.getSize().y;

    // Calcule la distance la plus proche entre le centre du cercle du player et le rectangle de l'ennemi
    float closestX = std::max(rectLeft, std::min(centerX, rectRight));
    float closestY = std::max(rectTop, std::min(centerY, rectBottom));

    // Calcule la distance entre le centre du cercle du player et le point le plus proche
    float distanceX = centerX - closestX;
    float distanceY = centerY - closestY;

    // Utilise le théorème de Pythagore pour calculer la distance réelle
    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    // Si la distance est inférieure au rayon du cercle du player, il y a une collision
    if (distance < player.getRadius()) {
        return true; // Collision détectée
    }

    return false; // Pas de collision
}


void Player::drawHealthAndDamage(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("font/arial.ttf")) {
        // Gestion de l'erreur si la police ne peut pas être chargée
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10); // Position du texte à l'écran

    // Convertir les points de vie en chaîne de caractères pour affichage
    //std::string healthString = "Health: " + std::to_string(life);
    std::stringstream ss;
    ss << "Health: " << life;
    ss << " Damage: " << damage;
    std::string healthString = ss.str();

    text.setString(healthString);

    // Dessiner le texte sur la fenêtre
    window.draw(text);
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(circle);
}

void Player::animationUpdate(float deltaTime){

    sf::Vector2f newPosition = circle.getPosition();
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && newPosition.y > WALL_THICKNESS) {
        movement.y -= animationSpeed * deltaTime; // Déplacer vers le haut
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && newPosition.x > WALL_THICKNESS) {
        movement.x -= animationSpeed * deltaTime; // Déplacer vers la gauche
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && newPosition.y + 2 * circle.getRadius() < WINDOW_HEIGHT - WALL_THICKNESS) {
        movement.y += animationSpeed * deltaTime; // Déplacer vers le bas
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && newPosition.x + 2 * circle.getRadius() < WINDOW_WIDTH - WALL_THICKNESS) {
        movement.x += animationSpeed * deltaTime; // Déplacer vers la droite
    }

    if(movement.x == 0.0f && movement.y == 0.0f){
        row = 0;
    }
    else if(movement.x > 0.0f){
        row = 3;
    }
    else if(movement.x < 0.0f){
        row = 1;
    }
    else if(movement.y > 0.0f){
        row = 0;
    }
    else if(movement.y < 0.0f){
        row = 2;
    }


    animation.Update(row, deltaTime);
    circle.setTextureRect(animation.uvRect);

}

