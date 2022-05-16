#include "gol.hpp"

const std::vector<std::string> GameOfLife::presets{"gun"};

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

bool GameOfLife::evolve()
{
    std::vector<std::vector<Cell>> nm;
    nm.reserve(_height);

    for (unsigned i = 0 ; i < _height ; ++i)
    {
        std::vector<Cell> temp;
        temp.reserve(_width);

        for (unsigned j = 0 ; j < _width ; ++j)
            temp.emplace_back(get_cell(i, j));

        nm.push_back(temp);
    }

    if (_matrix == nm)
        return true;

    _matrix.swap(nm);
    if (!anyone_left())
        return true;

    return false;
}

Cell GameOfLife::get_cell(const int i, const int j) const
{
    int n = count_neighbours(i, j);
    const Cell& c = _matrix.at(i).at(j);

    if ((c.is_dead() && n == 3) || (c.is_alive() && (n == 2 || n == 3)))
        return Cell(i, j, true);
    else
        return Cell(i, j);

}

int GameOfLife::count_neighbours(const int i, const int j) const
{
    int result = 0;

    for (int di = -1 ; di < 2 ; ++di)
    {
        int index;
        if (i+di >= _height)
            index = 0;
        else if (i+di < 0)
            index = _height-1;
        else
            index = i+di;

        for (int dj = -1 ; dj < 2 ; ++dj)
        {
            if (di != 0 || dj != 0)
            {
                int jndex;
                if (j+dj >= _width)
                    jndex = 0;
                else if (j+dj < 0)
                    jndex = _width-1;
                else
                    jndex = j+dj;

                result += (_matrix.at(index).at(jndex).is_alive() ? 1 : 0);
            }
        }
    }

    return result;
}

bool GameOfLife::anyone_left() const
{
    for (unsigned i = 0 ; i < _height ; ++i)
        for (unsigned j = 0 ; j < _width ; ++j)
            if (_matrix.at(i).at(j).is_alive())
                return true;

    return false;
}

void GameOfLife::clear()
{
    for (unsigned i = 0 ; i < _height ; ++i)
        for (unsigned j = 0 ; j < _width ; ++j)
            _matrix.at(i).at(j).kill();
}

void GameOfLife::export_layout() const
{
    std::filesystem::path cwd = std::filesystem::current_path() / "out.txt";
    std::ofstream file(cwd.string());
    if (file.is_open())
    {
        for (unsigned i = 0 ; i < _height ; ++i)
            for (unsigned j = 0 ; j < _width ; ++j)
                if (_matrix.at(i).at(j).is_alive())
                    file << i << ' ' << j << "\n";
    }
}

bool GameOfLife::import_layout(std::string filename)
{
    std::filesystem::path filepath;
    std::ifstream file;

    for (auto& preset : presets)
    {
        if (preset == filename)
        {
            filename = getenv("HOME") + std::string{"/.game_of_life/presets/"} + filename;
            break;
        }
    }

    filepath = filename;
    file.open(filepath.string());
    if (!file.is_open())
    {
        filepath = std::filesystem::current_path() / filename;
        file.open(filepath.string());
        if (!file.is_open())
        {
            std::cerr << "Couldnt find file\n";
            return false;
        }
    }

    clear();
    for (std::string line ; getline(file, line) ; )
    {
        int i = stoi(line.substr(0, line.find_first_of(' ')));
        int j = stoi(line.substr(line.find_first_of(' ')+1, line.length()));

        if (i < _height && i >= 0 && j < _width && j >= 0)
            _matrix.at(i).at(j).populate();
    }

    return true;
}