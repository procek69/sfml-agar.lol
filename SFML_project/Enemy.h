#pragma once

#include <SFML/Graphics.hpp>
#include "Application.h"

class Enemy : public sf::CircleShape
{
public:
    float dx;
    float dy;
    float velocity;
    bool dirty;
    sf::VideoMode* _video;
    sf::CircleShape* _player;
    Enemy(sf::VideoMode* video, sf::CircleShape* player);

    bool isOutside();
    bool hit();
    void move();
    void reset();
private:
    void randRadius();
    void resetPosition();
    void resetColor();
};