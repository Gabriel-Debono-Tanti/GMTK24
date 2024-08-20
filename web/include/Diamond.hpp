#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include "Animation.hpp"
using namespace std;

class Diamond
{
private:
    SDL_Texture* tex;
    SDL_Rect frame;
    
    int speed = 100, frames = 1;
public:
 SDL_Rect position;
    Diamond(SDL_Point dim, SDL_Point pos);
    void InitTex(const string &str, SDL_Renderer* ren){
        tex = IMG_LoadTexture(ren, str.c_str());
        
    }
    void setPosition(SDL_Point pos){
        position.x = pos.x; 
        position.y = pos.y;
    }
    void Render(SDL_Renderer* ren){
        SDL_RenderCopy(ren, tex, &frame, &position);
    };
    void Destroy(){
        SDL_DestroyTexture(tex);
    }
    
    void Update(SDL_Renderer* ren, const Uint8* state){
        
       frame.x = frame.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

        
    }

    ~Diamond();
};

Diamond::Diamond(SDL_Point dim, SDL_Point pos)
{
     position = {pos.x, pos.y, dim.x, dim.y};
     frame = {0, 0, dim.x, dim.y};
}

Diamond::~Diamond()
{
}
