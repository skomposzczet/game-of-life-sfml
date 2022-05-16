#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

enum class selection{none, kill, populate};

class Cell: public sf::Drawable
{
public:
    enum {size = 15, isize = 14, bsize = 1};

    Cell(const int i, const int j);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(_rect);
    }

    void select(selection& s);

    void deselect();

    void apply();

private:
    sf::RectangleShape _rect;
    bool _alive = false;

    selection _selected = selection::none;

    static sf::Vector2i get_position(const int i, const int j)
    {
        return sf::Vector2i(j * Cell::size, i * Cell::size);
    }
};

#endif