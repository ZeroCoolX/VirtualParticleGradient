#ifndef PARTICLE_H
#define PARTICLE_H


struct Particle{
    double m_x;
    double m_y;

    double m_xspeed;
    double m_yspeed;

public:
    Particle();
    virtual ~Particle();
    void update();
};

#endif // PARTICLE_H
