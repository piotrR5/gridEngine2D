#include <vector>
#include <SDL2/SDL.h>
#include <string>
#include "cell.hpp"
#include "parser.hpp"

#ifndef __GUI

#define __GUI

class Button{
public:
    float w,h,x,y;
    Button(): w(0), h(0), x(0), y(0) {}
    Button(float _w, float _h, float _x, float _y): w(_w), h(_h), x(_x), y(_y) {}
    std::string label;
    bool hovering=0;
    Button(std::string l): label(l) {}
    void setButton(float w, float h, float x, float y, std::string label);
};

class Gui_Container{
    float w,h,x,y;
    std::vector<Button>children;
    RGBA color, color_hover;
public:

    Gui_Container();
    Gui_Container( Config config);
    void add(Button o);

    void draw(SDL_Renderer* ren);

    ~Gui_Container();
};



#endif