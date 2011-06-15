/*
 * May 29, 2005
 */
 
#include "ParticleSystem.h"
 
namespace traer { namespace physics {

    void ParticleSystem::setIntegrator( int integrator )
    {
        switch ( integrator )
        {
            case RUNGE_KUTTA:
                this.integrator = new RungeKuttaIntegrator( this );
                break;
            case MODIFIED_EULER:
                this.integrator = new ModifiedEulerIntegrator( this );
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
        integrator.step( t );
    }
    
    Particle ParticleSystem::makeParticle( float mass, float x, float y, float z )
    {
        Particle p = new Particle( mass );
        p.position().set( x, y, z );
        particles.add( p );
        return p;
    }
    
    Particle ParticleSystem::makeParticle()
    {  
        return makeParticle( 1.0f, 0f, 0f, 0f );
    }
    
    Spring ParticleSystem::makeSpring( Particle a, Particle b, float ks, float d, float r )
    {
        Spring s = new Spring( a, b, ks, d, r );
        springs.add( s );
        return s;
    }
    
    Attraction ParticleSystem::makeAttraction( Particle a, Particle b, float k, float minDistance )
    {
        Attraction m = new Attraction( a, b, k, minDistance );
        attractions.add( m );
        return m;
    }
    
    void ParticleSystem::clear()
    {
        particles.clear();
        springs.clear();
        attractions.clear();
    }
    
    public ParticleSystem::ParticleSystem( float g, float somedrag )
    {
        integrator = new RungeKuttaIntegrator( this );
        particles = new ArrayList();
        springs = new ArrayList();
        attractions = new ArrayList();
        gravity = new Vector3D( 0, g, 0 );
        drag = somedrag;
        hasDeadParticles = false;
    }
    
    public ParticleSystem::ParticleSystem( float gx, float gy, float gz, float somedrag )
    {
        integrator = new RungeKuttaIntegrator( this );
        particles = new ArrayList();
        springs = new ArrayList();
        attractions = new ArrayList();
        gravity = new Vector3D( gx, gy, gz );
        drag = somedrag;
        hasDeadParticles = false;
    }
    
    public ParticleSystem::ParticleSystem()
    {
        integrator = new RungeKuttaIntegrator( this );
        particles = new ArrayList();
        springs = new ArrayList();
        attractions = new ArrayList();
        gravity = new Vector3D( 0, ParticleSystem.DEFAULT_GRAVITY, 0 );
        drag = ParticleSystem.DEFAULT_DRAG;
        hasDeadParticles = false;
    }
    
    void ParticleSystem::applyForces()
    {
        if ( !gravity.isZero() )
        {
            for ( int i = 0; i < particles.size(); ++i )
            {
                Particle p = (Particle)particles.get( i );
                p.force.add( gravity );
            }
        }
        
        for ( int i = 0; i < particles.size(); ++i )
        {
            Particle p = (Particle)particles.get( i );
            p.force.add( p.velocity.x() * -drag, p.velocity.y() * -drag, p.velocity.z() * -drag );
        }
        
        for ( int i = 0; i < springs.size(); i++ )
        {
            Spring f = (Spring)springs.get( i );
            f.apply();
        }
        
        for ( int i = 0; i < attractions.size(); i++ )
        {
            Attraction f = (Attraction)attractions.get( i );
            f.apply();
        }
        
        for ( int i = 0; i < customForces.size(); i++ )
        {
            Force f = (Force)customForces.get( i );
            f.apply();
        }
    }
    
    void ParticleSystem::clearForces()
    {
        Iterator i = particles.iterator();
        while ( i.hasNext() )
        {
            Particle p = (Particle)i.next();
            p.force.clear();
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
    
    Particle ParticleSystem::getParticle( int i )
    {
        return (Particle)particles.get( i );
    }
    
    Spring ParticleSystem::getSpring( int i )
    {
        return (Spring)springs.get( i );
    }
    
    Attraction ParticleSystem::getAttraction( int i )
    {
        return (Attraction)attractions.get( i );
    }
    
    void ParticleSystem::addCustomForce( Force f )
    {
        customForces.add( f );
    }
    
    int ParticleSystem::numberOfCustomForces()
    {
        return customForces.size();
    }
    
    Force ParticleSystem::getCustomForce( int i )
    {
        return (Force)customForces.get( i );
    }
    
    Force ParticleSystem::removeCustomForce( int i )
    {
        return (Force)customForces.remove( i );
    }
    
    void ParticleSystem::removeParticle( Particle p )
    {
        particles.remove( p );
    }
    
    Spring ParticleSystem::removeSpring( int i )
    {
        return (Spring)springs.remove( i );
    }
    
    Attraction ParticleSystem::removeAttraction( int i  )
    {
        return (Attraction)attractions.remove( i );
    }
    
    void ParticleSystem::removeAttraction( Attraction s )
    {
        attractions.remove( s );
    }
    
    void ParticleSystem::removeSpring( Spring a )
    {
        springs.remove( a );
    }
    
    void ParticleSystem::removeCustomForce( Force f )
    {
        customForces.remove( f );
    }

} } // namespace traer::physics