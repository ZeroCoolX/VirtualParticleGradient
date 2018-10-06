#include "Particle.h"
#include <stdlib.h>
#include <math.h>

# define M_PIl          3.141592653589793238462643383279502884L /* pi */

using namespace std;

Particle::Particle():m_x(0), m_y(0)
{
    init();
}

void Particle::init(){
    // Angle from 0 -> 2PI
    m_x = 0;
    m_y = 0;
    m_direction = (2 * M_PIl * rand())/RAND_MAX;
    m_speed = (0.04 * rand())/RAND_MAX;
    // square it to achieve an exaggerated distribution as you move towards the edge
    m_speed *= m_speed;
}

void Particle::update(int interval){
    m_direction += interval * 0.0003;

    double xspeed = m_speed * cos(m_direction);
    double yspeed = m_speed * sin(m_direction);

    m_x += xspeed * interval;
    m_y += yspeed * interval;

    // reset particles that go off the screen to get new direction and speed from the center of the screen
    if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1){
        init();
    }

}

Particle::~Particle()
{

}
