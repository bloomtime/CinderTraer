/*
 * May 29, 2005
 */
 
#include "ParticleSystem.h"
#include "RungeKuttaIntegrator.h"
#include "ModifiedEulerIntegrator.h"
#include "Vector3D.h"
 
namespace traer { namespace physics {

    // FIXME C++: set with a pointer and delete the old one
    void ParticleSystem::setIntegrator( int id )
    {
        switch ( id )
        {
            case RUNGE_KUTTA:
                integrator = new RungeKuttaIntegrator( this );
                break;
            case MODIFIED_EULER:
                integrator = new ModifiedEulerIntegrator( this );
                break;
        }
    }
    
    void ParticleSystem::setGravity( float x, float y, float z )
    {
        gravity.set( x, y, z );
    }
    
    // default down gravity
    void ParticleSystem::setGravity( float g )
    {
        gravity.set( 0, g, 0 );
    }
    
    void ParticleSystem::setDrag( float d )
    {
        drag = d;
    }
    
    void ParticleSystem::tick()
    {
        tick( 1 );
    }
    
    void ParticleSystem::tick( float t )
    {  
        integrator->step( t );
    }
    
    Particle* ParticleSystem::makeParticle( float mass, float x, float y, float z )
    {
        Particle* p = new Particle( mass );
        p->getPosition()->set( Vector3D(x, y, z) );
        particles.push_back( p );
        return p;
    }
    
    Particle* ParticleSystem::makeParticle()
    {  
        return makeParticle( 1.0f, 0.0f, 0.0f, 0.0f );
    }
    
    Spring* ParticleSystem::makeSpring( Particle* a, Particle* b, float ks, float d, float r )
    {
        Spring* s = new Spring( a, b, ks, d, r );
        springs.push_back( s );
        return s;
    }
    
    Attraction* ParticleSystem::makeAttraction( Particle* a, Particle* b, float k, float minDistance )
    {
        Attraction* m = new Attraction( a, b, k, minDistance );
        attractions.push_back( m );
        return m;
    }
    
    void ParticleSystem::clear()
    {
        // FIXME C++: delete everything, we own it!
        particles.clear();
        springs.clear();
        attractions.clear();
    }
    
    ParticleSystem::ParticleSystem( float g, float somedrag )
    {
        integrator = new RungeKuttaIntegrator( this );
//        particles = new ArrayList();
//        springs = new ArrayList();
//        attractions = new ArrayList();
        gravity.set( 0, g, 0 );
        drag = somedrag;
        hasDeadParticles = false;
    }
    
    ParticleSystem::ParticleSystem( float gx, float gy, float gz, float somedrag )
    {
        integrator = new RungeKuttaIntegrator( this );
//        particles = new ArrayList();
//        springs = new ArrayList();
//        attractions = new ArrayList();
        gravity.set( gx, gy, gz );
        drag = somedrag;
        hasDeadParticles = false;
    }
    
    ParticleSystem::ParticleSystem()
    {
        integrator = new RungeKuttaIntegrator( this );
//        particles = new ArrayList();
//        springs = new ArrayList();
//        attractions = new ArrayList();
        gravity.set( 0, DEFAULT_GRAVITY, 0 );
        drag = DEFAULT_DRAG;
        hasDeadParticles = false;
    }
    
    void ParticleSystem::applyForces()
    {
        if ( !gravity.isZero() )
        {
            for ( int i = 0; i < particles.size(); ++i )
            {
                Particle* p = particles[i];
                p->getForce()->add( gravity );
            }
        }
        
        for ( int i = 0; i < particles.size(); ++i )
        {
            Particle* p = particles[i];
            p->getForce()->add( p->getVelocity()->x * -drag, p->getVelocity()->y * -drag, p->getVelocity()->z * -drag );
        }
        
        for ( int i = 0; i < springs.size(); i++ )
        {
            Spring* f = springs[i];
            f->apply();
        }
        
        for ( int i = 0; i < attractions.size(); i++ )
        {
            Attraction* f = attractions[i];
            f->apply();
        }
        
        for ( int i = 0; i < customForces.size(); i++ )
        {
            Force* f = customForces[i];
            f->apply();
        }
    }
    
    void ParticleSystem::clearForces()
    {
        for ( int i = 0; i < particles.size(); ++i )
        {
            Particle* p = particles[i];
            p->getForce()->clear();
        }
    }
    
    int ParticleSystem::numberOfParticles()
    {
        return particles.size();
    }
    
    int ParticleSystem::numberOfSprings()
    {
        return springs.size();
    }
    
    int ParticleSystem::numberOfAttractions()
    {
        return attractions.size();
    }
    
    Particle* ParticleSystem::getParticle( int i )
    {
        return particles[i];
    }
    
    Spring* ParticleSystem::getSpring( int i )
    {
        return springs[i];
    }
    
    Attraction* ParticleSystem::getAttraction( int i )
    {
        return attractions[i];
    }
    
    void ParticleSystem::addCustomForce( Force* f )
    {
        customForces.push_back( f );
    }
    
    int ParticleSystem::numberOfCustomForces()
    {
        return customForces.size();
    }
    
    Force* ParticleSystem::getCustomForce( int i )
    {
        return customForces[i];
    }
    
    Force* ParticleSystem::removeCustomForce( int i )
    {
        Force* erased = customForces[i];
        customForces.erase( customForces.begin() + i );
        return erased;
    }
    
    void ParticleSystem::removeParticle( Particle* p )
    {
        particles.erase( std::find(particles.begin(), particles.end(), p) );
    }
    
    Spring* ParticleSystem::removeSpring( int i )
    {
        Spring* erased = springs[i];
        springs.erase( springs.begin() + i );
        return erased;
    }
    
    Attraction* ParticleSystem::removeAttraction( int i  )
    {
        Attraction* erased = attractions[i];
        attractions.erase( attractions.begin() + i );
        return erased;
    }
    
    void ParticleSystem::removeAttraction( Attraction* s )
    {
        attractions.erase( std::find(attractions.begin(), attractions.end(), s) );
    }
    
    void ParticleSystem::removeSpring( Spring* a )
    {
        springs.erase( std::find(springs.begin(), springs.end(), a) );
    }
    
    void ParticleSystem::removeCustomForce( Force* f )
    {
        customForces.erase( std::find(customForces.begin(), customForces.end(), f) );
    }

} } // namespace traer::physics