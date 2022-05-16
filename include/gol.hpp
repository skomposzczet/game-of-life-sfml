#ifndef GOL_H
#define GOL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // debug

class Cell: public sf::Drawable
{
public:
    Cell(const int i, const int j)
    {
        _rect.setSize(sf::Vector2f(static_cast<float>(Cell::isize), static_cast<float>(Cell::isize)));
        _rect.setFillColor(sf::Color::White);
        _rect.setOutlineColor(sf::Color::Black);
        _rect.setOutlineThickness(1.f);

        auto position = get_position(i, j);
        _rect.setPosition(position.x, position.y);
    }
    enum {size = 15, isize = 14, bsize = 1};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(_rect);
    }

    void select()
    {
        _selected = true;
        _rect.setFillColor(sf::Color::Blue);
    }

    void deselect()
    {
        if (_selected)
        {
            _selected = false;
            _rect.setFillColor((alive ? sf::Color::Green : sf::Color::White));
        }
    }

    void apply()
    {
        if (_selected)
        {
            alive = true;
            _rect.setFillColor(sf::Color::Green);
        }
    }

private:
    sf::RectangleShape _rect;
    bool alive = false;

    bool _selected = false;

    static sf::Vector2i get_position(const int i, const int j)
    {
        return sf::Vector2i(j * Cell::size, i * Cell::size);
    }
};

class GameOfLife: public sf::Drawable
{
public:
    GameOfLife(const int x, const int y)
        : _width{x/Cell::size}, _height{y/Cell::size}
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

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (unsigned i = 0 ; i < _height ; ++i)
            for (unsigned j = 0 ; j < _width ; ++j)
                target.draw(_matrix.at(i).at(j));
    }

    void press(const int x, const int y)
    {
        _pressed = true;
        _begin.x = _end.x = x / Cell::size;
        _begin.y = _end.y = y / Cell::size;
        _matrix.at(_begin.y).at(_begin.x).select();
    }

    void unpress()
    {
        for (unsigned i = 0 ; i < _height ; ++i)
            for (unsigned j = 0 ; j < _width ; ++j)
                _matrix.at(i).at(j).apply();

        _pressed = false;
        _begin.x = _end.x = -1;
        _begin.y = _end.y = -1;
    }

    bool pressed() const
    {
        return _pressed;
    }

    void move_mouse(const int x, const int y)
    {
        _end.x = x / Cell::size;
        _end.y = y / Cell::size;

        for (unsigned i = 0 ; i < _height ; ++i)
            for (unsigned j = 0 ; j < _width ; ++j)
                if (((i >= _begin.y && i <= _end.y) || (i <= _begin.y && i >= _end.y)) && ((j >= _begin.x && j <= _end.x) || (j <= _begin.x && j >= _end.x)))
                    _matrix.at(i).at(j).select();
                else
                    _matrix.at(i).at(j).deselect();
    }

private:
    const int _height;
    const int _width;
    std::vector<std::vector<Cell>> _matrix;

    bool _pressed = false;
    sf::Vector2i _begin{-1,-1};
    sf::Vector2i _end{-1,-1};
};

#endif // GOL_H
