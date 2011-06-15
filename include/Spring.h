/*
 * May 29, 2005
 */

#pragma once

#include "Force.h"

namespace traer { namespace physics {

/**
 * @author jeffrey traer bernstein
 *
 */
class Spring : public Force
{

public:

    float springConstant;
    float damping;
    float restLength;
    Particle a, b;
    bool on;
    
    Spring( Particle A, Particle B, float ks, float d, float r );
    
    void turnOff();
    
    void turnOn();
    
    bool isOn();
    
    bool isOff();
    
    Particle getOneEnd();
    
    Particle getTheOtherEnd();
    
    float currentLength();
    
    float restLength();
    
    float strength();
    
    void setStrength( float ks );
    
    float damping();
    
    void setDamping( float d );
    
    void setRestLength( float l );
    
    void apply();

protected:

    void setA( Particle p );
    
    void setB( Particle p );
  
};

} } // namespace traer::physics