#include "Room1.h"
#include <cmath>
#include <iostream>

Room1::Room1(sf::RenderWindow& app,StateManager& stateManager,Player& p1): app(app),stateManager(stateManager),p1(p1)
{
    door = sf::RectangleShape(sf::Vector2f(50, WALL_THICKNESS));
    door.setFillColor(sf::Color::Black);  // Vous pouvez choisir la couleur que vous préférez
    door.setPosition((WINDOW_WIDTH - 50) / 2, 0);  // Au milieu du mur supérieur

    doorTexture.loadFromFile("Images/DoorClose.png");
    doorSprite.setTexture(doorTexture);
    doorSprite.setScale(0.5f, 0.5f);
    doorSprite.setPosition((WINDOW_WIDTH - 50) / 2, 0);

    // Initialisation des obstacles
    obstacles[0] = sf::RectangleShape(sf::Vector2f(40, 30));
    obstacles[0].setFillColor(sf::Color::Transparent);
    obstacles[0].setPosition(940, 0);

    obstacles[1] = sf::RectangleShape(sf::Vector2f(100, 100));
    obstacles[1].setPosition(380, 430);

    obstacles[2] = sf::RectangleShape(sf::Vector2f(200, 100));
    obstacles[2].setPosition(780, 150);

    obstacles[3] = sf::RectangleShape(sf::Vector2f(200, 200));
    obstacles[3].setPosition(1000, 500);

    obstacles[4] = sf::RectangleShape(sf::Vector2f(200, 200));
    obstacles[4].setPosition(50, 50);

    for(int i = 1; i<=NUM_OBSTACLES; i++){
            obstaclesTexture.loadFromFile("Images/obstacle3.png");
            obstacles[i].setTexture(&obstaclesTexture);

    }

    // Initialisation de tous les enemies
    enemyTexture.loadFromFile("Images/BaseSlime.png");
    enemies.push_back(Enemy(300.0f, 10.0f, enemyTexture));
    enemies.push_back(Enemy(1000.0f, 10.0f, enemyTexture));
    enemies.push_back(Enemy(1500.0f, 500.0f, enemyTexture));
}

Room1::~Room1()
{
}

void Room1::update()
{
    //mise a jour enemy
    for (int i=0;i<NUM_ENEMIES;i++)
    {
        enemies[i].update(p1.getCircle().getPosition());
    }

    // Gestion de toutes les collisions entre les ennemis
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        for (int j = i + 1; j < NUM_ENEMIES; j++)
        {
            handleEnemyCollision(enemies[i], enemies[j]);
        }
    }
}

void Room1::render()
{
    sf::Sprite groundSprite; // Déclaration du sprite pour la porte
    sf::Texture groundTexture;
    groundTexture.loadFromFile("Images/ground.png");
    groundSprite.setTexture(groundTexture);
    sf::IntRect repeatingRectGround(0, 0, groundTexture.getSize().x, groundTexture.getSize().y);
    for (int y = 0; y < app.getSize().y; y += repeatingRectGround.height) {
        for (int x = 0; x < app.getSize().x; x += repeatingRectGround.width) {
            groundSprite.setTextureRect(repeatingRectGround);
            groundSprite.setPosition(x, y);
            app.draw(groundSprite);
        }
    }


    sf::RectangleShape topWall(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS));
    topWall.setFillColor(sf::Color::Black);
    topWall.setPosition(0, 0);

    sf::RectangleShape bottomWall(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS));
    bottomWall.setFillColor(sf::Color::Black);
    bottomWall.setPosition(0, WINDOW_HEIGHT - WALL_THICKNESS);

    sf::RectangleShape leftWall(sf::Vector2f(WALL_THICKNESS, WINDOW_HEIGHT));
    leftWall.setFillColor(sf::Color::Black);
    leftWall.setPosition(0, 0);

    sf::RectangleShape rightWall(sf::Vector2f(WALL_THICKNESS, WINDOW_HEIGHT));
    rightWall.setFillColor(sf::Color::Black);
    rightWall.setPosition(WINDOW_WIDTH - WALL_THICKNESS, 0);

    app.draw(topWall);
    app.draw(bottomWall);
    app.draw(leftWall);
    app.draw(rightWall);
    app.draw(door);



    //----------------------------TOPWALL
    sf::Sprite TBWallSprite; // Déclaration du sprite pour la porte
    sf::Texture WallTexture;
    WallTexture.loadFromFile("Images/wall.png");
    TBWallSprite.setTexture(WallTexture);
    sf::IntRect repeatingRect(0, 0, WallTexture.getSize().x, WALL_THICKNESS);
    // Dessin du sprite répété horizontalement et verticalement
    for (int x = 0; x < app.getSize().x; x += repeatingRect.width) {
        TBWallSprite.setTextureRect(repeatingRect);
        TBWallSprite.setPosition(x, 0);
        app.draw(TBWallSprite);
        TBWallSprite.setPosition(x, WINDOW_HEIGHT - WALL_THICKNESS);
        app.draw(TBWallSprite);
    }

    //----------------------------sideWall
    sf::Sprite sideWallSprite;
    sideWallSprite.setTexture(WallTexture);
    sideWallSprite.setRotation(90.0f);
    sf::IntRect repeatingRectSide(0, 0, WallTexture.getSize().y,WALL_THICKNESS);
    for (int y = 0; y < app.getSize().y; y += repeatingRectSide.height) {
        for (int x = 0; x < WALL_THICKNESS; x += 1) {
            sideWallSprite.setTextureRect(repeatingRectSide);
            sideWallSprite.setPosition(WINDOW_WIDTH, y);
            app.draw(sideWallSprite);
            sideWallSprite.setPosition(x, y);
            app.draw(sideWallSprite);
        }
    }

    app.draw(doorSprite);

    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        app.draw(obstacles[i]);
    }
    app.draw(p1.getCircle());
    for (int i=0;i<NUM_ENEMIES;i++)
    {
        app.draw(enemies[i].getEne());
    }

    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        app.draw(p1.getProjectiles()[i]);
    }
    p1.drawHealthAndDamage(app);
}

