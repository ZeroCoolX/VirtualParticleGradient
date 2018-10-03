#include<iostream>
#include<SDL2/SDL.h>

using namespace std;

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO)  < 0){
        cout << "SDL failed to initialize" << endl;
        return -1;
    }

    cout << "SDL Initialized successfully" << endl;

    SDL_Quit();

    return 0;
}
