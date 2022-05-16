#ifndef GOL_H
#define GOL_H

#include <SFML/Graphics.hpp>
#include <vector>

class Cell: sf::Drawable
{
public:
    Cell(const int i, const int j)
    {
        _rect.setFillColor(sf::Color::White);
        _rect.setOutlineColor(sf::Color::Black);
        _rect.setOutlineThickness(1.f);

        auto position = get_position(i, j);
        _rect.setPosition(position.x, position.y);
    }
    enum {size = 15, isize = 14, bsize = 1};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {}

private:
    sf::RectangleShape _rect;
    bool alive = false;

    static sf::Vector2i get_position(const int i, const int j)
    {
        return sf::Vector2i(j * Cell::size, i * Cell::size);
    }
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
                temp.emplace_back(Cell(i, j));

            _matrix.push_back(temp);
        }
    }

private:
    const int _height;
    const int _width;
    std::vector<std::vector<Cell>> _matrix;
};

#endif // GOL_H
