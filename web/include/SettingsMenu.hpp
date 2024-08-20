#pragma once
#include "Scene.hpp"
#include "Button.hpp"
#include "DataLoader.hpp"
#include <SDL_ttf.h>
#include "LoadTexture.hpp"
#include <SDL_mixer.h>
class SettingsMenu : public Scene
{
private:

    Button incvol = Button({32, 32}, {270, 550});
    Button decvol = Button({32, 32}, {220, 550});
    Button backbutton = Button({32, 32}, {100, 700});
    DataLoader loader;
    SoundSettings ss;
    SDL_Texture* Back;
    SDL_Rect backrect = {30,400,400, 400};
    TTF_Font* font;
    SDL_Color col = {255, 255, 255,255};
    bool lock_click = false;
    Mix_Music* Music = NULL;
    TilemapImporter tmp = TilemapImporter("res/Levels/test.json");
   vector<Tile> tiles1, tiles2;
    
public:
    SettingsMenu();
     ~SettingsMenu();
   void Init(SDL_Renderer* renderer)override;
     void Render(SDL_Renderer* renderer)override;
     void Events(SDL_Event event)override;
    void Update(SDL_Renderer* renderer)override{
        
        loader.SaveSoundSettings("soundsettings", ss); 
        
        
    };
     void Destroy()override{
        Mix_HaltMusic();
        decvol.Destroy();
        incvol.Destroy();
        backbutton.Destroy();
         for(auto& tile : tiles1){
            tile.Destroy();
        }
         for(auto& tile : tiles2){
            tile.Destroy();
        }
        SDL_DestroyTexture(Back);
         Mix_FreeMusic( Music );
     };
    
};


SettingsMenu::SettingsMenu(/* args */)
{
}

SettingsMenu::~SettingsMenu()
{
}

inline void SettingsMenu::Init(SDL_Renderer* renderer)
{ 
    Music = Mix_LoadMUS( "res/Music/OtherMenus.wav" );
    Mix_PlayMusic( Music, -1 );
    font = TTF_OpenFont("Fonts/HomeVideo-Regular.ttf", 36);
  
    
    incvol.InitTex("res/Textures/UpButton.png", renderer);
    decvol.InitTex("res/Textures/DownButton.png", renderer);
    backbutton.InitTex("res/Textures/BackButton.png", renderer);
    loader.LoadSoundSettings("soundsettings", ss);
  
    incvol.Scale(1.5);
    decvol.Scale(1.5);
    backbutton.Scale(1.5);
    Back = IMG_LoadTexture(renderer, "res/Textures/BackUI.png");
    tiles1 = tmp.TilemapBottomTiles(renderer);
    tiles2 =  tmp.TilemapTopTiles(renderer);
}

inline void SettingsMenu::Render(SDL_Renderer* renderer){
  for(auto& tile : tiles1){
            tile.Render(renderer);
        }
         for(auto& tile : tiles2){
            tile.Render(renderer);
        }
   SDL_RenderCopy(renderer, Back, NULL, &backrect);
    decvol.Render(renderer);
    incvol.Render(renderer);
    backbutton.Render(renderer);
    writeText(to_string(ss.musicvolume), 340, 560, font, col, renderer);
    writeText("Volume", 60, 560, font, col, renderer);
    writeText("Settings", 150, 450, font, col, renderer);
}

inline void SettingsMenu::Events(SDL_Event event)
{ 
    
     SDL_Point mousePosition;


        mousePosition.x = event.motion.x; 
        mousePosition.y = event.motion.y;
       if(SDL_PointInRect(&mousePosition, &backbutton.position)){
            if(event.button.button == SDL_BUTTON_LEFT && !lock_click){
                changescene = true;
                Destroy();
                index = 0;
            }
        }


        if(SDL_PointInRect(&mousePosition, &incvol.position)){
             if(event.button.button == SDL_BUTTON_LEFT && !lock_click){
                ss.musicvolume += 1;
        }   
         if(ss.musicvolume > 100)
            ss.musicvolume = 100;
        if(ss.musicvolume < 1)
            ss.musicvolume = 1;
        }
        if(SDL_PointInRect(&mousePosition, &decvol.position)){
             if(event.button.button == SDL_BUTTON_LEFT && !lock_click){
                ss.musicvolume -= 1;

        }
         if(ss.musicvolume > 100)
            ss.musicvolume = 100;
        if(ss.musicvolume < 1)
            ss.musicvolume = 1;
        }
                
            
       if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            lock_click = false;

       
       }
     
}
