#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
SDL_Texture* UpdateText( std::string path, SDL_Renderer* renderer )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
void writeText(std::string t, int x, int y, TTF_Font* font, SDL_Color font_color, SDL_Renderer* renderer) {
  
 SDL_Surface *text_surface = TTF_RenderText_Solid(font, t.c_str(), font_color);
 SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
 SDL_Rect wrect = {x, y, text_surface->w, text_surface->h};
 SDL_FreeSurface(text_surface);
 SDL_RenderCopy(renderer, text_texture, NULL, &wrect);
 SDL_DestroyTexture(text_texture);
}