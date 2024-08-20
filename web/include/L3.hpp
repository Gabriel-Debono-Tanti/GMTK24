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
class L3 : public Scene
{
private:
     player p = player( {13, 25}, {3*32, 16*32},2);
     TilemapImporter tmp = TilemapImporter("res/Levels/l3.json");
     vector<Tile> tiles, toptiles;
     vector<Wall> walls;
     vector<Diamond> diamonds;
     vector<Block> blocks;
     vector<CameraArea> careas;
     vector<LaserDoor> ldoors;
    const Uint8* currentKeyStates;
    DataLoader dl;
    GameData gd;
    StepButton button = StepButton({32, 32}, {32*13, 32*6});
    StepButton button2 = StepButton({32, 32}, {32*23, 32*4});
    Lever lev = Lever({15, 25}, {31*32, 12*32});
public:
 L3(/* args */);
    ~L3();
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
            button2.Switch(blocks);
            careas[0].update(lev.set);
            ldoors[0].update(button2.set);
            ldoors[1].update(button.set);
            cout << p.caught << endl;
          if(p.caught){
            
                 changescene = true;Destroy();
               
                    index = index;
            
            }
            if(p.diamondscount == p.alldiamonds){
              gd.l4 = true;
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
    button2.Destroy();
    lev.Destroy();
    };
    
};


L3::L3()
{
}

L3::~L3()
{
}
void L3::Init(SDL_Renderer* ren)
{ 
  lev.InitTex("res/Textures/lever.png", ren);
  button.InitTex("res/Textures/PushButton.png", ren);
  button2.InitTex("res/Textures/PushButton.png", ren);
  p.InitTex("res/Textures/player-Sheet.png",ren);
  tiles = tmp.TilemapBottomTiles(ren);
  toptiles = tmp.TilemapTopTiles(ren);
  walls = tmp.TilemapWalls();
  diamonds = tmp.DiamondTiles(ren);
  blocks = tmp.Blocks(ren);
  careas = tmp.CameraAreas(ren);
  ldoors = tmp.LaserDoors(ren);
  p.alldiamonds = 1;
  dl.LoadGameData(1, gd);
}
void L3::Render(SDL_Renderer* ren)
{ 
    SDL_SetRenderDrawColor(ren,0, 0, 0,255);
    
    for (auto& tile : tiles)
    {
      tile.Render(ren);
    }
    lev.Render(ren);
    button.Render(ren);
    button2.Render(ren);
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