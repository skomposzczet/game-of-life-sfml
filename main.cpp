#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1290, 900), "GAME OF LIFE", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(10, 10));
    sf::Event event;
    window.setFramerateLimit(30);
    sf::Color color = sf::Color::Black;

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
        }

        window.display();
    }
}
