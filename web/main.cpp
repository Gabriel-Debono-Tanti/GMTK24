#include <SDL.h>
#include <stdio.h>
#include "include/MainScene.hpp"
#include "include/GameScene.hpp"
#include "include/Scene.hpp"
#include "include/pi.hpp"
#include "include/SettingsMenu.hpp"
#include "include/DataLoader.hpp"
#include "include/L2.hpp"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "include/LevelSelection.hpp"
#include "include/L1.hpp"
#include "include/L3.hpp"
#include "include/L4.hpp"
#include "include/L5.hpp"
#include "include/L6.hpp"
#include "include/L7.hpp"
#include "include/json.hpp"
#include <SDL_image.h>


#include <emscripten.h>


using namespace std;

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

Uint32 frameStart;
int frameTime;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;

SDL_Window* window;
SDL_Renderer* renderer;
bool isRunning = true;
vector<Scene*> scenes;
Scene* currentscene;
DisplaySettings ds;
DataLoader dl;
SoundSettings ss;

void main_loop() {
    frameStart = SDL_GetTicks();

    dl.LoadSoundSettings("soundsettings", ss);
    Mix_VolumeMusic(ss.musicvolume);

    if (currentscene->changescene) {
        scenes.clear();
        scenes = { new MainScene(), new SettingsMenu(), new LevelSelection(), new L1() , new L2(), new L3(), new L4(), new L5(), new L6(), new L7(), new GameScene() };
        currentscene = scenes[currentscene->index];
        currentscene->Init(renderer);
        currentscene->changescene = false;
    }

    SDL_UpdateWindowSurface(window);
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
        }
        currentscene->Events(e);
    }

    currentscene->Update(renderer);
    SDL_RenderClear(renderer);
    SDL_RenderSetViewport(renderer, &currentscene->viewport);
    currentscene->Render(renderer);
    SDL_RenderPresent(renderer);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }

    if (!isRunning) {
        emscripten_cancel_main_loop();

    }
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    window = SDL_CreateWindow("A Scaled Heist", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (ds.isFullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(window, 0);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    scenes = { new MainScene(), new SettingsMenu(), new LevelSelection(), new L1() , new L2(), new L3(), new L4(), new L5(), new L6(), new L7(), new GameScene() };
    currentscene = scenes[0]; // Initialize the first scene
    currentscene->Init(renderer);


    emscripten_set_main_loop(main_loop, 0, 1);

    while (isRunning) {
        main_loop();
    }


    for (Scene* scene : scenes) {
        scene->Destroy();
    }

    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();

    return 0;
}
