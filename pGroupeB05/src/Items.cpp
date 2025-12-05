#include "Items.h"

Items::Items()
{

}

Items::~Items()
{
    //dtor
}

void Items::destroyItemSprite(sf::Sprite& spr)
{
    spr.setPosition(-150,-150);
}

bool Items::isPlayerCollidingWithItem(const sf::CircleShape& player, const sf::Sprite itemSprite)
{
    // Calcule les coordonnées du centre du cercle du player
    float centerX = player.getPosition().x + player.getRadius();
    float centerY = player.getPosition().y + player.getRadius();

    // Calcule les coordonnées du rectangle de l'item (sprite)
    sf::FloatRect itemBounds = itemSprite.getGlobalBounds();

    // Calcule la distance la plus proche entre le centre du cercle du player et le rectangle de l'item
    float closestX = std::max(itemBounds.left, std::min(centerX, itemBounds.left + itemBounds.width));
    float closestY = std::max(itemBounds.top, std::min(centerY, itemBounds.top + itemBounds.height));

    // Calcule la distance entre le centre du cercle du player et le point le plus proche
    float distanceX = centerX - closestX;
    float distanceY = centerY - closestY;

    // Utilise le théorème de Pythagore pour calculer la distance réelle
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    // Si la distance est inférieure au rayon du cercle du player, il y a une collision
    if (distance < player.getRadius()) {
        return true; // Collision détectée
    }

    return false; // Pas de collision
}














