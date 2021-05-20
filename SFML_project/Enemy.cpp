#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::VideoMode* video, sf::CircleShape* player) : _video(video), _player(player)
{
    resetColor();
    dirty = false;
    velocity = 1.f;
    dx = 1;
    dy = 1;
}

bool Enemy::hit()
{
    if (dirty) return false;
    float distance = sqrt(pow(_player->getPosition().x + _player->getRadius() - getPosition().x - getRadius(), 2) + pow(_player->getPosition().y + _player->getRadius() - getPosition().y - getRadius(), 2));
    return getRadius() + _player->getRadius() > distance;
}

void Enemy::move()
{
	sf::Vector2<float> pos = getPosition();
	pos.x += dx * velocity;
	pos.y += dy * velocity;
	setPosition(pos);
}

void Enemy::reset()
{
    randRadius();
    resetPosition();
}

void Enemy::randRadius()
{
    setRadius(rand() % (int)_player->getRadius() + (int)(_player->getRadius() * 0.2));
}

void Enemy::resetPosition()
{
    const auto W = this->_video->width;
    const auto H = this->_video->height;
    this->velocity = 0.7f + (rand() % 20 / 10.f);
    const auto r = getRadius();
    sf::Vector2f start({ 0, 0 });
    sf::Vector2f end({ 0, 0 });
    if (rand() % 2)
    {
        start.x = r + rand() % (int)(W - 2 * r);
        end.x = r + rand() % (int)(W - 2 * r);
        start.y = r;
        end.y = H - r;
        if (rand() % 2)
        {
            std::swap(start.y, end.y);
        }
    }
    else
    {
        start.y = r + rand() % (int)(H - 2 * r);
        end.y = r + rand() % (int)(H - 2 * r);
        start.x = r;
        end.x = W - r;
        if (rand() % 2)
        {
            std::swap(start.x, end.x);
        }
    }

    sf::Vector2f dir = end - start;
    float length = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
    sf::Vector2f unit({ dir.x / length, dir.y / length });
    dx = unit.x;
    dy = unit.y;
    setPosition(start);
}

void Enemy::resetColor()
{
    ApplicationProperties ap;
    auto colors = ap.getColors();
    setFillColor(colors[rand() % colors.size()]);
}

bool Enemy::isOutside()
{
    const auto W = this->_video->width;
    const auto H = this->_video->height;
    const auto r = getRadius();
    const auto pos = getPosition();
    if (pos.x + 3 * r < 0) return true;
    if (pos.y + 3 * r < 0) return true;
    if (pos.x - 3 * r > W) return true;
    if (pos.y - 3 * r > H) return true;
    return false;
}
