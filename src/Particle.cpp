
#include "Particle.h"

namespace traer { namespace physics {

    Particle::Particle( float m )
    {
        position = new Vector3D();
        velocity = new Vector3D();
        force = new Vector3D();
        mass = m;
        fixed = false;
        age = 0;
        dead = false;
    }
  
    float Particle::distanceTo( Particle p )
    {
        return this.position().distanceTo( p.position() );
    }
  
    void Particle::makeFixed()
    {
	    fixed = true;
	    velocity.clear();
    }
  
    bool Particle::isFixed()
    {
	  return fixed;
    }
  
    bool Particle::isFree()
    {
        return !fixed;
    }
  
    void Particle::makeFree()
    {
        fixed = false;
    }
  
    Vector3D Particle::position()
    {
        return position;
    }
  
    Vector3D Particle::velocity()
    {
        return velocity;
    }
  
    float Particle::mass()
    {
        return mass;
    }
  
    void Particle::setMass( float m )
    {
        mass = m;
    }
  
    Vector3D Particle::force()
    {
        return force;
    }
  
    float Particle::age()
    {
        return age;
    }
  
    void Particle::reset()
    {
        age = 0;
        dead = false;
        position.clear();
        velocity.clear();
        force.clear();
        mass = 1f;
    }

} } // namespace traer::physics