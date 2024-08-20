#pragma once
#include <map>
#include <SDL.h>
using namespace std;
struct Animation
{
    int vertspace;
    int index;
    int frames;
    int speed;
    Animation(){}
    Animation(int i, int f, int s){
        index = i;
        frames = f;
        speed = s;
    }
    
};





