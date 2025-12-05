#ifndef IRONARROWHEAD_H
#define IRONARROWHEAD_H

#include <Items.h>


class IronArrowhead : public Items
{
    private:
        sf::Sprite sprite;
        sf::Texture texture;
    public:
        IronArrowhead(float x,float y);
        virtual ~IronArrowhead();
        void statUps(Player& player,float nb);
        void testDraw(sf::RenderWindow& window);
        sf::Sprite& getSprite();

};

#endif // IRONARROWHEAD_H
