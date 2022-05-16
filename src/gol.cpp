#include "gol.hpp"

GameOfLife::GameOfLife(const int x, const int y)
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

void GameOfLife::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned i = 0 ; i < _height ; ++i)
        for (unsigned j = 0 ; j < _width ; ++j)
            target.draw(_matrix.at(i).at(j));
}

void GameOfLife::press(const int x, const int y, sf::Mouse::Button button)
{
    if(_selecting != selection::none)
        return;

    _selecting = (button == sf::Mouse::Left ? selection::populate : selection::kill);
    _begin.x = _end.x = x / Cell::size;
    _begin.y = _end.y = y / Cell::size;
    _matrix.at(_begin.y).at(_begin.x).select(_selecting);
}

void GameOfLife::unpress(sf::Mouse::Button button)
{
    if (_selecting == selection::populate && button == sf::Mouse::Left || _selecting == selection::kill && button == sf::Mouse::Right)
    {
        for (unsigned i = 0 ; i < _height ; ++i)
            for (unsigned j = 0 ; j < _width ; ++j)
                _matrix.at(i).at(j).apply();

        _selecting = selection::none;
        _begin.x = _end.x = -1;
        _begin.y = _end.y = -1;
    }
}

void GameOfLife::move_mouse(const int x, const int y)
{
    _end.x = x / Cell::size;
    _end.y = y / Cell::size;

    for (unsigned i = 0 ; i < _height ; ++i)
        for (unsigned j = 0 ; j < _width ; ++j)
            if (((i >= _begin.y && i <= _end.y) || (i <= _begin.y && i >= _end.y)) && ((j >= _begin.x && j <= _end.x) || (j <= _begin.x && j >= _end.x)))
                _matrix.at(i).at(j).select(_selecting);
            else
                _matrix.at(i).at(j).deselect();
}