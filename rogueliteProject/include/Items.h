#ifndef ITEMS_H
#define ITEMS_H
#include <SFML/Graphics.hpp>
#include "Player.h"

class Items
{
    private:

    public:
        Items();
        virtual ~Items();
        void destroyItemSprite(sf::Sprite& srpou);
        bool isPlayerCollidingWithItem(const sf::CircleShape& player, const sf::Sprite itemSprite);
        virtual void statUps(Player& player,float nb)=0;
};

#endif // ITEMS_H
