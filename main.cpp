#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "gol.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1290, 900), "GAME OF LIFE", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(10, 10));
    sf::Event event;
    window.setFramerateLimit(30);
    sf::Color color = sf::Color::Black;

    GameOfLife gol(1290, 900);

    while (window.isOpen())
    {
        window.clear(color);
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                gol.press(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
            }
            else if(event.type == sf::Event::MouseButtonReleased)
            {
                gol.unpress(event.mouseButton.button);
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (gol.pressed())
                    gol.move_mouse(event.mouseMove.x, event.mouseMove.y);
            }
        }

        window.draw(gol);
        window.display();
    }
}
