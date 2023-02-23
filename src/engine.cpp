#include "engine.hpp"

#ifdef __linux__ 
    //linux code goes here
    void clearConsole(){
        system("clear");
    }
#elif _WIN32
    // windows code goes here
    void clearConsole(){
        system("cls");
    }
#else

#endif

Engine::Engine(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
    renderer=SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);    

    g=Grid(32);

    srand(time(NULL));

    for(auto& i:g.getGrid()){
        for(auto& j:i){
            //uint8_t r=(uint8_t)rand()%256,g=(uint8_t)rand()%256,b=(uint8_t)rand()%256;
            uint8_t r=255/2, g=255/2, b=255/2;
            j.getColor()=RGBA{r, g, b, 255};
        }
    }
    

    mainLoop();
}

Engine::~Engine(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Engine::eventHandler(bool& run){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            run = false;
            std::cout << "Quitting!\n";
            break;
        
        break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_q:{
                    run = false;
                    std::cout << "Quitting!\n";
                    break;
                }
                break;
            }
            printf( "Key press detected\n" );
            break;

        case SDL_KEYUP:
            printf( "Key release detected\n" );
            break;
        }
    }
}

bool Engine::mainLoop(){
    bool run=true;

    while(run){
        int startLoop=SDL_GetTicks();
        SDL_RenderClear(renderer);
        /*
            event handling
        */
        eventHandler(run);


        /**
         * draw here
        */
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH-MENU_WIDTH-1, 0, SCREEN_WIDTH-MENU_WIDTH, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH-MENU_WIDTH+1, 0, SCREEN_WIDTH-MENU_WIDTH+1, SCREEN_HEIGHT);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);

        
        

        drawGrid();
        g.__debug__setRandomColor(SDL_GetTicks64());



        SDL_RenderPresent(renderer);
        int dT = SDL_GetTicks64() - startLoop;
        if(desiredDT-dT)std::cout<<"[fps: "<<1000/abs(desiredDT+dT)<<"]\n";
        else std::cout<<"[fps: "<<fps<<"]\n";
        if(dT<desiredDT){
            SDL_Delay(desiredDT-dT);
        }
        //clearConsole();
    }

    return 0;
}


void Engine::drawGrid(){
    int16_t res=g.getRes();
    
    double cellSize=(double)SCREEN_HEIGHT/(2*res);

    for(size_t y=0;y<g.getGrid().size();y++){
        for(size_t x=0; x<g.getGrid()[0].size(); x++){
            SDL_FRect cell;
            cell.h=cellSize;
            cell.w=cellSize;
            cell.x=x*cellSize;
            cell.y=y*cellSize;
            RGBA c=g.getGrid()[y][x].getColor();
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
            SDL_RenderFillRectF(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        }
    }
}

