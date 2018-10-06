#include "Particle.h"
#include <stdlib.h>
#include <math.h>

# define M_PIl          3.141592653589793238462643383279502884L /* pi */

using namespace std;

Particle::Particle():m_x(0), m_y(0)
{
    // Angle from 0 -> 2PI
    m_direction = (2 * M_PIl * rand())/RAND_MAX;
    m_speed = (0.0001 * rand())/RAND_MAX;
}

void Particle::update(int interval){
    double xspeed = m_speed * cos(m_direction);
    double yspeed = m_speed * sin(m_direction);

    m_x += xspeed * interval;
    m_y += yspeed * interval;
}

Particle::~Particle()
{

}
