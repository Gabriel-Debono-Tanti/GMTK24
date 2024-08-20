#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Scene
{
private:
    
public:
    static int index;
    
    static bool changescene;
    static  SDL_Rect viewport;
    virtual void Init(SDL_Renderer* renderer){
        
    };
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual void Events(SDL_Event event) = 0;
    virtual void Update(SDL_Renderer* renderer) = 0;
    virtual void Destroy(){
        
    };
};

int Scene::index = 0;
bool Scene::changescene = false;
SDL_Rect Scene::viewport = {0,0,1200, 900};
