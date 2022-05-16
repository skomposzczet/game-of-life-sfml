#ifndef GOL_H
#define GOL_H

#include <SFML/Graphics.hpp>
#include <vector>

class Cell: sf::Drawable
{
public:
    Cell()
    {
        _rect.setFillColor(sf::Color::White);
        _rect.setOutlineColor(sf::Color::Black);
        _rect.setOutlineThickness(1.f);
    }
    enum {size = 15, isize = 14, bsize = 1};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {}

private:
    sf::RectangleShape _rect;
    bool alive = false;
};

class GameOfLife: public sf::Drawable
{
public:
    GameOfLife(const int x, const int y)
        : _width{x/Cell::size}, _height{Cell::size}
    {

        _matrix.reserve(_height);

        for (unsigned i = 0 ; i < _height ; ++i)
        {
            std::vector<Cell> temp;
            temp.reserve(_width);

            for (unsigned j = 0 ; j < _width ; ++j)
                temp.emplace_back(Cell());

            _matrix.push_back(temp);
        }
    }

private:
    const int _height;
    const int _width;
    std::vector<std::vector<Cell>> _matrix;
};

#endif // GOL_H
