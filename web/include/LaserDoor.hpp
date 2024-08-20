#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

class LaserDoor
{
private:
    SDL_Texture* tex;
    SDL_Rect frame;
public:
    SDL_Rect position;
    bool active;
    LaserDoor(SDL_Point dim, SDL_Point pos);
    void InitTex(const string &str, SDL_Renderer* ren){
        tex = IMG_LoadTexture(ren, str.c_str());
    }
    void setPosition(SDL_Point pos){
        position.x = pos.x; 
        position.y = pos.y;
    }
    void update( bool setactivity){
        active = setactivity;
        if(!active){
            frame.y = frame.h;
        }
    }
    void Render(SDL_Renderer* ren){
        
        SDL_RenderCopy(ren, tex, &frame, &position);
      
       
    };
    void Destroy(){
        SDL_DestroyTexture(tex);
    }
    ~LaserDoor();
};

LaserDoor::LaserDoor(SDL_Point dim, SDL_Point pos)
{
    frame = {0,0,dim.x, dim.y};
     position = {pos.x, pos.y, dim.x, dim.y};
}

LaserDoor::~LaserDoor()
{
}
