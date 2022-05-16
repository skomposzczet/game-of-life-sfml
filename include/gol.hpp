#ifndef GOL_H
#define GOL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // debug

#include "cell.hpp"

class GameOfLife: public sf::Drawable
{
public:
    GameOfLife(const int x, const int y);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void press(const int x, const int y, sf::Mouse::Button button);

    void unpress(sf::Mouse::Button button);

    void move_mouse(const int x, const int y);

    bool pressed() const
    {
        return (_selecting == selection::none ? false : true);
    }

    bool evolve();

    void clear();

private:
    const int _height;
    const int _width;
    std::vector<std::vector<Cell>> _matrix;

    selection _selecting = selection::none;
    sf::Vector2i _begin{-1,-1};
    sf::Vector2i _end{-1,-1};

    Cell get_cell(const int i, const int j) const;

    int count_neighbours(const int i, const int j) const;

    bool anyone_left() const;
};

#endif // GOL_H
