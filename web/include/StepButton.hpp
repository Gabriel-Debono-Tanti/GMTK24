#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "player.hpp"
#include "PushableBlock.hpp"
using namespace std;

class StepButton
{
private:
    SDL_Texture* tex;
    SDL_Rect frame;
public:
SDL_Rect position;
bool set = true;
    StepButton(SDL_Point dim, SDL_Point pos);
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
    void Switch(vector<Block>& blocks){
        for(Block& block :blocks){
        if(SDL_HasIntersection(&position, &block.position)){
                set = false;
                frame.y = frame.h;
        }
        }
    }
    ~StepButton();
};

StepButton::StepButton(SDL_Point dim, SDL_Point pos)
{   
    frame = {0,0,dim.x, dim.y};
    position = {pos.x, pos.y, dim.x, dim.y};
}

StepButton::~StepButton()
{
}
