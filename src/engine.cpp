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
    config.parseConfig("config.cfg");

    //window=SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
    window=SDL_CreateWindow(
        config.at<string>("ENGINE_NAME").c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        config.at<int>("SCREEN_WIDTH"), 
        config.at<int>("SCREEN_HEIGHT"), 
        SDL_WINDOW_SHOWN); 

    renderer=SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* icon = IMG_Load("assets/icons/icon.png");
    SDL_SetWindowIcon(window, icon);
    delete icon;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);    

    g=Grid(1);

    srand(time(NULL));

    for(auto& i:g.getGrid()){
        for(auto& j:i){
            //uint8_t r=(uint8_t)rand()%256,g=(uint8_t)rand()%256,b=(uint8_t)rand()%256;
            uint8_t r=255/2, g=255/2, b=255/2;
            j.getColor()=RGBA{r, g, b, 255};
        }
    }

    guiSetup();

    mainLoop();
}

Engine::~Engine(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Engine::guiSetup(){
    gui=Gui_Container(config);
    Button test(100,50, 100,50);
    Button test2(100,50, 100,500);
    gui.add(test);
    gui.add(test2);
}


void Engine::eventHandler(bool& run){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            run = false;
            std::cout << "Quitting!\n";
            config.saveConfig("config.cfg");
            break;
        
        break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_q:{
                    run = false;
                    std::cout << "Quitting!\n";
                    config.saveConfig("config.cfg");
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

    g.setRes(config.at<int>("RESOLUTION"));

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
        SDL_RenderDrawLine(renderer, config.at<int>("SCREEN_WIDTH")-config.at<int>("MENU_WIDTH"), 0, config.at<int>("SCREEN_WIDTH")-config.at<int>("MENU_WIDTH"), config.at<int>("SCREEN_HEIGHT"));
        SDL_RenderDrawLine(renderer, config.at<int>("SCREEN_WIDTH")-config.at<int>("MENU_WIDTH")+1, 0, config.at<int>("SCREEN_WIDTH")-config.at<int>("MENU_WIDTH")+1, config.at<int>("SCREEN_HEIGHT"));
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);

        
        
        drawGrid();
        g.__debug__setRandomColor(SDL_GetTicks64());


        gui.draw(renderer);

        SDL_RenderPresent(renderer);


        /**
         * 
        */



        //clearConsole();
        int dT = SDL_GetTicks64() - startLoop;
        std::cout<<"[fps: "<<1000/(double)(dT+0.001)<<"]\n";
        if(dT<desiredDT){
            SDL_Delay(desiredDT-dT);
        }
    }

    return 0;
}


void Engine::drawGrid(){
    for(size_t y=0;y<g.getGrid().size();y++){
        for(size_t x=0; x<g.getGrid()[0].size(); x++){
            RGBA c=g.getGrid()[y][x].getColor();
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
            SDL_RenderFillRectF(renderer, &(g.getGrid()[y][x].getRect()));
        }
    }
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

