#ifndef TACOS_H
#define TACOS_H

#include <Items.h>

class Tacos : public Items
{
    private:
        sf::Sprite sprite;
        sf::Texture texture;
    public:
        Tacos(float x,float y);
        virtual ~Tacos();
        void statUps(Player& player,float nb);
        void testDraw(sf::RenderWindow& window);
        sf::Sprite& getSprite();

};

#endif // TACOS_H
