#include "Room3.h"

Room3::Room3(sf::RenderWindow& app,StateManager& stateManager,Player& p1): app(app),stateManager(stateManager),p1(p1)
{
    door = sf::RectangleShape(sf::Vector2f(50, WALL_THICKNESS));
    door.setFillColor(sf::Color::Magenta);
    door.setPosition((WINDOW_WIDTH - 50) / 2, 0);

    doorToR2 = sf::RectangleShape(sf::Vector2f(WALL_THICKNESS,50 ));
    doorToR2.setFillColor(sf::Color::Magenta);
    doorToR2.setPosition(0, (WINDOW_HEIGHT - WALL_THICKNESS) / 2);

    doorToR5 = sf::RectangleShape(sf::Vector2f(WALL_THICKNESS,50 ));
    doorToR5.setFillColor(sf::Color::Magenta);
    doorToR5.setPosition(WINDOW_WIDTH - 25, (WINDOW_HEIGHT - WALL_THICKNESS) / 2);

    // Initialisation des obstacles
    obstacles[0] = sf::RectangleShape(sf::Vector2f(30, 70));
    obstacles[0].setFillColor(sf::Color::Transparent);
    obstacles[0].setPosition(1885, 520);

    obstacles[1] = sf::RectangleShape(sf::Vector2f(50, 30));
    obstacles[1].setFillColor(sf::Color::Transparent);
    obstacles[1].setPosition(935, 0);

    obstacles[2] = sf::RectangleShape(sf::Vector2f(850, 400));
    obstacles[2].setFillColor(sf::Color::Black);
    obstacles[2].setPosition(10, 10);

    obstacles[3] = sf::RectangleShape(sf::Vector2f(850, 400));
    obstacles[3].setFillColor(sf::Color::Black);
    obstacles[3].setPosition(1060, 10);

    obstacles[4] = sf::RectangleShape(sf::Vector2f(850, 400));
    obstacles[4].setFillColor(sf::Color::Black);
    obstacles[4].setPosition(10, 670);

    obstacles[5] = sf::RectangleShape(sf::Vector2f(850, 400));
    obstacles[5].setFillColor(sf::Color::Black);
    obstacles[5].setPosition(1060, 670);

    enemyTexture.loadFromFile("Images/BaseSlime.png");
    enemies.push_back(Enemy(1000.0f, 100.0f, enemyTexture));
    enemies.push_back(Enemy(1000.0f, 800.0f, enemyTexture));

    enemyTexture2.loadFromFile("Images/skeleton.png");
    enemies2.push_back(Enemy2(1700.0f, 550.0f, enemyTexture2));
    // le programme crash si la ligne du dessous est retirée
    enemies2.push_back(Enemy2(1500.0f, 600.0f, enemyTexture2));


}

Room3::~Room3()
{
}



void Room3::update()
{
    for (int i=0;i<NUM_ENEMIES1_ROOM3;i++)
    {
        enemies[i].update(p1.getCircle().getPosition());
    }

    for (int i=0;i<NUM_ENEMIES2_ROOM3;i++)
    {
        enemies2[i].update(p1.getCircle().getPosition());
    }

    for (int i = 0; i < NUM_ENEMIES1_ROOM3; i++)
    {
        for (int j = i + 1; j < NUM_ENEMIES1_ROOM3; j++)
        {
            handleEnemyCollision(enemies[i], enemies[j]);
        }
    }
    for (int i = 0; i < NUM_ENEMIES2_ROOM3; i++)
    {
        for (int j = i + 1; j < NUM_ENEMIES2_ROOM3; j++)
        {
            handleEnemyCollision2(enemies2[i], enemies2[j]);
        }
    }

    for (int i = 0; i < NUM_ENEMIES1_ROOM3; i++)
    {
        for (int j = 0; j < NUM_ENEMIES2_ROOM3; j++)
        {
            handleEnemyCollision3(enemies[i], enemies2[j]);
        }
    }
}