void Room1::handleInput()
{
    sf::Vector2f oldPosition = p1.getCircle().getPosition(); // Stocke l'ancienne position du joueur
    p1.update();
    p1.applyDamage(enemies);

    // Vérification de la collision avec l'obstacle après les déplacements
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        // S'il y a collision, on réinitialise la position du cercle aux anciennes coordonnées
        if (isPlayerObstacle(p1.getCircle(),obstacles[i])) {
            p1.getCircle().setPosition(oldPosition);
        }
    }



    if (p1.getCircle().getPosition().x < WALL_THICKNESS) {
        p1.getCircle().setPosition(WALL_THICKNESS, p1.getCircle().getPosition().y);
    }
    if (p1.getCircle().getPosition().x + 2 * p1.getCircle().getRadius() > WINDOW_WIDTH - WALL_THICKNESS) {
        p1.getCircle().setPosition(WINDOW_WIDTH - 2 * p1.getCircle().getRadius() - WALL_THICKNESS, p1.getCircle().getPosition().y);
    }

    if (p1.getCircle().getPosition().y < WALL_THICKNESS) {
        p1.getCircle().setPosition(p1.getCircle().getPosition().x, WALL_THICKNESS);
    }
    if (p1.getCircle().getPosition().y + 2 * p1.getCircle().getRadius() > WINDOW_HEIGHT - WALL_THICKNESS) {
        p1.getCircle().setPosition(p1.getCircle().getPosition().x, WINDOW_HEIGHT - 2 * p1.getCircle().getRadius() - WALL_THICKNESS);
    }
    if (p1.getCircle().getPosition().y <= door.getPosition().y + WALL_THICKNESS && p1.getCircle().getPosition().x >= door.getPosition().x
        && p1.getCircle().getPosition().x + 2 * p1.getCircle().getRadius() <= door.getPosition().x + 50) {
        stateManager.setState(stateManager.getStateRoom2());

        if(stateManager.getCurrentState()== stateManager.getStateRoom2())
        {
            p1.getCircle().setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT - 20 );
        }
    }

    // Déplace tous les projectiles en vol
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        if (p1.getProjectileInFlight()[i])
        {
            p1.getProjectiles()[i].move(p1.getProjectileSpeed() * p1.getProjectileDirections()[i].x, p1.getProjectileSpeed() * p1.getProjectileDirections()[i].y);

            // Vérifie si le projectile a quitté l'écran ou atteint une certaine condition
            if (p1.getProjectiles()[i].getPosition().y < 0 || p1.getProjectiles()[i].getPosition().x < 0 || p1.getProjectiles()[i].getPosition().x > WINDOW_WIDTH
                || p1.getProjectiles()[i].getPosition().y > WINDOW_HEIGHT )
            {
                // Réinitialisation de la position du projectile
                p1.getProjectiles()[i].setPosition(-100, -100);
                // Marque que le projectile n'est plus en vol
                p1.setProjectileInFlight(false);
            }
        }

        if (isCollidingWithObstacle(p1.getProjectiles()[i].getPosition().x, p1.getProjectiles()[i].getPosition().y, p1.getProjectiles()[i].getRadius()))
        {
            // S'il y a collision, le projectiles[i] disparait
            p1.getProjectiles()[i].setPosition(-100, -100);
        }

        //gestion de la mort des enemies
        for (int i = 0; i < MAX_PROJECTILES; ++i)
        {
            for (int j = 0; j < NUM_ENEMIES; ++j)
            {
                if (isProjectileCollidingWithEnemy(p1.getProjectiles()[i], enemies[j].getEne()))
                {
                    p1.getProjectiles()[i].setPosition(-100, -100);
                    enemies[j].decreaseHealth(p1.getDamage()); // Dégâts infligés
                    if (!enemies[j].isAlive())
                    {
                        enemies[j].destroy();
                        numDeadEnemies += 1;
                        if(numDeadEnemies==NUM_ENEMIES)
                        {
                            obstacles[0].setPosition(-1000, -1000);
                            doorTexture.loadFromFile("Images/DoorOpen.png");
                            doorSprite.setTexture(doorTexture);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        for (int j = 0; j < NUM_OBSTACLES; j++)
        {
            if (areRectanglesColliding(enemies[i].getEne(), obstacles[j]))
            {
                enemies[i].moveOppositeDirection();
            }
        }
    }



}



bool Room1::isCollidingWithObstacle(float x, float y, float radius) {
    // Calcule des coordonnées du centre du cercle
    float centerX = x + radius;
    float centerY = y + radius;

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        const sf::RectangleShape& obstacle = obstacles[i];

        // Calcule des coordonnées du rectangle obstacle
        float rectLeft = obstacle.getPosition().x;
        float rectRight = obstacle.getPosition().x + obstacle.getSize().x;
        float rectTop = obstacle.getPosition().y;
        float rectBottom = obstacle.getPosition().y + obstacle.getSize().y;

        // Calcule la distance la plus proche entre le centre du cercle et le rectangle
        float closestX = std::max(rectLeft, std::min(centerX, rectRight));
        float closestY = std::max(rectTop, std::min(centerY, rectBottom));

        // Calcule la distance entre le centre du cercle et le point le plus proche
        float distanceX = centerX - closestX;
        float distanceY = centerY - closestY;

        // Utilise le théorème de Pythagore pour calculer la distance réelle
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        // Si la distance est inférieure au rayon du cercle, il y a une collision
        if (distance < radius) {
            return true; // Collision détectée
        }
    }

    return false; // Pas de collision
}

bool Room1::areRectanglesColliding(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
    sf::FloatRect rect1Bounds = rect1.getGlobalBounds();
    sf::FloatRect rect2Bounds = rect2.getGlobalBounds();


    return rect1Bounds.intersects(rect2Bounds);
}

void Room1::handleEnemyCollision(Enemy& ene1, Enemy& ene2)
{
    if (areRectanglesColliding(ene1.getEne(), ene2.getEne()))
    {
        // Déplacement des ennemis dans des directions opposées
        ene1.avoidCollision(ene2);
        ene2.avoidCollision(ene1);
    }
}

bool Room1::isProjectileCollidingWithEnemy(const sf::CircleShape& projectile, const sf::RectangleShape& enemy)
{
    // Création d'une forme rectangulaire pour l'ennemi
    sf::FloatRect enemyBounds = enemy.getGlobalBounds();

    // Création d'une forme rectangulaire pour le projectile
    sf::FloatRect projectileBounds = projectile.getGlobalBounds();

    // Vérifie si les deux formes rectangulaires (ennemi et projectile) se chevauchent
    if (projectileBounds.intersects(enemyBounds)) {
        return true; // Collision détectée
    }

    return false; // Pas de collisions
}

bool Room1::isPlayerObstacle(const sf::CircleShape& player, const sf::RectangleShape& obstacle)
{
    // Calcule les coordonnées du centre du cercle du projectile
    float centerX = player.getPosition().x + player.getRadius();
    float centerY = player.getPosition().y + player.getRadius();

    // Calcule les coordonnées du rectangle de l'ennemi
    float rectLeft = obstacle.getPosition().x;
    float rectRight = obstacle.getPosition().x + obstacle.getSize().x;
    float rectTop = obstacle.getPosition().y;
    float rectBottom = obstacle.getPosition().y + obstacle.getSize().y;

    // Calcule la distance la plus proche entre le centre du cercle du projectile et le rectangle de l'ennemi
    float closestX = std::max(rectLeft, std::min(centerX, rectRight));
    float closestY = std::max(rectTop, std::min(centerY, rectBottom));

    // Calcule la distance entre le centre du cercle du projectile et le point le plus proche
    float distanceX = centerX - closestX;
    float distanceY = centerY - closestY;

    // Utilise le théorème de Pythagore pour calculer la distance réelle
    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    // Si la distance est inférieure au rayon du cercle du projectile, il y a une collision
    if (distance < player.getRadius()) {
        return true; // Collision détectée
    }

    return false; // Pas de collision
}
