#include <cstdlib>
#include <cstdint>
#include <SDL2/SDL_rect.h>
#include "constants.h"


#ifndef __CELL

#define __CELL

struct RGBA{
    uint8_t r,g,b,a;
};

class Cell{
    RGBA color;
    SDL_FRect rect;
    
public:
    /// @brief builds default Cell object (with color {0,0,0,0});
    Cell() : color({0,0,0,0}) {
        rect.h=0;
        rect.w=0;
        rect.x=0;
        rect.y=0;
    }
    /// @brief builds Cell object with color c
    /// @param c 
    Cell(RGBA c) : color(c) {
        rect.h=0;
        rect.w=0;
        rect.x=0;
        rect.y=0;
    }
    /// @brief  build Cell object with color c and rectangle r
    /// @param c 
    /// @param r 
    Cell(RGBA c, SDL_FRect r) : color(c) , rect(r) {}
    /// @brief returns reference to color
    /// @return 
    RGBA& getColor() {return color;}
    SDL_FRect& getRect() {return rect;}
};

#endif
