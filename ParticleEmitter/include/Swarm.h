#ifndef SWARM_H
#define SWARM_H
#include "Particle.h"

class Swarm{
public:
    const static int NPARTICLES = 5000;

private:
    Particle * m_pParticles;

public:
    Swarm();
    virtual ~Swarm();
    // neither the particle nor the collection can be changed
    const Particle * const getParticles(){
        return m_pParticles;
    }
};

#endif // SWARM_H
