#pragma once

#include "cinder/Vector.h"

namespace traer { namespace physics {

class Particle
{
public:  
  
    Particle( const float &m );
  
    ci::Vec3f position;
    ci::Vec3f velocity;
    ci::Vec3f force;
    float mass;
    float age;
    bool fixed;
    
    void reset();
  
};

} } // namespace traer::physics