
#include "Particle.h"

namespace traer { namespace physics {

    Particle::Particle( const float &m )
    {
//        position = new Vector3D();
//        velocity = new Vector3D();
//        force = new Vector3D();
        mass = m;
        fixed = false;
        age = 0;
        dead = false;
    }
  
    float Particle::distanceTo( Particle *p ) const
    {
        return position.distanceTo( *(p->getPosition()) );
    }
  
    void Particle::makeFixed()
    {
	    fixed = true;
	    velocity.clear();
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
  
    Vector3D* Particle::getPosition()
    {
        return &position;
    }
  
    Vector3D* Particle::getVelocity()
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
  
    Vector3D* Particle::getForce()
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
        position.clear();
        velocity.clear();
        force.clear();
        mass = 1.0f;
    }

} } // namespace traer::physics