#include "Room7.h"

Room7::Room7(sf::RenderWindow& app,StateManager& stateManager,Player& p1): app(app),stateManager(stateManager),p1(p1)
{
    enemyTexture.loadFromFile("Images/BaseSlime.png");
    enemies.push_back(Enemy(400.0f, 100.0f, enemyTexture));
    enemies.push_back(Enemy(800.0f, 100.0f, enemyTexture));
    enemies.push_back(Enemy(1200.0f, 100.0f, enemyTexture));

}

Room7::~Room7()
{
}

void Room7::update()
{
    for (int i=0;i<NUM_ENEMIES;i++)
    {
        enemies[i].update(p1.getCircle().getPosition());
    }

    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        for (int j = i + 1; j < NUM_ENEMIES; j++)
        {
            handleEnemyCollision(enemies[i], enemies[j]);
        }
    }
}

void Room7::render()
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

    app.draw(p1.getCircle());

    for (int i=0;i<NUM_ENEMIES;i++)
    {
        if(enemies[i].getEne().getSize() == sf::Vector2f(40,40))
        {
            enemies[i].setSizeEne(160,160);
        }
        app.draw(enemies[i].getEne());
    }

    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        app.draw(p1.getProjectiles()[i]);
    }

    p1.drawHealthAndDamage(app);




}

void Room7::handleInput()
{
        sf::Vector2f oldPosition = p1.getCircle().getPosition(); // Stocke l'ancienne position du joueur
        p1.update();
        // Vérification de la collision avec l'obstacle après les déplacements

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
                        numDeadEnemies1 += 1;
                    }
                }
            }

        }

    }

    for(int i=0;i<NUM_ENEMIES;i++)
    {
        if (isPlayerCollidingWithEnemy(p1.getCircle(), enemies[i].getEne()))
        {
            enemies[i].moveOppositeDirection();
        }
    }


}

int Room7::getNumDeadBoss()
{
    return numDeadEnemies1;
}


bool Room7::areRectanglesColliding(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
    sf::FloatRect rect1Bounds = rect1.getGlobalBounds();
    sf::FloatRect rect2Bounds = rect2.getGlobalBounds();


    return rect1Bounds.intersects(rect2Bounds);
}

void Room7::handleEnemyCollision(Enemy& ene1, Enemy& ene2)
{
    if (areRectanglesColliding(ene1.getEne(), ene2.getEne()))
    {
        // Déplacement des ennemis dans des directions opposées
        ene1.avoidCollision(ene2);
        ene2.avoidCollision(ene1);
    }
}

bool Room7::isProjectileCollidingWithEnemy(const sf::CircleShape& projectile, const sf::RectangleShape& enemy)
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

bool Room7::isPlayerCollidingWithEnemy(const sf::CircleShape& player, const sf::RectangleShape& enemy)
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

bool Room7::gettmpRoom7()
{
    return tmpRoom7;
}

