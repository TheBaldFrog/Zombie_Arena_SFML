#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
    // Settings
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    float timeIntervalHit = 200;
    float hitDamange = 10;
    float speedIncreasePercent = .2f;  // 20%
    float healthIncreasePercent = .2f; // 20%
    //------------------------------

    Vector2f m_Position;
    Sprite m_Sprite;
    Texture m_Texture;

    // screen resolution
    Vector2f m_Resolution;
    IntRect m_Arena;
    int m_TileSize;
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;

    // player health
    int m_Health;
    int m_MaxHealth;

    Time m_LastHit;

    // Speed in pixels per second
    float m_Speed;

public:
    Player();

    void spawn(IntRect arena, Vector2f resolution, int tileSize);

    void resetPlayerStats();

    // Handle the player getting hit by a zombie
    bool hit(Time timeHit);

    // How long ago was the player last hit
    Time getLastHitTime();

    FloatRect getPosition();

    // get venter of the player
    Vector2f getCenter();

    // What angle is the player facing
    float getRotation();

    Sprite getSprite();

    // move the player
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    // ---------------

    // We will call this function once every frame
    void update(float elapsedTime, Vector2f mousePosition);

    // Give the player a speed boost
    void upgradeSpeed();

    void upgradeHealth();

    // Increase the maximum amount of health the player can have
    void increaseHealthLevel(int amount);

    int getHealth();
};
