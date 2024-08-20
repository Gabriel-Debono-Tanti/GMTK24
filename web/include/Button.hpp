#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

class Button
{
private:
    SDL_Texture* tex;
    
public:
    SDL_Rect position, src;
    Button(SDL_Point dim, SDL_Point pos);
    void InitTex(const string &str, SDL_Renderer* ren){
        tex = IMG_LoadTexture(ren, str.c_str());
    }
    void setPosition(SDL_Point pos){
        position.x = pos.x; 
        position.y = pos.y;
    }
    void Render(SDL_Renderer* ren){
        SDL_RenderCopy(ren, tex, &src, &position);
    };
    void Destroy(){
        SDL_DestroyTexture(tex);
    }
    void Scale(float scalefactor){
        

        position.w = position.w * scalefactor;
        
        position.h =  position.h * scalefactor;
    }
    ~Button();
};

Button::Button(SDL_Point dim, SDL_Point pos)
{
     position = {pos.x, pos.y, dim.x, dim.y};
     src = {0,0, dim.x, dim.y};
}

Button::~Button()
{
}
