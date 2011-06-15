#pragma once

#include "Vector3D.h"

namespace traer { namespace physics {

class Particle
{
public:  
  
    bool fixed;
	
    Particle( float m );
  
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#distanceTo(traer.physics.Particle)
     */
    float distanceTo( Particle p );
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#makeFixed()
     */
    void makeFixed();
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#isFixed()
     */
    bool isFixed();
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#isFree()
     */
    bool isFree();
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#makeFree()
     */
    void makeFree();
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#position()
     */
    Vector3D position();
      
    Vector3D velocity();
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#mass()
     */
    float mass();
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#setMass(float)
     */
    void setMass( float m );
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#force()
     */
    Vector3D force();
      
    /* (non-Javadoc)
     * @see traer.physics.AbstractParticle#age()
     */
    float age();
  
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