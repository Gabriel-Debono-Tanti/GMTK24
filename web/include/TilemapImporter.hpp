#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include "json.hpp" 
#include "Wall.hpp"
#include "Tile.hpp"
#include "PushableBlock.hpp"
#include "CameraArea.hpp"
using json = nlohmann::json;
using namespace std;
class TilemapImporter
{
private:
    int y = 0;
    int x = 0;
    json level;
    vector<SDL_Texture*> maptextures;
public:
    TilemapImporter(const string& filename);
    
    
    std::vector<Wall> TilemapWalls() {
        std::vector<Wall> walls;
        for(const auto& element : level["layers"][1]["objects"]){
            Wall wall(SDL_Point{element["width"], element["height"]}, SDL_Point{element["x"], element["y"]});
            walls.push_back(wall);
        }
        return walls;
    };
    std::vector<CameraArea> CameraAreas(SDL_Renderer* ren) {
        std::vector<CameraArea> CAreas;
        for(const auto& element : level["layers"][4]["objects"]){
            string filename = "res/Textures/camarea.png";
                
                
            CameraArea Cameraa(SDL_Point{element["width"], element["height"]}, SDL_Point{element["x"], element["y"]});
            Cameraa.InitTex(filename,ren);
          
            CAreas.push_back(Cameraa);
        }
        return CAreas;
    };
    vector<Tile> TilemapBottomTiles(SDL_Renderer* ren){
             vector<Tile> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][0]["data"]){
            int value = element.get<int>();
        
            if(posx == 1216){
                    posx = 0;
                    posy += 32;
                
            }
            if(value == 0){
                posx += 32;
            }
            if(value != 0){
                string filename = "res/Textures/" + to_string(value) + ".png";
                Tile tile({32, 32}, {posx, posy});
           
                tile.InitTex(filename,ren);
            
                
            
                tilemap.push_back(tile);
                posx += 32;  
            }
        }
        return tilemap; 
    }
     vector<Tile> TilemapTopTiles(SDL_Renderer* ren){
             vector<Tile> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][5]["data"]){
            int value = element.get<int>();
        
            if(posx == 1216){
                    posx = 0;
                    posy += 32;
                
            }
            if(value == 0){
                posx += 32;
            }
            if(value != 0){
                string filename = "res/Textures/" + to_string(value) + ".png";
                Tile tile({32, 32}, {posx, posy});
           
                tile.InitTex(filename,ren);
            
                
            
                tilemap.push_back(tile);
                posx += 32;  
            }
        }
        return tilemap; 
    }
    vector<Diamond> DiamondTiles(SDL_Renderer* ren){
             vector<Diamond> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][2]["data"]){
            int value = element.get<int>();
        
            if(posx == 1216){
                    posx = 0;
                    posy += 32;
                
            }
            if(value == 0){
                posx += 32;
            }
            if(value != 0){
                string filename = "res/Textures/Diamond.png";
                Diamond tile = Diamond({32, 32}, {posx, posy - 25});
           
                tile.InitTex(filename,ren);
            
                
            
                tilemap.push_back(tile);
                posx += 32;  
            }
        }
        return tilemap; 
    }
    vector<Block> Blocks(SDL_Renderer* ren){
             vector<Block> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][3]["data"]){
            int value = element.get<int>();
        
            if(posx == 1216){
                    posx = 0;
                    posy += 32;
                
            }
            if(value == 0){
                posx += 32;
            }
            if(value != 0){
                string filename = "res/Textures/block.png";
                Block tile = Block({21, 32}, {posx, posy});
           
                tile.InitTex(filename,ren);
            
                
            
                tilemap.push_back(tile);
                posx += 32;  
            }
        }
        return tilemap; 
    }
    vector<LaserDoor> LaserDoors(SDL_Renderer* ren){
             vector<LaserDoor> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][6]["data"]){
            int value = element.get<int>();
        
            if(posx == 1216){
                    posx = 0;
                    posy += 32;
                
            }
            if(value == 0){
                posx += 32;
            }
            if(value != 0){
                string filename = "res/Textures/laserdoor.png";
                LaserDoor tile = LaserDoor({31, 31}, {posx, posy});
           
                tile.InitTex(filename,ren);
            
                
            
                tilemap.push_back(tile);
                posx += 32;  
            }
        }
        return tilemap; 
    }
    
    ~TilemapImporter();
};


TilemapImporter::TilemapImporter(const string& filename)
{ 
    std::ifstream f(filename);
    level = json::parse(f);
    if (level.is_null()) {
        std::cerr << "Error: Failed to parse JSON file." << std::endl;
        return;
    }
}

TilemapImporter::~TilemapImporter()
{
}
