#include<iostream>
#include<SDL2/SDL.h>
#include<Screen.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<Swarm.h>
using namespace std;

int main(int argc, char* argv[]){
    // seed the rand()
    srand(time(NULL));

    Screen screen;
    if(!screen.init()){
        cout << "Error initializing SDL2..." << endl;
    }

    Swarm swarm;


    while(screen.processEvents()){
        int elapsed = SDL_GetTicks();

        screen.clearScreen();
        swarm.update(elapsed);

        float r_smoother = 0.0001F;
        float g_smoother = 0.0002F;
        float b_smoother = 0.0003F;
        int halfMaxColourValue = 128; // -128, 128 = 255 (max colour value)
        // extra failsafe that we won't ever go out of 0-255
        unsigned char red = (unsigned char)((1 + sin(elapsed * r_smoother)) * halfMaxColourValue);
        unsigned char green = (unsigned char)((1 + sin(elapsed * g_smoother)) * halfMaxColourValue);
        unsigned char blue = (unsigned char)((1 + sin(elapsed * b_smoother)) * halfMaxColourValue);

        const Particle * const pParticles = swarm.getParticles();
        for(int i = 0; i < Swarm::NPARTICLES; ++i){
            Particle particle = pParticles[i];

            int x = (particle.m_x  + 1) * Screen::SCREEN_WIDTH / 2;
            int y = (particle.m_y * Screen::SCREEN_WIDTH / 2) + Screen::SCREEN_HEIGHT / 2;

            screen.setPixel(x, y, red, green, blue);
        }
        screen.update();
    }

    screen.close();

    return 0;
}
