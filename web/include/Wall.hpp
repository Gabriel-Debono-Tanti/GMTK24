#pragma once
#include "SDL.h"

class Wall
{
private:
    
public:
SDL_Rect Wallbox;
    Wall(SDL_Point size, SDL_Point position) {
        Wallbox.x = position.x;
        Wallbox.y = position.y;
        Wallbox.w = size.x;
        Wallbox.h = size.y;
        };
    
    
};

