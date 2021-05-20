#pragma once
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "deleter.h"
class GameState
{
	std::vector<Enemy*> enemies;
	bool lose;
	int points;
	int currentEnemies;
	int currentLimit;
	sf::CircleShape* player;
	sf::Font font;
	sf::Text text;
	bool backgroundThreadWorking = true;
	sf::Thread* thread;
	int minimumLimit = 10;
	int maximumLimit = 20;
public:
	void restart();
	void calculate(sf::VideoMode* video);
	void movePlayerTo(sf::Vector2f cursorPosition);
	void drawTo(sf::RenderWindow* window, sf::VideoMode* video);
	int init();
	GameState();
	~GameState();
};

