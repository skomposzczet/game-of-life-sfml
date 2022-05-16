#include "cell.hpp"

Cell::Cell(const int i, const int j, bool alive)
    :_alive{alive}
{
    _rect.setSize(sf::Vector2f(static_cast<float>(Cell::isize), static_cast<float>(Cell::isize)));
    if (_alive)
        _rect.setFillColor(sf::Color::Green);
    else
        _rect.setFillColor(sf::Color::White);

    _rect.setOutlineColor(sf::Color::Black);
    _rect.setOutlineThickness(1.f);

    auto position = get_position(i, j);
    _rect.setPosition(position.x, position.y);
}

void Cell::select(selection& s)
{
    _selected = s;

    if (_selected == selection::populate)
        _rect.setFillColor(sf::Color::Blue);
    else if (_selected == selection::kill)
        _rect.setFillColor(sf::Color::Red);
}

void Cell::deselect()
{
    if (_selected != selection::none)
    {
        _selected = selection::none;
        _rect.setFillColor((_alive ? sf::Color::Green : sf::Color::White));
    }
}

void Cell::apply()
{
    if (_selected != selection::none)
    {
        if (_selected == selection::populate)
        {
            _alive = true;
            _rect.setFillColor(sf::Color::Green);
        }
        else if (_selected == selection::kill)
            kill();
    }
}