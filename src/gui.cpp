#include "gui.hpp"

void Button::setButton(float w, float h, float x, float y, SDL_Renderer* renderer){
    TTF_Init();
    this->w=w;
    this->h=h;
    this->x=x;
    this->y=y;

    font=TTF_OpenFont("assets/fonts/OpenSans-Light.ttf", 24);
    textColor={255,255,255,255};
    buttRect.w=w;
    buttRect.h=h;
    buttRect.x=x+1152;
    buttRect.y=y;

    surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_Quit();
}

Button::~Button(){

}

Gui_Container::Gui_Container(){

}

Gui_Container::Gui_Container(Config config){
    x=config.at<int>("SCREEN_WIDTH")-config.at<int>("MENU_WIDTH");
    y=config.at<int>("SCREEN_HEIGHT")-config.at<int>("MENU_HEIGHT");
    w=config.at<int>("MENU_WIDTH");
    h=config.at<int>("MENU_HEIGHT");
    color=config.at<RGBA>("gui_color");
    color_hover=config.at<RGBA>("gui_color_hover");
}

void Gui_Container::add(Button o){
    children.push_back(o);
}

void Gui_Container::draw(SDL_Renderer* ren){
    for(size_t i=0;i<children.size();i++){
        SDL_Rect butt;
        butt.w=children[i].w;
        butt.h=children[i].h;
        butt.x=children[i].x + x;
        butt.y=children[i].y + y;

        if(children[i].hovering){
            SDL_SetRenderDrawColor(ren, color_hover.r, color_hover.g, color_hover.b, color_hover.a);
            SDL_RenderFillRect(ren, &butt);
            
        }else{
            SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(ren, &butt);
        }

        SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(ren, &butt);   

        SDL_RenderCopy(ren, children[i].texture, NULL, &children[i].buttRect);     
    }
    SDL_SetRenderDrawColor(ren, 0,0,0,255);
}

Gui_Container::~Gui_Container(){}