#include "IronArrowhead.h"

IronArrowhead::IronArrowhead(float x,float y)
{
    texture.loadFromFile("Images/testItems.png");


    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    sprite.setPosition(x,y);
}

IronArrowhead::~IronArrowhead()
{
    //dtor
}

void IronArrowhead::statUps(Player& player,float nb)
{
    player.setDamage(nb);
//    setItemSprite(getItemSprite());
}

void IronArrowhead::testDraw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::Sprite& IronArrowhead::getSprite()
{
    return sprite;
}
