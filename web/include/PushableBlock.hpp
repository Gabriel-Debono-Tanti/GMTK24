#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "player.hpp"
#include "Wall.hpp"
using namespace std;

class Block
{
private:
    SDL_Texture* tex;
    
public:
    SDL_Rect position;
    Block(SDL_Point dim, SDL_Point pos);
    void InitTex(const string &str, SDL_Renderer* ren){
        tex = IMG_LoadTexture(ren, str.c_str());
    }
    void setPosition(SDL_Point pos){
        position.x = pos.x; 
        position.y = pos.y;
    }
    void Render(SDL_Renderer* ren){
        SDL_RenderCopy(ren, tex, NULL, &position);
    };
    void Destroy(){
        SDL_DestroyTexture(tex);
    }
     void handleWallCollisions(const std::vector<Wall>& walls, player& p) {
         
       
         for (const Wall& wall : walls) {
        // Get the bounding boxes of the position and the wall
        SDL_Rect wallBounds = wall.Wallbox;
        
        // Check if the position's rectangle intersects with the wall's rectangle
        SDL_Rect overlap;
        if (SDL_IntersectRect(&position, &wallBounds, &overlap)) {
            if (overlap.w < overlap.h) {
                // Horizontal collision
                if (position.x < wallBounds.x) {
                    position.x -= overlap.w - 1;  // Move left
                } else {
                    position.x += overlap.w - 1;  // Move right
                }
            } else {
                // Vertical collision
                if (position.y < wallBounds.y) {
                    position.y -= overlap.h;  // Move up
                } else {
                    position.y += overlap.h;  // Move down
                }
            }
        }
    }
   if (SDL_HasIntersection(&position, &p.position)) {
        SDL_Rect overlap;
        SDL_IntersectRect(&position, &p.position, &overlap);

        if (!p.scaleddown) {
            // When the player is not scaled down, adjust the block's position
            if (overlap.w < overlap.h) {
                if (position.x < p.position.x) {
                    position.x -= overlap.w + 0.1f;
                } else {
                    position.x += overlap.w - 0.1f;
                }
            } else {
                if (position.y < p.position.y) {
                    position.y -= overlap.h;
                } else {
                    position.y += overlap.h;
                }
            }
        } else {
            // When the player is scaled down, keep the block stationary and move the player instead
            if (overlap.w < overlap.h) {
                if (p.position.x < position.x) {
                    p.position.x -= overlap.w ; // Move player back to the left
                } else {
                    p.position.x += overlap.w; // Move player back to the right
                }
            } else {
                if (p.position.y < position.y) {
                    p.position.y -= overlap.h; // Move player back up
                } else {
                    p.position.y += overlap.h; // Move player back down
                }
            }
        }
    }
}
    ~Block();
};

Block::Block(SDL_Point dim, SDL_Point pos)
{
     position = {pos.x, pos.y, dim.x, dim.y};
}

Block::~Block()
{
}
