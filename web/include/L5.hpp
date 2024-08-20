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
#include "DataLoader.hpp"
#include "StepButton.hpp"
#include "Lever.hpp"
using namespace std;
class L5 : public Scene
{
private:
     player p = player( {13, 25}, {14*32, 24*32},2);
     TilemapImporter tmp = TilemapImporter("res/Levels/l5.json");
     vector<Tile> tiles, toptiles;
     vector<Wall> walls;
     vector<Diamond> diamonds;
     vector<Block> blocks;
     vector<CameraArea> careas;
     vector<LaserDoor> ldoors;
    const Uint8* currentKeyStates;
    DataLoader dl;
    GameData gd;
   StepButton button = StepButton({32, 32}, {128, 16*32});
    Lever lev = Lever({15, 25}, {34*32,8*32});
public:
 L5(/* args */);
    ~L5();
    void Render(SDL_Renderer* ren) override;
    void Events(SDL_Event event) override{
         SDL_Point mousePosition;
          

        mousePosition.x = event.motion.x; 
        mousePosition.y = event.motion.y;
       if(SDL_PointInRect(&mousePosition, &p.Back.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
                changescene = true;Destroy();
                
                index = 2;
                
            }
        }
        if(SDL_PointInRect(&mousePosition, &p.Restart.position)){
            if(event.button.button == SDL_BUTTON_LEFT){
           
                  changescene = true;Destroy();
                   
                    index = index;        
            }    
                    
            }
        
    
    };
      void Init(SDL_Renderer* ren) override;
      void Update(SDL_Renderer* ren) override{
          const Uint8* state = SDL_GetKeyboardState(NULL);
          lev.Switch(p, state);
          button.Switch(blocks);
          ldoors[0].update(button.set);
          ldoors[1].update(lev.set);
            for(CameraArea& carea : careas){
              carea.update(true);
            }
            
          if(p.caught){
            
                 changescene = true;Destroy();
                  
                    index = index;
            
            }
            if(p.diamondscount == p.alldiamonds){
              gd.l6 = true;
              dl.SaveGameData(1, gd);
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
    for(auto& ld : ldoors){
      ld.Destroy();
    }
    button.Destroy();
    lev.Destroy();
    };
    
};


L5::L5()
{
}

L5::~L5()
{
}
void L5::Init(SDL_Renderer* ren)
{ 
  lev.InitTex("res/Textures/lever.png", ren);
  button.InitTex("res/Textures/PushButton.png", ren);
  p.InitTex("res/Textures/player-Sheet.png",ren);
  tiles = tmp.TilemapBottomTiles(ren);
  toptiles = tmp.TilemapTopTiles(ren);
  walls = tmp.TilemapWalls();
  diamonds = tmp.DiamondTiles(ren);
  blocks = tmp.Blocks(ren);
  careas = tmp.CameraAreas(ren);
  ldoors = tmp.LaserDoors(ren);
  p.alldiamonds = 2;
  dl.LoadGameData(1, gd);
}
void L5::Render(SDL_Renderer* ren)
{ 
    SDL_SetRenderDrawColor(ren,0, 0, 0,255);
    
    for (auto& tile : tiles)
    {
      tile.Render(ren);
    }
    lev.Render(ren);
   button.Render(ren);
     for(auto& block : blocks){
        block.Render(ren);
      }
    for(auto& ld : ldoors){
      ld.Render(ren);
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