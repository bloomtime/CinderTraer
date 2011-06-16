
#include "Particle.h"

namespace traer { namespace physics {

    Particle::Particle( const float &m )
    {
        mass = m;
        fixed = false;
        age = 0;
        dead = false;
    }
  
    float Particle::distanceTo( Particle *p ) const
    {
        return position.distance( *(p->getPosition()) );
    }
  
    void Particle::makeFixed()
    {
	    fixed = true;
	    velocity.set(0,0,0);
    }
  
    bool Particle::isFixed() const
    {
	  return fixed;
    }
  
    bool Particle::isFree() const
    {
        return !fixed;
    }
  
    void Particle::makeFree()
    {
        fixed = false;
    }
  
    ci::Vec3f* Particle::getPosition()
    {
        return &position;
    }
  
    ci::Vec3f* Particle::getVelocity()
    {
        return &velocity;
    }
  
    float Particle::getMass() const
    {
        return mass;
    }
  
    void Particle::setMass( const float &m )
    {
        mass = m;
    }
  
    ci::Vec3f* Particle::getForce()
    {
        return &force;
    }
  
    float Particle::getAge() const
    {
        return age;
    }

    void Particle::setAge(const float &a)
    {
        age = a;
    }

    void Particle::reset()
    {
        age = 0;
        dead = false;
        position.set(0,0,0);
        velocity.set(0,0,0);
        force.set(0,0,0);
        mass = 1.0f;
    }

} } // namespace traer::physics