#include <cstdlib>
#include <cstdint>

#ifndef __CELL

#define __CELL

struct RGBA{
    uint8_t r,g,b,a;
};

class Cell{
    RGBA color;
public:
    /// @brief builds default Cell object (with color {0,0,0,0});
    Cell() : color({0,0,0,0}) {}
    /// @brief builds Cell object with color c
    /// @param c 
    Cell(RGBA c) : color(c) {}
    /// @brief returns reference to color
    /// @return 
    RGBA& getColor() {return color;}
};

#endif
