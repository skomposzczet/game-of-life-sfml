#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <ctime>

#include "gol.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1290, 900), "GAME OF LIFE", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(10, 10));
    sf::Event event;
    window.setFramerateLimit(30);
    sf::Color color = sf::Color::Black;

    double time_counter = 0;
    double interval = .5;

    bool running = false;
    clock_t this_time;
    clock_t last_time;

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
                else if (event.key.code == sf::Keyboard::Space)
                    gol.evolve();
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    if (!running)
                    {
                        running = true;
                        this_time = clock();
                        last_time = this_time;
                    }
                    else
                        running = false;
                }
                else if (event.key.code == sf::Keyboard::RBracket)
                    interval /= 2;
                else if (event.key.code == sf::Keyboard::LBracket)
                    interval *= 2;
                else if (event.key.code == sf::Keyboard::R)
                {
                    running = false;
                    gol.clear();
                }
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

        if (running)
        {
            this_time = clock();
            time_counter += static_cast<double>(this_time - last_time);
            last_time = this_time;

            if(time_counter > interval * CLOCKS_PER_SEC)
            {
                time_counter -= interval * CLOCKS_PER_SEC;
                if (gol.evolve())
                    running = false;
            }
        }

        window.draw(gol);
        window.display();
    }
}
