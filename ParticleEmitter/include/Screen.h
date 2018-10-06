#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

class Screen
{
public:
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HEIGHT = 600;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer;

public:
    Screen();
    bool init();
    bool processEvents();
    void close();
    void update();
    void clearScreen();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
};

#endif // SCREEN_H
