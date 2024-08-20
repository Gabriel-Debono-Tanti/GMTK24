#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

class CameraArea
{
private:
    SDL_Texture* tex;
    
public:
    SDL_Rect position;
    bool active;
    CameraArea(SDL_Point dim, SDL_Point pos);
    void InitTex(const string &str, SDL_Renderer* ren){
        tex = IMG_LoadTexture(ren, str.c_str());
    }
    void setPosition(SDL_Point pos){
        position.x = pos.x; 
        position.y = pos.y;
    }
    void update( bool setactivity){
        active = setactivity;
    }
    void Render(SDL_Renderer* ren){
        if(active){
             SDL_RenderCopy(ren, tex, NULL, &position);
        }else{
            position = {0,0,0,0};
        }
       
    };
    void Destroy(){
        SDL_DestroyTexture(tex);
    }
    ~CameraArea();
};

CameraArea::CameraArea(SDL_Point dim, SDL_Point pos)
{
     position = {pos.x, pos.y, dim.x, dim.y};
}

CameraArea::~CameraArea()
{
}
