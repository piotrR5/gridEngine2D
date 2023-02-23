#include <vector>
#include <iostream>
#include "grid.hpp"
#include "cell.hpp"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>

#ifndef __ENGINE

#define __ENGINE

#define MENU_WIDTH 300
#define MENU_HEIGHT SCREEN_HEIGHT
#define SCREEN_WIDTH 1152 + MENU_WIDTH // 300 is the place for the menu
#define SCREEN_HEIGHT 786

class Engine{
    uint8_t fps=60;
    uint8_t desiredDT=1000/fps;
    Grid g;
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    /**
     * @return
     * @brief returns reference to grid of the engine
    */
    Grid& getGrid() {return g;}
    /**
     * @return
     * @brief returns set fps
    */
    int getFps() {return fps;}
    /**
     * @return
     * @brief sets given fps
     * @param f
    */
    void setFps(uint8_t _fps) {fps=_fps; desiredDT=1000/_fps;}

    /**
     * @brief function handles events and changes [run] to false if program is to be exited
    */
    void eventHandler(bool& run);

    /**
     * @brief function stores the main program loop, primary and periodic logic is done inside
    */
    bool mainLoop();

    /**
     * @brief function draws the grid on a designated place
    */
    void drawGrid();

    Engine();

    ~Engine();
}; 

#endif
