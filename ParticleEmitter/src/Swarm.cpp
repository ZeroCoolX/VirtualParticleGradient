#include "Swarm.h"

Swarm::Swarm(): previousTime(0)
{
    m_pParticles = new Particle[NPARTICLES];
}

void Swarm::update(int elapsedMiliseconds){
    int interval = elapsedMiliseconds - previousTime;

    for(int i = 0; i < NPARTICLES; ++i){
        m_pParticles[i].update(interval);
    }

    previousTime = elapsedMiliseconds;
}

Swarm::~Swarm()
{
    delete [] m_pParticles;
}
