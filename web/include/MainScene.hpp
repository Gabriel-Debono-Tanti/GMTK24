#pragma once
#include "Scene.hpp"
#include "Button.hpp"
#include <SDL_mixer.h>
#include "TilemapImporter.hpp"
class MainScene : public Scene
{
private:
    Button ToGame = Button({128, 64}, {450, 530});
    Button ToSettings = Button({128, 64}, {450, 700});
   TilemapImporter tmp = TilemapImporter("res/Levels/test.json");
   vector<Tile> tiles1, tiles2;
    Mix_Music* Music = NULL;
    SDL_Texture* tex;
    SDL_Rect pos = {350, 130, 121*4, 90*4};
public:
     MainScene();
     ~MainScene();
    void Init(SDL_Renderer* renderer) override;
    void Render(SDL_Renderer* renderer) override;
     void Update(SDL_Renderer* ren) override{};
    void Events(SDL_Event event) override ;
    void Destroy() override{
       Mix_HaltMusic();
        ToGame.Destroy();
        ToSettings.Destroy();
        for(auto& tile : tiles1){
            tile.Destroy();
        }
         for(auto& tile : tiles2){
            tile.Destroy();
        }
       
          Mix_FreeMusic( Music );
          SDL_DestroyTexture(tex);
    };
};


MainScene::MainScene(/* args */)
{
}

MainScene::~MainScene()
{
}

void MainScene::Render(SDL_Renderer* renderer)
{
  //  SDL_SetRenderDrawColor(renderer,0, 255,0, 255);
     for(auto& tile : tiles1){
            tile.Render(renderer);
        }
         for(auto& tile : tiles2){
            tile.Render(renderer);
        }
    ToGame.Render(renderer);
    ToSettings.Render(renderer);
    SDL_RenderCopy(renderer, tex, NULL, &pos);
    

 }
 inline void MainScene::Events(SDL_Event event)
 { 
    
    SDL_Point mousePosition;


        mousePosition.x = event.motion.x; 
        mousePosition.y = event.motion.y;
        if(SDL_PointInRect(&mousePosition, &ToSettings.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
                changescene = true;
                Destroy();
                index = 1;
            }
        }
       
        if(SDL_PointInRect(&mousePosition, &ToGame.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
                changescene = true;
                Destroy();
                index = 2;
            }
        }
   
 }
 void MainScene::Init(SDL_Renderer* renderer)
 {
   Music = Mix_LoadMUS( "res/Music/MainMenu.wav" );
    Mix_PlayMusic( Music, -1 );
   ToGame.InitTex("res/Textures/start.png",renderer);
    ToGame.Scale(2);
   ToSettings.InitTex("res/Textures/settings.png",renderer);
   ToSettings.Scale(2);
  tiles1 = tmp.TilemapBottomTiles(renderer);
    tiles2 =  tmp.TilemapTopTiles(renderer);
    tex = IMG_LoadTexture(renderer, "res/Textures/Title.png");
}
