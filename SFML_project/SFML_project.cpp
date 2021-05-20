#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Enemy.h"
#include "Application.h"
#include "GameState.h"

#define WIDTH 1024
#define HEIGHT 768
#define ENTER_KEY 13

int main()
{
    Globals::init();
    GameState gs;
    if (gs.init()) {
        return 1;
    }
    sf::VideoMode video(WIDTH, HEIGHT);
    sf::RenderWindow window(video, "agar.lol clone");
    window.setMouseCursorVisible(false);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.key.code == ENTER_KEY)
            {
                gs.restart();
                window.setMouseCursorVisible(false);
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        gs.movePlayerTo(worldPos);

        gs.calculate(&video);
        window.clear();
        gs.drawTo(&window, &video);
        
        window.display();
    }
    return 0;
}