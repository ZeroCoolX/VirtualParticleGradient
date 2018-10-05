#include<iostream>
#include<SDL2/SDL.h>
#include<Screen.h>
#include<math.h>

using namespace std;

int main(int argc, char* argv[]){
    Screen screen;
    if(!screen.init()){
        cout << "Error initializing SDL2..." << endl;
    }


    while(screen.processEvents()){
        // algorithm for wax and waning colours smoothly without crazy hues
        // Returns the number of milliseconds since start
        int elapsed = SDL_GetTicks();
        float r_smoother = 0.0001F;
        float g_smoother = 0.0002F;
        float b_smoother = 0.0003F;
        int halfMaxColourValue = 128; // -128, 128 = 255 (max colour value)
        // extra failsafe that we won't ever go out of 0-255
        unsigned char red = (unsigned char)((1 + sin(elapsed * r_smoother)) * halfMaxColourValue);
        unsigned char green = (unsigned char)((1 + sin(elapsed * g_smoother)) * halfMaxColourValue);
        unsigned char blue = (unsigned char)((1 + sin(elapsed * b_smoother)) * halfMaxColourValue);

        for(int y = 0; y < screen.SCREEN_HEIGHT; ++y){
            for(int x = 0; x < screen.SCREEN_WIDTH; ++x){
                screen.setPixel(x, y, red, green, blue);
            }
        }
        screen.update();
    }

    screen.close();

    return 0;
}
