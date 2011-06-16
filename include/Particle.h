#pragma once

#include "Vector3D.h"

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

    Vector3D* getPosition();
      
    Vector3D* getVelocity();
      
    float getMass() const;
      
    void setMass( const float &m );
      
    Vector3D* getForce();
      
    float getAge() const;

    void setAge(const float &a);

protected:

    Vector3D position;
    Vector3D velocity;
    Vector3D force;
    float mass;
    float age;
    bool dead;
    
    void reset();
  
};

} } // namespace traer::physics