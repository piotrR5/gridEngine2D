#include <vector>
#include <cstdint>
#include <cstdlib>
#include "cell.hpp"
#include <cmath>
#include <iostream>

#ifndef __GRID

#define __GRID

class Grid{
    std::vector<std::vector<Cell>>grid;
    uint16_t res;


public:
    /// @brief build an empty Grid object 
    Grid() : grid(std::vector<std::vector<Cell>>(0,std::vector<Cell>(0))), res(0) {}

    /// @brief build grid object using a 2D vector of Cells
    /// @param g
    Grid(std::vector<std::vector<Cell>>g) : grid(g), res(g.size()/2) {} 

    /// @brief build grid object of res _res and default 2D vector of cells
    /// @param _res
    Grid(uint16_t _res) : grid(std::vector<std::vector<Cell>>(_res*2,std::vector<Cell>(_res*3))), res(_res) {} 

    /// @brief returns reference to Grid object
    /// @return 
    std::vector<std::vector<Cell>>&getGrid() {return grid;}

    /**
    * sets grid resolution (only these will be implemented: 4,8,16,32,64,128).
    * resolution is to be understood as follows: 4 means there will be 6 (3x2) 4x4 cell squares on the grid.
    * @param x 
    * @param y 
    */
    void setRes(uint16_t s); 

    /**
     * @brief this function changes colors randomly
     * @param
    */
    void __debug__setRandomColor(uint64_t seed);

    /**
    * @brief returns resolution of the grid
    * @return 
    */
    uint16_t getRes() {return res;}
};



#endif
