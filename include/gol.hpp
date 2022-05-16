#ifndef GOL_H
#define GOL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // debug

#include "cell.hpp"

/**
 * @brief Class for game of life, includes grid of Cells and simulation methods
 * 
 */
class GameOfLife: public sf::Drawable
{
public:
    /**
     * @brief Constructs a new GameOfLife object
     * 
     * @param x x size of window or area in which gol is to be displayed
     * @param y y size of window or area in which gol is to be displayed
     */
    GameOfLife(const int x, const int y);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Initiates selection
     * 
     * @param x x position of mouse
     * @param y y position of mouse
     * @param button Pressed mouse button, determines what type of selection is used 
     */
    void press(const int x, const int y, sf::Mouse::Button button);

    /**
     * @brief Finalizes selection
     * 
     * @param button Released mouse button, only correct will end selection (eg if selecting is in populate mode (left button used) only release of left button will stop selection)
     */
    void unpress(sf::Mouse::Button button);

    /**
     * @brief Widthens selection to current mouse position
     * 
     * @param x x position of moved mouse
     * @param y y position of moved mouse
     */
    void move_mouse(const int x, const int y);

    /**
     * @returns true if any selection mode is on, false if its none
     */
    bool pressed() const
    {
        return (_selecting == selection::none ? false : true);
    }

    /**
     * @brief Simulates single iteration of game
     * 
     * @returns true if game should stop ie if there is no more Cells alive or further iterations dont change arrangement of Cells (still lifes)
     */
    bool evolve();

    /**
     * @brief Resets game, kills all Cells
     */
    void clear();

private:
    const int _height;
    const int _width;
    std::vector<std::vector<Cell>> _matrix;

    selection _selecting = selection::none;
    sf::Vector2i _begin{-1,-1};
    sf::Vector2i _end{-1,-1};

    /**
     * @brief Determines whether Cell should be alive or dead in next iteration
     * 
     * @param i y index of examined Cell
     * @param j x index of examined Cell
     * @returns Cell with dead or alive status, depending on its current status and alive neighbours count 
     */
    Cell get_cell(const int i, const int j) const;

    /**
     * @brief Calculates how many alive neighbours are there around Cell. Periodic boundary conditions are used: first Cell in some row is adjacent to last Cell in the same row etc.
     * 
     * @param i y index of examined Cell
     * @param j x index of examined Cell
     * @returns neighbours count 
     */
    int count_neighbours(const int i, const int j) const;

    /**
     * @brief Checks for any alive Cells in game
     * 
     * @returns true if there is at least one alive Cell in game, false if there are none
     */
    bool anyone_left() const;
};

#endif // GOL_H
