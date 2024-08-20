#pragma once
#include "Scene.hpp"
#include "Button.hpp"
#include "DataLoader.hpp"
#include "LoadTexture.hpp"

class LevelSelection : public Scene
{
private:
    Button L1 = Button({64,32}, {300, 820});
    Button L2 = Button({64,32}, {300, 740});
    Button L3 = Button({64,32}, {300, 660});
     Button L4 = Button({64,32}, {300, 580});
     Button L5 = Button({64,32}, {300, 500});
     Button L6 = Button({64,32}, {300, 420});
     Button L7 = Button({64,32}, {300, 340});
    DataLoader dl;
    GameData gd;
     Button backbutton = Button({32, 32}, {100, 700});
     TTF_Font* font;
     TTF_Font* font2;
     Mix_Music* Music = NULL;
public:
    
    void Init(SDL_Renderer* renderer)override{
         Music = Mix_LoadMUS( "res/Music/OtherMenus.wav" );
    Mix_PlayMusic( Music, -1 );
         font = TTF_OpenFont("res/Fonts/HomeVideo-Regular.ttf", 36);
         font2 = TTF_OpenFont("res/Fonts/HomeVideo-Regular.ttf", 60);
        dl.LoadGameData(1, gd);
        L1.InitTex("res/Textures/building.png", renderer);
        L2.InitTex("res/Textures/building.png", renderer);
         L3.InitTex("res/Textures/building.png", renderer);
          L4.InitTex("res/Textures/building.png", renderer);
          L5.InitTex("res/Textures/building.png", renderer);
           L6.InitTex("res/Textures/building.png", renderer);
          L7.InitTex("res/Textures/building.png", renderer);
         backbutton.InitTex("res/Textures/BackButton.png", renderer);
         backbutton.Scale(1.5);
        L1.src.x = 128;
        L1.src.y = 0;
        L7.src.x = 64;
        L7.src.x = 0;
        L1.Scale(2.5);
        L2.Scale(2.5);
        L3.Scale(2.5);
        L4.Scale(2.5);
        L5.Scale(2.5);
        L6.Scale(2.5);
        L7.Scale(2.5);
        if(gd.l2){
            L1.src.y = 32;
        }
        if(gd.l3){
            L2.src.y = 32;
        }
        if(gd.l4){
              L3.src.y = 32;
        }
         if(gd.l5){
              L4.src.y = 32;
        }
         if(gd.l6){
              L5.src.y = 32;
        }
           if(gd.l7){
              L6.src.y = 32;
        }
           if(gd.l8){
              L7.src.y = 32;
        }
    };
     void Render(SDL_Renderer* renderer)override{
        SDL_SetRenderDrawColor(renderer,4, 26,64, 255);
        L1.Render(renderer);
        L2.Render(renderer);
        L3.Render(renderer);
        L4.Render(renderer);
        L5.Render(renderer);
        L6.Render(renderer);
        L7.Render(renderer);
        backbutton.Render(renderer);
         writeText("Level 1",550, 830, font, {255, 255, 255,255}, renderer );
         
         if(gd.l2){
            writeText("Level 2",550, 750, font, {255, 255, 255,255}, renderer );
        }
        if(gd.l3){
            writeText("Level 3",550, 670, font, {255, 255, 255,255}, renderer );
        }
        if(gd.l4){
              writeText("Level 4",550, 590, font, {255, 255, 255,255}, renderer );
        }
         if(gd.l5){
              writeText("Level 5",550, 510, font, {255, 255, 255,255}, renderer );
        }
         if(gd.l6){
              writeText("Level 6",550, 430, font, {255, 255, 255,255}, renderer );
        }
           if(gd.l7){
              writeText("Level 7",550, 350, font, {255, 255, 255,255}, renderer );
        }
           if(gd.l8){
              writeText("Thanks for Playing!",250, 130, font2, {255, 255, 255,255}, renderer );
        }
     };
     void Events(SDL_Event event)override{
         SDL_Point mousePosition;


        mousePosition.x = event.motion.x; 
        mousePosition.y = event.motion.y;
          if(SDL_PointInRect(&mousePosition, &backbutton.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
                changescene = true;
                Destroy();
                index = 0;
            }
        }
        if(SDL_PointInRect(&mousePosition, &L1.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
                changescene = true;
                Destroy();
                index = 3;
            }
        }
         if(SDL_PointInRect(&mousePosition, &L2.position)){
            if(event.button.button == SDL_BUTTON_LEFT && gd.l2){
                changescene = true;
                Destroy();
                index = 4;
            }
        }
          if(SDL_PointInRect(&mousePosition, &L3.position)){
            if(event.button.button == SDL_BUTTON_LEFT && gd.l3){
                changescene = true;
                Destroy();
                index = 5;
            }
        }
         if(SDL_PointInRect(&mousePosition, &L4.position)){
            if(event.button.button == SDL_BUTTON_LEFT && gd.l4){
                changescene = true;
                Destroy();
                index = 6;
            }
        }
          if(SDL_PointInRect(&mousePosition, &L5.position)){
            if(event.button.button == SDL_BUTTON_LEFT && gd.l5){
                changescene = true;
                Destroy();
                index = 7;
            }
        }
         if(SDL_PointInRect(&mousePosition, &L6.position)){
            if(event.button.button == SDL_BUTTON_LEFT && gd.l6){
                changescene = true;
                Destroy();
                index = 8;
            }
        }
         if(SDL_PointInRect(&mousePosition, &L7.position)){
            if(event.button.button == SDL_BUTTON_LEFT && gd.l7){
                changescene = true;
                Destroy();
                index = 9;
            }
        }
     };
    void Update(SDL_Renderer* renderer)override{

    };
     void Destroy()override{
        L1.Destroy();
        L2.Destroy();
        L3.Destroy();
        L4.Destroy();
        L5.Destroy();
        L6.Destroy();
        L7.Destroy();
        backbutton.Destroy();
        Mix_FreeMusic(Music);
     };
    
};


