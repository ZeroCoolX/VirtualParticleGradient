#ifndef SWARM_H
#define SWARM_H
#include "Particle.h"

class Swarm{
public:
    const static int NPARTICLES = 5000;

private:
    Particle * m_pParticles;
    int previousTime;

public:
    Swarm();
    virtual ~Swarm();
    void update(int elapsedMilisecond);
    // neither the particle nor the collection can be changed
    const Particle * const getParticles(){
        return m_pParticles;
    }
};

#endif // SWARM_H
