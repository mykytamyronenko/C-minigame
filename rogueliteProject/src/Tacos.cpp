#include "Tacos.h"

Tacos::Tacos(float x,float y)
{
    texture.loadFromFile("Images/testItems2.png");


    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    sprite.setPosition(x,y);
}

Tacos::~Tacos()
{
    //dtor
}

void Tacos::statUps(Player& player,float nb)
{
    player.setLife(nb);
}

void Tacos::testDraw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::Sprite& Tacos::getSprite()
{
    return sprite;
}
