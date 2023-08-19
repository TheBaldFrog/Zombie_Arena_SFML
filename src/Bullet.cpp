#include "Bullet.h"

Bullet::Bullet()
{
    m_BulletShape.setSize(sf::Vector2f(2, 2));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    float gradient = (startX - targetX) / (startY - targetY);
}