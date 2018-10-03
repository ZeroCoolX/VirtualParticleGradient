#include<iostream>
#include<SDL2/SDL.h>
#include <mem.h>

using namespace std;

int main(int argc, char* argv[]){
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    if(SDL_Init(SDL_INIT_VIDEO)  < 0){
        cout << "SDL failed to initialize" << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
                                          "Particle Emitter",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if(window == NULL){
        cout << "Could not create SDL window: " << SDL_GetError() << endl;
        SDL_Quit();
        return 2;
    }

    // SDL refreshes from top left hand corner to bottom right at max FPS
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        cout << "Could not create renderer" << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }
                                                            // uses 1 byte / pixel      write pixels directly
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(texture == NULL){
        cout << "Could not create texture" << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }

    // must allocate enough memory for each pixel on the screen
    Uint32 *buffer = new  Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

    // Initialize a block of memory with the same value
    memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i){
            // RRGGBBAA
        buffer[i] = 0xFF00FFFF;
    }

    // draw to the screen
    SDL_UpdateTexture(texture, NULL, buffer, /*number of bytes per row of pixels*/ SCREEN_WIDTH*sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;

    while(!quit){
        // update particles
        // draw particles
        // check for messages/events
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){ // raised by user clicking the X in the window corner
                quit = true;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete [] buffer;
    return 0;
}
