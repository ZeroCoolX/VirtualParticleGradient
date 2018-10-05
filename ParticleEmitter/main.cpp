#include<iostream>
#include<SDL2/SDL.h>
#include<Screen.h>

using namespace std;

int main(int argc, char* argv[]){
    Screen screen;
    if(!screen.init()){
        cout << "Error initializing SDL2..." << endl;
    }

    while(screen.processEvents()){
        // update particles
        // draw particles
        // check for messages/events
    }

    screen.close();

    return 0;
}
