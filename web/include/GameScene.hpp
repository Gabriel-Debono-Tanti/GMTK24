#pragma once
#include "Scene.hpp"
#include "LoadTexture.hpp"
#include "player.hpp"
#include "TilemapImporter.hpp" 
#include "Tile.hpp"
#include <iostream>
#include <vector>
#include "Diamond.hpp"
#include "PushableBlock.hpp"
#include "CameraArea.hpp"
using namespace std;
class GameScene : public Scene
{
private:
     player p = player( {13, 25}, {200, 200},1);
     TilemapImporter tmp = TilemapImporter("res/Levels/test.json");
     vector<Tile> tiles, toptiles;
     vector<Wall> walls;
     vector<Diamond> diamonds;
     vector<Block> blocks;
     vector<CameraArea> careas;
     vector<LaserDoor> ldoors;
    const Uint8* currentKeyStates;

public:
 GameScene(/* args */);
    ~GameScene();
    void Render(SDL_Renderer* ren) override;
    void Events(SDL_Event event) override{
         SDL_Point mousePosition;

        mousePosition.x = event.motion.x; 
        mousePosition.y = event.motion.y;
       if(SDL_PointInRect(&mousePosition, &p.Back.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
                changescene = true;
                Destroy();
                index = 3;
                
            }
        }
        if(SDL_PointInRect(&mousePosition, &p.Restart.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
          
                  changescene = true;
                    Destroy();
                    index = index;    
            }        
            }
        
      if(event.button.button == SDL_BUTTON_RIGHT){
              changescene = true;
                index = 0;
 
            }
    };
      void Init(SDL_Renderer* ren) override;
      void Update(SDL_Renderer* ren) override{
          const Uint8* state = SDL_GetKeyboardState(NULL);
          if(p.caught){
            p.Screen(true);
            if (p.screenpos.x == p.maxscreen)
            {
                 changescene = true;
                    Destroy();
                    index = index;
            }
            }
          p.handleWallCollisions(walls, diamonds, ren, careas, ldoors);
          p.Update(ren, state);
          p.Screen(false);
          for(auto& block : blocks){
            block.handleWallCollisions(walls, p);
          }
      };
      void Destroy() override{
        p.Destroy();
        for (auto& tile : tiles)
        {
          tile.Destroy();
        }
        for (auto& tile : toptiles)
    {
      tile.Destroy();
    }
        for (auto& d : diamonds){
          d.Destroy();
        }
      for(auto& block : blocks){
        block.Destroy();
      }
       for (auto& carea : careas)
    {
      carea.Destroy();
    }
    };
    
};


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}
void GameScene::Init(SDL_Renderer* ren)
{ 
  
  p.InitTex("./Textures/player-Sheet.png",ren);
  tiles = tmp.TilemapBottomTiles(ren);
  toptiles = tmp.TilemapTopTiles(ren);
  walls = tmp.TilemapWalls();
  diamonds = tmp.DiamondTiles(ren);
  blocks = tmp.Blocks(ren);
  careas = tmp.CameraAreas(ren);
  p.alldiamonds = 1;
}
void GameScene::Render(SDL_Renderer* ren)
{ 
    SDL_SetRenderDrawColor(ren,0, 0, 0,255);
    
    for (auto& tile : tiles)
    {
      tile.Render(ren);
    }
     for(auto& block : blocks){
        block.Render(ren);
      }
    p.Render(ren);
    for (auto& carea : careas)
    {
      carea.Render(ren);
    }
    for (auto& tile : toptiles)
    {
      tile.Render(ren);
    }
     for (auto& d : diamonds){
      d.Render(ren);
    }
     p.UI(ren);
    
}