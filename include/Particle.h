#pragma once

#include "cinder/Vector.h"

namespace traer { namespace physics {

class Particle
{
public:  
  
    Particle( const float &m );
	void setLocked( bool b ){ locked = b; };
	void setFixed( bool b ){ if( !locked ) fixed = b; };
    ci::Vec3f position;
    ci::Vec3f velocity;
    ci::Vec3f force;
    float mass;
    float age;
    bool fixed;
	bool locked;
    
    void reset();
  
};

} } // namespace traer::physics