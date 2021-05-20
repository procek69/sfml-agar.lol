#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class ApplicationProperties
{
	std::vector<sf::Color> colors;
	void init();
public:
	std::vector<sf::Color> getColors();
};

namespace Globals
{
	void init();
}