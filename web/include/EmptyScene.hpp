#pragma once
#include "Scene.hpp"


class EmptyScene : public Scene
{
private:
    /* data */
public:
    
    void Init(SDL_Renderer* renderer)override = 0;
     void Render(SDL_Renderer* renderer)override = 0;
     void Events(SDL_Event event)override = 0;
    void Update(SDL_Renderer* renderer)override = 0;
     void Destroy()override = 0;
    
};


