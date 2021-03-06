#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <ctime>

#include "gol.hpp"

void start(bool& r, clock_t& tt, clock_t& lt)
{
    r = true;
    lt = tt = clock();
}

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(1290, 900), "GAME OF LIFE", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(10, 10));
    sf::Event event;
    window.setFramerateLimit(30);
    sf::Color color = sf::Color::Black;

    // to measure time
    bool running = false;
    double time_counter = 0;
    double interval = .5;
    clock_t this_time;
    clock_t last_time;

    GameOfLife gol(1290, 900);
    
    if(argc > 1)
        if (gol.import_layout(static_cast<std::string>(argv[1])));
            start(running, this_time, last_time);

    while (window.isOpen())
    {
        window.clear(color);
        
        while (window.pollEvent(event))
        {
            // closing window
            if (event.type == sf::Event::Closed) 
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                // single iteration
                else if (event.key.code == sf::Keyboard::Space)
                    gol.evolve();

                // continous simulation
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    if (!running)
                        start(running, this_time, last_time);
                    else
                        running = false;
                }

                // speeds up simulation
                else if (event.key.code == sf::Keyboard::RBracket)
                    interval /= 2;

                // slows down simulation
                else if (event.key.code == sf::Keyboard::LBracket)
                    interval *= 2;

                // resets grid (and simulation)
                else if (event.key.code == sf::Keyboard::R)
                {
                    running = false;
                    gol.clear();
                }

                // export to file
                else if (event.key.code == sf::Keyboard::E)
                    gol.export_layout();
            }
            
            /// start selecting
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                gol.press(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
            }
            // end selecting
            else if(event.type == sf::Event::MouseButtonReleased)
            {
                gol.unpress(event.mouseButton.button);
            }
            // move mouse while selecting
            else if (event.type == sf::Event::MouseMoved)
            {
                if (gol.pressed())
                    gol.move_mouse(event.mouseMove.x, event.mouseMove.y);
            }
        }

        // next iteration is called if simulation in on
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

        // drawing grid
        window.draw(gol);
        window.display();
    }
}
