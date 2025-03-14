#include "Cell.hpp"
#include <iostream>

Cell::Cell()
{
    _mine = false;
    _discovered = false;
    _neighbours = 0;
}
Cell::~Cell()
{

}
void Cell::addMine(bool mine){
    _mine = mine; // ajouter un mine Si mine es true, la celda contendrá una mina. Si es false, la celda seguirá sin mina.
}
int Cell::get_neighbours(){
    return _neighbours; //Ahora devolverá el número correcto de minas vecinas. avant il retourné 0
}
void Cell::get_neighbours(std::vector<std::vector<Cell>> &grid, size_t x, size_t y)
{
    _neighbours = 0;
    if (_mine)
        return;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (x + i >= 0 && y + j >= 0 && x + i < grid.size() && y + j < grid[x + i].size())
            {
                if (grid[x + i][y + j].is_a_mine())
                    _neighbours++;
            }
        }
    }
}
bool Cell::is_discovered(){
    return _discovered;
}
bool Cell::is_a_mine(){
    return _mine;
}
bool Cell::discover(std::vector<std::vector<Cell>> &grid, size_t x, size_t y)
{
    if (is_a_mine())
        return true;
    _discovered = true;
    if (has_neighbours())
        return false;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if ((x + i >= 0) && (y + j >= 0) && (x + i < grid.size()) && (y + j < grid[x + i].size()))
            {
                if (!grid[x + i][y + j].is_a_mine() && !grid[x + i][y + j].is_discovered())
                    grid[x + i][y + j].discover(grid, x + i, y + j);
            }
        }
    }
    return false;
}
bool Cell::has_neighbours(){
    return _neighbours > 0;
}
bool Cell::is_flagged(){
    return _flagged;
}
void Cell::flag(){
    _flagged = true;
}