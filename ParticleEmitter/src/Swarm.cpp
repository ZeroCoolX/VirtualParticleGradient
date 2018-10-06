#include "Swarm.h"

Swarm::Swarm()
{
    m_pParticles = new Particle[NPARTICLES];
}

void Swarm::update(){
    for(int i = 0; i < NPARTICLES; ++i){
        m_pParticles[i].update();
    }
}

Swarm::~Swarm()
{
    delete [] m_pParticles;
}
