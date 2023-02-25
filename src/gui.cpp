#include "gui.hpp"

void Button::setButton(float w, float h, float x, float y, std::string label){
    this->w=w;
    this->h=h;
    this->x=x;
    this->y=y;
    this->label=label;
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
        SDL_FRect butt;
        butt.w=children[i].w;
        butt.h=children[i].h;
        butt.x=children[i].x + x;
        butt.y=children[i].y + y;
        if(children[i].hovering){
            SDL_SetRenderDrawColor(ren, color_hover.r, color_hover.g, color_hover.b, color_hover.a);
            SDL_RenderFillRectF(ren, &butt);
            
        }else{
            SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            SDL_RenderFillRectF(ren, &butt);
        }

        SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRectF(ren, &butt);
        
    }
    SDL_SetRenderDrawColor(ren, 0,0,0,255);
}

Gui_Container::~Gui_Container(){}