void Room3::render()
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

    app.draw(door);
    app.draw(doorToR2);
    app.draw(doorToR5);
    app.draw(p1.getCircle());
    for (int i = 0; i < NUM_ENEMIES1_ROOM3; i++)
    {
        app.draw(enemies[i].getEne());
    }
    for (int i = 0; i < NUM_ENEMIES2_ROOM3; i++)
    {
        app.draw(enemies2[i].getEne());
    }
    for (int i = 0; i < NUM_OBSTACLES3; i++)
    {
        app.draw(obstacles[i]);
    }
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        app.draw(p1.getProjectiles()[i]);
    }

    p1.drawHealthAndDamage(app);

}


void Room3::handleInput()
{
        sf::Vector2f oldPosition = p1.getCircle().getPosition(); // Stocke l'ancienne position du joueur
        p1.update();
        p1.applyDamageRoom2(enemies, enemies2);

        // Vérification de la collision avec l'obstacle après les déplacements
        for (int i = 0; i < NUM_OBSTACLES3; i++)
        {
            // S'il y a collision, on réinitialise la position du cercle aux anciennes coordonnées
            if (isPlayerObstacle(p1.getCircle(),obstacles[i]))
            {
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
        if (p1.getCircle().getPosition().y + 2 * p1.getCircle().getRadius() >= doorToR2.getPosition().y &&
            p1.getCircle().getPosition().y <= doorToR2.getPosition().y + 50 &&
            p1.getCircle().getPosition().x <= doorToR2.getPosition().x + WALL_THICKNESS &&
            p1.getCircle().getPosition().x + 2 * p1.getCircle().getRadius() >= doorToR2.getPosition().x) {
                stateManager.setState(stateManager.getStateRoom2());
            if(stateManager.getCurrentState()== stateManager.getStateRoom2())
            {
                p1.getCircle().setPosition(WINDOW_WIDTH-100, WINDOW_HEIGHT/2);
            }

        }

        if (p1.getCircle().getPosition().y <= door.getPosition().y + WALL_THICKNESS && p1.getCircle().getPosition().x >= door.getPosition().x
        && p1.getCircle().getPosition().x + 2 * p1.getCircle().getRadius() <= door.getPosition().x + 50) {
        stateManager.setState(stateManager.getStateRoom4());

            if(stateManager.getCurrentState()== stateManager.getStateRoom4())
            {
                p1.getCircle().setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT - 20 );
            }
        }

        if (p1.getCircle().getPosition().y + 2 * p1.getCircle().getRadius() >= doorToR5.getPosition().y &&
            p1.getCircle().getPosition().y <= doorToR5.getPosition().y + 50 &&
            p1.getCircle().getPosition().x + 2 * p1.getCircle().getRadius() >= doorToR5.getPosition().x &&
            p1.getCircle().getPosition().x <= doorToR5.getPosition().x + WALL_THICKNESS) {
                stateManager.setState(stateManager.getStateRoom5());
            if(stateManager.getCurrentState()== stateManager.getStateRoom5())
            {
                p1.getCircle().setPosition(20,WINDOW_HEIGHT/2);
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

        for (int i = 0; i < MAX_PROJECTILES; ++i)
        {
            for (int j = 0; j < NUM_ENEMIES1_ROOM3; ++j)
            {
                if (isProjectileCollidingWithEnemy(p1.getProjectiles()[i], enemies[j].getEne()))
                {
                    p1.getProjectiles()[i].setPosition(-100, -100);
                    enemies[j].decreaseHealth(p1.getDamage()); // Dégâts infligés
                    if (!enemies[j].isAlive())
                    {
                        enemies[j].destroy();
                        numDeadEnemies1 += 1;
                    }
                }
            }
            for (int j = 0; j < NUM_ENEMIES2_ROOM3; ++j)
            {
                if (isProjectileCollidingWithEnemy(p1.getProjectiles()[i], enemies2[j].getEne()))
                {
                    p1.getProjectiles()[i].setPosition(-100, -100);
                    enemies2[j].decreaseHealth(p1.getDamage()); // Dégâts infligés
                    if (!enemies2[j].isAlive())
                    {
                        enemies2[j].destroy();
                        numDeadEnemies2 += 1;
                    }
                }
            }
        }

        if(numDeadEnemies1==NUM_ENEMIES1_ROOM3 && numDeadEnemies2==NUM_ENEMIES2_ROOM3)
        {
            obstacles[0].setPosition(-1000, -1000);
            obstacles[1].setPosition(-1000, -1000);
        }

    }

    for(int i=0;i<NUM_ENEMIES1_ROOM3;i++)
    {
        if (isPlayerCollidingWithEnemy(p1.getCircle(), enemies[i].getEne()))
        {
            enemies[i].moveOppositeDirection();
        }
    }

    for(int i=0;i<NUM_ENEMIES2_ROOM3;i++)
    {
        if (isPlayerCollidingWithEnemy(p1.getCircle(), enemies2[i].getEne()))
        {
            enemies2[i].moveOppositeDirection();
        }
    }

    for (int i = 0; i < NUM_ENEMIES1_ROOM3; i++)
    {
        for (int j = 0; j < NUM_OBSTACLES3; j++)
        {
            if (areRectanglesColliding(enemies[i].getEne(), obstacles[j]))
            {

                enemies[i].moveOppositeDirection();
            }
        }
    }

    for (int i = 0; i < NUM_ENEMIES2_ROOM3; i++)
    {
        for (int j = 0; j < NUM_OBSTACLES3; j++)
        {
            if (areRectanglesColliding(enemies2[i].getEne(), obstacles[j]))
            {
                enemies2[i].moveOppositeDirection();
            }
        }
    }

}

bool Room3::areRectanglesColliding(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
    sf::FloatRect rect1Bounds = rect1.getGlobalBounds();
    sf::FloatRect rect2Bounds = rect2.getGlobalBounds();


    return rect1Bounds.intersects(rect2Bounds);
}

void Room3::handleEnemyCollision(Enemy& ene1, Enemy& ene2)
{
    if (areRectanglesColliding(ene1.getEne(), ene2.getEne()))
    {
        // Déplacement des ennemis dans des directions opposées
        ene1.avoidCollision(ene2);
        ene2.avoidCollision(ene1);
    }
}

void Room3::handleEnemyCollision2(Enemy2& ene1, Enemy2& ene2)
{
    if (areRectanglesColliding(ene1.getEne(), ene2.getEne()))
    {
        // Déplacement des ennemis dans des directions opposées
        ene1.avoidCollision(ene2);
        ene2.avoidCollision(ene1);
    }
}

void Room3::handleEnemyCollision3(Enemy& ene1, Enemy2& ene2)
{
    if (areRectanglesColliding(ene1.getEne(), ene2.getEne()))
    {
        // Déplacement des ennemis dans des directions opposées
        ene1.avoidCollision2(ene2);
        ene2.avoidCollision2(ene1);
    }
}

bool Room3::isProjectileCollidingWithEnemy(const sf::CircleShape& projectile, const sf::RectangleShape& enemy)
{
    // Création d'une forme rectangulaire pour l'ennemi
    sf::FloatRect enemyBounds = enemy.getGlobalBounds();

    // Création d'une forme rectangulaire pour le projectile
    sf::FloatRect projectileBounds = projectile.getGlobalBounds();

    // Vérifie si les deux formes rectangulaires (ennemi et projectile) se chevauchent
    if (projectileBounds.intersects(enemyBounds)) {
        return true; // Collision détectée
    }

    return false; // Pas de collision
}

bool Room3::isPlayerObstacle(const sf::CircleShape& player, const sf::RectangleShape& obstacle)
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

bool Room3::isCollidingWithObstacle(float x, float y, float radius) {
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
bool Room3::isPlayerCollidingWithEnemy(const sf::CircleShape& player, const sf::RectangleShape& enemy)
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
