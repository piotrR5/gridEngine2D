#include "grid.hpp"

void Grid::setUpGrid(){
    config.parseConfig("config.cfg");
    GRID_HEIGHT=config.at<int>("SCREEN_HEIGHT");
    GRID_WIDTH=config.at<int>("SCREEN_WIDTH")-config.at<int>("MENU_WIDTH");
}


Cell cellAvg(std::vector<Cell>cells){
    double colorAvg[4];

    for(auto c:cells){
        colorAvg[0]+=c.getColor().r;
        colorAvg[1]+=c.getColor().g;
        colorAvg[2]+=c.getColor().b;
        colorAvg[3]+=c.getColor().a;
    }

    for(size_t i=0;i<4;i++)colorAvg[i]/=cells.size();

    uint8_t r,g,b,a;

    r=(uint8_t)colorAvg[0];
    g=(uint8_t)colorAvg[1];
    b=(uint8_t)colorAvg[2];
    a=(uint8_t)colorAvg[3];

    return Cell(RGBA{r,g,b,a});
}

void Grid::setRes(uint16_t s){
    if(s==res)return;

    bool shrink(s<res);

    if(res==0){
        grid=std::vector<std::vector<Cell>>(s*2, std::vector<Cell>(s*3, Cell(RGBA(), SDL_FRect())));
    }else if(shrink){
        std::vector<std::vector<Cell>>newGrid(std::vector<std::vector<Cell>>(s*2, std::vector<Cell>(s*3, Cell())));
        uint16_t ratio=res/s;
        for(size_t i=0;i<grid.size();i+=ratio){
            for(size_t j=0;j<grid[0].size();j+=ratio){
                std::cout<<"["<<i<<" "<<j<<"\n";
                std::cout<<"["<<grid.size()<<" "<<grid[0].size()<<"\n";
                std::vector<Cell>cellVector;
                for(size_t p=0;p<ratio;p++){
                    for(size_t q=0;q<ratio;q++){
                        cellVector.push_back(grid[i+p][j+q]);
                        newGrid[i/ratio][j/ratio]=cellAvg(cellVector);
                    }
                }
            }
        }

        grid=newGrid;


    }else{
        std::vector<std::vector<Cell>>newGrid(std::vector<std::vector<Cell>>(s*2, std::vector<Cell>(s*3, Cell())));
        uint16_t ratio=s/res;
        for(size_t i=0;i<grid.size();i++){
            for(size_t j=0;j<grid[0].size();j++){
                for(size_t p=0;p<ratio;p++){
                    for(size_t q=0;q<ratio;q++){
                        newGrid[ratio*i+p][ratio*j+q]=grid[i][j];
                    }
                }
            }
        }

        grid=newGrid;
    }

    res=s;

    double cellSize=((double)GRID_HEIGHT)/(2*res);

    for(size_t y=0;y<grid.size();y++){
        for(size_t x=0; x<grid[0].size(); x++){
            grid[y][x].getRect().h=cellSize;
            grid[y][x].getRect().w=cellSize;
            grid[y][x].getRect().x=x*cellSize;
            grid[y][x].getRect().y=y*cellSize;
        }
    }
}

void Grid::__debug__setRandomColor(uint64_t seed){

    double x=-sin(seed/500.0)*cos(seed/500.0)*2;

    for(auto &i:grid){
        for(auto &j:i){

            RGBA tempC=j.getColor();
            
            tempC.r+=(int8_t)(rand()%2*x*2);
            tempC.g+=(int8_t)(rand()%2*x*2);
            tempC.b+=(int8_t)(rand()%2*x*2);

            j.getColor()=tempC;
        }
    }
}
