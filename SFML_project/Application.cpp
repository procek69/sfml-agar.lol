#include "Application.h"

void ApplicationProperties::init()
{
	if (colors.size() > 0) return;
	colors.push_back(sf::Color(255, 204, 0));
	colors.push_back(sf::Color(51, 204, 204));
	colors.push_back(sf::Color(153, 51, 102));
	colors.push_back(sf::Color(153, 204, 0));
	colors.push_back(sf::Color(0, 204, 255));
	colors.push_back(sf::Color(255, 128, 128));
}

std::vector<sf::Color> ApplicationProperties::getColors()
{
	init();
	return colors;
}

void Globals::init()
{
	srand(time(nullptr));
}