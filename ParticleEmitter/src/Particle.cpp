#include "Particle.h"
#include <stdlib.h>

Particle::Particle()
{
    // random number between -1 and 1
    m_x = ((2.0 * rand())/RAND_MAX) - 1;
    m_y = ((2.0 * rand())/RAND_MAX) - 1;

    m_xspeed = (((2.0 * rand()) / RAND_MAX) - 1) * 0.001;
    m_yspeed = (((2.0 * rand()) / RAND_MAX) - 1) * 0.001;
}

void Particle::update(){
    m_x += m_xspeed;
    m_y += m_yspeed;

    if(m_x < -1 || m_x >= 1){
        m_xspeed *= -1;
    }
    if(m_y < -1 || m_y >= 1){
        m_yspeed *= -1;
    }
}

Particle::~Particle()
{

}
