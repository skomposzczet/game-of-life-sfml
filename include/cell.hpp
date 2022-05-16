#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

/** Mode of selection */
enum class selection
{
    /** No selection */
    none, 
    
    /** Selection after which selected Cells will be killed */
    kill, 
    
    /** Selection after which selected Cells will be populated */
    populate
};

/**
 * @brief Class representing single Cell in game of life
 * 
 */
class Cell: public sf::Drawable
{
public:
    enum 
    {
        /** Size of whole Cell */
        size = 15, 

        /** Size of internal Cell ie withoud borders */
        isize = 14, 

        /** Thickness of Cells border */
        bsize = 1
    };

    /**
     * @brief Constructor for Cell object
     * 
     * @param i y index of Cell
     * @param j x index of Cell
     * @param alive Determines whether contructed Cell should be dead or alive, false is default
     */
    Cell(const int i, const int j, bool alive = false);

    /**
     * @brief Compares cells by their alive status
     * 
     * @param c Second Cell
     * @returns true if both are alive or both dead, false otherwise
     */
    bool operator==(const Cell& c) const
    {
        return _alive == c._alive;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(_rect);
    }

    /**
     * @brief Selects Cell
     * 
     * @param s mode in which Cell should be selected
     */
    void select(selection& s);

    /**
     * @brief Deselects Cell
     */
    void deselect();

    /**
     * @brief If Cell is selected applies selections action to it (ie. kills if its selected to be killed)
     * 
     */
    void apply();

    /**
     * @returns true if Cell is alive and false if dead 
     */
    bool is_alive() const
    {
        return _alive;
    }

    /**
     * @returns true if Cell is dead and false is alive 
     */
    bool is_dead() const
    {
        return !_alive;
    }

    /**
     * @brief Sets Cells status to dead, and colors it white
     */
    void kill()
    {
        _alive = false; 
        _rect.setFillColor(sf::Color::White);
    }

private:
    sf::RectangleShape _rect;
    bool _alive;

    selection _selected = selection::none;

    /**
     * @brief Calculates Cells position on screen based on its indexes
     * 
     * @param i y index 
     * @param j x index
     * @returns vector of two ints describing Cells position 
     */
    static sf::Vector2i get_position(const int i, const int j)
    {
        return sf::Vector2i(j * Cell::size, i * Cell::size);
    }
};

#endif // CELL_H
