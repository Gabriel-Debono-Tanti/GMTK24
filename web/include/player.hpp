#pragma once
#include  <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include "Wall.hpp"
#include <vector>
#include "Animation.hpp"
#include "Diamond.hpp"
#include <algorithm>
#include "LoadTexture.hpp"
#include <SDL_ttf.h>
#include <iostream>
#include "CameraArea.hpp"
#include <time.h>
#include "LaserDoor.hpp"
using namespace std;
class player
{
private:
    SDL_Texture* tex, *screen;
   
    SDL_Texture* Diamonds;
    SDL_Rect frame;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    
    map<const char*, Animation> ani;
    int movespeed;
    int index, speed, frames;
    Mix_Music* Music = NULL;
public:
bool caught = false;
    SDL_Rect position;  
    SDL_Rect screenpos = {0,0,1200,900};
    bool scaleddown = false;
    int diamondscount = 0;
    int alldiamonds;
    int maxscreen =0, minscreen = -1200;
    TTF_Font* font;
      Button Back = Button({32, 32}, {850,10});
    Button Restart = Button({32, 32}, {950, 10});
    
    player(SDL_Point dim, SDL_Point pos, int speed);
    void Update(SDL_Renderer* ren, const Uint8* state){
        
             frame.x = frame.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        frame.y = index * frame.h;
        
            
        
      if(diamondscount != alldiamonds ){
        if (state[SDL_SCANCODE_W]) {
            position.y -= movespeed;
            Setanimation("Walk");
        }
        else if (state[SDL_SCANCODE_S]) {
            position.y += movespeed;
            Setanimation("Walk");
        }
        else if (state[SDL_SCANCODE_A]) {
            position.x -= movespeed;
            flip = SDL_FLIP_HORIZONTAL;
            Setanimation("Walk");
        }
        else if (state[SDL_SCANCODE_D]) {
            position.x += movespeed;
            flip = SDL_FLIP_NONE;
            Setanimation("Walk");
        }
        
        else{
           if(state[SDL_SCANCODE_1]){
            if(!scaleddown){
                position.w *= .5;
                position.h *= .5;
                scaleddown = true;
            
                Setanimation("Scale");
            
            }
            
            
        }
        else if(state[SDL_SCANCODE_2]){
            if (scaleddown){
                position.w *= 2;
                position.h *= 2;
                scaleddown=false;
                 
                Setanimation("Scale");
            
            }
        
        }else
            Setanimation("Idle");
        };
      }else{
            Setanimation("Finish");
            
        } 
        



    };
    
    void InitTex(const std::string &str, SDL_Renderer* ren){
        tex = IMG_LoadTexture(ren, str.c_str());
        screen = IMG_LoadTexture(ren, "res/Textures/screen.png");
        Diamonds = IMG_LoadTexture(ren, "Textures/Diamond.png");
        font = TTF_OpenFont("res/Fonts/HomeVideo-Regular.ttf", 36);
          Back.InitTex("res/Textures/BackButton.png", ren);
           Back.Scale(1.5);
         Restart.InitTex("res/Textures/RestartButton.png", ren);
           Restart.Scale(1.5);
            Music = Mix_LoadMUS( "res/Music/GameMusic.wav" );
    Mix_PlayMusic( Music, -1 );
    }
    void setPosition(SDL_Point pos){
        position.x = pos.x; 
        position.y = pos.y;
    }
    void Render(SDL_Renderer* ren){
        SDL_RenderCopyEx(ren, tex, &frame, &position,0,  NULL, flip);
       
    };
    void Screen(bool closed){
        if(closed){
            if(screenpos.x < maxscreen){
                screenpos.x += 30;
            }
        }else{
            if(screenpos.x > minscreen){
                screenpos.x -= 30;
            }
        }
    }
    void UI(SDL_Renderer* ren){
         SDL_Rect DFrame = {0,0,32,32};
        SDL_Rect DPosition = {50,20,32,32};
        SDL_RenderCopy(ren, Diamonds, &DFrame, &DPosition);
        writeText(to_string(diamondscount).c_str(),100,20, font, {255, 255, 255,255}, ren );
        Back.Render(ren);
        Restart.Render(ren);
        SDL_RenderCopy(ren, screen, NULL, &screenpos);
        if(diamondscount == alldiamonds){
            writeText("Level Complete! ",450, 400, font, {255, 255, 255,255}, ren );
             writeText("Go back to Level Selection.",350, 450, font, {255, 255, 255,255}, ren );
        }
    };
    void Destroy(){
        SDL_DestroyTexture(tex);
        SDL_DestroyTexture(Diamonds);
        SDL_DestroyTexture(screen);
        Back.Destroy();
        Restart.Destroy();
        Mix_FreeMusic(Music);
        Music = NULL;
        
    }
    void Setanimation( const char* aniname){
        
         frames = ani[aniname].frames;
         index = ani[aniname].index;
         speed = ani[aniname].speed;
    };
    
     void handleWallCollisions(const std::vector<Wall>& walls, std::vector<Diamond>& diamonds,  SDL_Renderer* ren, vector<CameraArea>& careas, vector<LaserDoor> & ldoors);
    ~player();
};

player::player( SDL_Point dim, SDL_Point pos, int speed)
{
    movespeed = speed;
    Animation idle = Animation(0, 4, 100);
    Animation walk = Animation(1, 4, 100);
    Animation Finish = Animation(2, 4, 100);
    Animation scale = Animation(3, 4, 10);
    ani.emplace("Idle", idle);
    ani.emplace("Walk", walk);
    ani.emplace("Finish", Finish);
    ani.emplace("Scale", scale);
    
    frame = {0, 0, dim.x, dim.y}; // Assuming each frame size is 32x32
    position = {pos.x, pos.y, dim.x*2, dim.y*2};
    Setanimation( "Idle");
}

player::~player()
{
}

 void player::handleWallCollisions(const std::vector<Wall>& walls,  std::vector<Diamond>& diamonds, SDL_Renderer* ren, vector<CameraArea>& careas,  vector<LaserDoor> & ldoors) {
         
       
        for (const Wall& wall : walls) {
            
            if (SDL_HasIntersection(&position, &wall.Wallbox)) {
               SDL_Rect overlap;
            SDL_IntersectRect(&position, &wall.Wallbox, &overlap);

            if (overlap.w < overlap.h) {
                if (position.x < wall.Wallbox.x) {
                    position.x -= overlap.w + 0.1f;
                } else {
                    position.x += overlap.w - 0.1f;
                }
            } else {
                if (position.y < wall.Wallbox.y) {
                    position.y -= overlap.h;
                } else {
                    position.y += overlap.h;
                }
            }
            }
        }
        for ( Diamond& diam : diamonds) {
            if(SDL_HasIntersection(&position, &diam.position) && !scaleddown){
                diam.Destroy();
                auto it = find_if(diamonds.begin(), diamonds.end(), [&diam](const Diamond& s) { return &s == &diam; });
                 diamonds.erase(it);
                diamondscount++;
            }
        }
         for (const CameraArea& carea : careas) {
            if(SDL_HasIntersection(&position, &carea.position)){
                if(!scaleddown && carea.active){
                    
                  
                  caught = true;
                    
                    
                }

            }

         }
          for (const LaserDoor& carea : ldoors) {
            if(SDL_HasIntersection(&position, &carea.position)){
                if(!scaleddown && carea.active){
                    
                  
                  caught = true;
                    
                    
                }

            }

         }
       
        
       
    }