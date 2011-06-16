#pragma once

#include "cinder/Vector.h"

namespace traer { namespace physics {

class Particle
{
public:  
  
    bool fixed;
	
    Particle( const float &m );
  
    float distanceTo( Particle *p ) const;
      
    void makeFixed();
      
    bool isFixed() const;
      
    bool isFree() const;

    void makeFree();

    ci::Vec3f* getPosition();
      
    ci::Vec3f* getVelocity();
      
    float getMass() const;
      
    void setMass( const float &m );
      
    ci::Vec3f* getForce();
      
    float getAge() const;

    void setAge(const float &a);

protected:

    ci::Vec3f position;
    ci::Vec3f velocity;
    ci::Vec3f force;
    float mass;
    float age;
    bool dead;
    
    void reset();
  
};

} } // namespace traer::physics