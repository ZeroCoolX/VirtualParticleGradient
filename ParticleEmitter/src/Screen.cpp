#include "Screen.h"
#include <mem.h>

Screen::Screen() :
    m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_blurBuffer(NULL){

}

bool Screen::init(){
        if(SDL_Init(SDL_INIT_VIDEO)  < 0){
        return false;
    }

    m_window = SDL_CreateWindow(
                                          "Particle Emitter",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if(m_window == NULL){
        SDL_Quit();
        return false;
    }

    // SDL refreshes from top left hand corner to bottom right at max FPS
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(m_renderer == NULL){
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
                                                            // uses 1 byte / pixel      write pixels directly
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_texture == NULL){
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    // must allocate enough memory for each pixel on the screen
    m_buffer = new  Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    m_blurBuffer = new  Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

    // Initialize a block of memory with the same value
    memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    memset(m_blurBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    return true;
}

// Copy from one buffer and write to the other
void Screen::boxBlur(){
    // Swap buffers so pixel info is in blurBuffer and we draw buffer;
    Uint32 *tempBuffer = m_buffer;
    m_buffer = m_blurBuffer;
    m_blurBuffer = tempBuffer;

    for(int y = 0; y < SCREEN_HEIGHT; ++y){
        for(int x = 0; x < SCREEN_WIDTH; ++x){
            /*
            "Box Blur Algorithm":
            Add the colors of all 9 pixels, then divide by 9 to get the average and set "1" to that value

            0 0 0
            0 1 0
            0 0 0
            */

            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;

            int boxBlurDivider = 9;

            for(int row = -1; row <= 1; ++row){
                for(int col = -1; col <= 1; ++col){
                    int curX = x + col;
                    int curY = y + row;

                    if(curX >= 0 && curX < SCREEN_WIDTH && curY >= 0 && curY < SCREEN_HEIGHT){
                        Uint32 color = m_blurBuffer[curY * SCREEN_WIDTH + curX];
                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }

            Uint8 red = redTotal / boxBlurDivider;
            Uint8 green = greenTotal / boxBlurDivider;
            Uint8 blue = blueTotal / boxBlurDivider;

            setPixel(x, y, red, green, blue);
        }
    }
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT){
        return;
    }

    Uint32 color = 0;

    color += red;
    color <<= 8;

    color += green;
    color <<= 8;

    color += blue;
    color <<=8;

    color += 0xFF;
    m_buffer[(y * SCREEN_WIDTH) + x] = color;
}


void Screen::update(){
    // draw to the screen
    SDL_UpdateTexture(m_texture, NULL, m_buffer, /*number of bytes per row of pixels*/ SCREEN_WIDTH*sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

bool Screen::processEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){ // raised by user clicking the X in the window corner
            return false;
        }
    }
    return true;
}
void Screen::close(){
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();

    delete [] m_buffer;
    delete [] m_blurBuffer;
}
