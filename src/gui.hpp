#include <vector>
#include <SDL2/SDL.h>
#include <string>
#include "cell.hpp"
#include "parser.hpp"
#include <SDL2/SDL_ttf.h>

#ifndef __GUI

#define __GUI

class Button{    
public:
    float w,h,x,y;
    std::string text;
    SDL_Rect buttRect, textRect;
    SDL_Color textColor;
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* texture;


    Button(): w(0), h(0), x(0), y(0){}
    Button(float _w, float _h, float _x, float _y): w(_w), h(_h), x(_x), y(_y) {}
    bool hovering=0;
    Button(std::string l) {}

    void setButton(float w, float h, float x, float y, SDL_Renderer* renderer);
    void setText(std::string text, SDL_Renderer* renderer);

    ~Button();
};

class Gui_Container{
    float w,h,x,y;
    
    RGBA color, color_hover;
public:
    std::vector<Button>children;
    Gui_Container();
    Gui_Container( Config config);
    void add(Button o);

    void draw(SDL_Renderer* ren);

    ~Gui_Container();
};



#endif