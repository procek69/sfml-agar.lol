#include "GameState.h"

GameState::GameState()
{
    player = new sf::CircleShape(10.f);
    player->setFillColor(sf::Color::Green);
    player->setRadius(10.f);
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    thread = new sf::Thread([=]() {
        while (backgroundThreadWorking)
        {
            if (currentLimit > minimumLimit)
            {
                currentLimit = currentLimit - 1;
                sf::sleep(sf::milliseconds(1000));
            }
        }
    });
    thread->launch();
    currentEnemies = 0;
    currentLimit = minimumLimit;
}

int GameState::init()
{
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "arial.ttf not found" << std::endl;
        return 1;
    }
    return 0;
}

void GameState::movePlayerTo(sf::Vector2f cursorPosition)
{
    int radius = player->getRadius();
    cursorPosition.x -= radius;
    cursorPosition.y -= radius;
    player->setPosition(cursorPosition);
}

void GameState::drawTo(sf::RenderWindow* window, sf::VideoMode* video)
{
    for (auto e : enemies) {
        if (!e->dirty)
            window->draw(*e);
    }

    if (lose)
    {
        window->setMouseCursorVisible(true);
        text.setString("You lose: " + std::to_string(points) + " points. Press ENTER to restart");
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        text.setPosition(sf::Vector2f(video->width / 2.f, video->height / 2.f));
        window->draw(text);
        return;
    }
    window->draw(*player);
}

void GameState::restart()
{
    lose = false;
    points = 0;
    for (auto e : enemies)
        delete e;
    enemies.clear();
    currentEnemies = 0;
    currentLimit = minimumLimit;
    player->setRadius(10.f);
}

GameState::~GameState()
{
    std::for_each(enemies.begin(), enemies.end(), deleter<Enemy>());
    delete player;
    enemies.clear();
    backgroundThreadWorking = false;
    thread->terminate();
    delete this->thread;
}

void GameState::calculate(sf::VideoMode* video)
{
    if (lose) return;
    if (currentEnemies < currentLimit)
    {
        Enemy* ed = nullptr;
        for (auto e : enemies)
        {
            if (e->dirty)
                ed = e;
        }
        if (ed != nullptr)
        {
            ed->dirty = false;
            ed->reset();
        }
        else
        {
            Enemy* e = new Enemy(video, player);
            e->reset();
            enemies.push_back(e);
        }
        currentEnemies++;
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        Enemy*& e = enemies[i];
        e->move();
        if (e->hit())
        {

            if (e->getRadius() >= player->getRadius())
            {
                lose = true;
            }
            else
            {
                points++;
                currentLimit++;
                if (currentLimit > maximumLimit)
                {
                    currentLimit = maximumLimit;
                }
                player->setRadius(player->getRadius() + 1);
            }
            e->dirty = true;
            currentEnemies--;
        }
        if (e->isOutside()) {
            e->dirty = true;
            currentEnemies--;
        }
    }
}