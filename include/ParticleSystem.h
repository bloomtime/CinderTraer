/*
 * May 29, 2005
 */
 
#pragma once

#include <vector>
#include "Vector3D.h"
#include "Integrator.h"
#include "Spring.h"
#include "Attraction.h"
#include "Force.h"

#define RUNGE_KUTTA 0
#define MODIFIED_EULER 1

#define DEFAULT_GRAVITY  0
#define DEFAULT_DRAG 0.001f

namespace traer { namespace physics {

class ParticleSystem
{
public:
    
    std::vector<Particle*> particles;
    std::vector<Spring*> springs;
    std::vector<Attraction*> attractions;
    std::vector<Force*> customForces;
 
    Integrator* integrator;
  
    Vector3D gravity;
    float drag;

    bool hasDeadParticles;
  
    void setIntegrator( int integrator );
  
    void setGravity( float x, float y, float z );
  
    // default down gravity
    void setGravity( float g );
    
    void setDrag( float d );
    
    void tick();
    
    void tick( float t );
    
    Particle* makeParticle( float mass, float x, float y, float z );
    
    Particle* makeParticle();
    
    Spring* makeSpring( Particle* a, Particle* b, float ks, float d, float r );
    
    Attraction* makeAttraction( Particle* a, Particle* b, float k, float minDistance );
    
    void clear();
    
    ParticleSystem( float g, float somedrag );
    
    ParticleSystem( float gx, float gy, float gz, float somedrag );
    
    ParticleSystem();
    
    int numberOfParticles();
    
    int numberOfSprings();
    
    int numberOfAttractions();
    
    Particle* getParticle( int i );
    
    Spring* getSpring( int i );
    
    Attraction* getAttraction( int i );
    
    void addCustomForce( Force* f );
    
    int numberOfCustomForces();
    
    Force* getCustomForce( int i );
    
    Force* removeCustomForce( int i );
    
    void removeParticle( Particle* p );
    
    Spring* removeSpring( int i );
    
    Attraction* removeAttraction( int i  );
    
    void removeAttraction( Attraction* s );
    
    void removeSpring( Spring* a );
    
    void removeCustomForce( Force* f );
  
    // FIXME C++: in Java things in the same package can access protected members
    // what's the C++ OOP equivalent for hiding these methods? should the Integrator own them?
//protected: 

    void applyForces();

    void clearForces();
  
};

} } // namespace traer::physics