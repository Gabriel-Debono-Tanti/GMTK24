#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

class Tile
{
private:
    SDL_Texture* tex;
    SDL_Rect position;
public:
    Tile(SDL_Point dim, SDL_Point pos);
    void InitTex(const string &str, SDL_Renderer* ren){
        tex = IMG_LoadTexture(ren, str.c_str());
    }
    void setPosition(SDL_Point pos){
        position.x = pos.x; 
        position.y = pos.y;
    }
    void Render(SDL_Renderer* ren){
        SDL_RenderCopy(ren, tex, NULL, &position);
    };
    void Destroy(){
        SDL_DestroyTexture(tex);
    }
    ~Tile();
};

Tile::Tile(SDL_Point dim, SDL_Point pos)
{
     position = {pos.x, pos.y, dim.x, dim.y};
}

Tile::~Tile()
{
}
