#include "EulerIntegrator.h"
#include "Particle.h"

namespace traer { namespace physics {

	EulerIntegrator::EulerIntegrator( ParticleSystem* system )
	{
		s = system;
	}
	
	void EulerIntegrator::step( const float &t )
	{
		s->clearForces();
		s->applyForces();
		
		for ( int i = 0; i < s->numberOfParticles(); i++ )
		{
			Particle* p = s->getParticle( i );
			if ( p->isFree() )
			{
                const ci::Vec3f force = *(p->getForce());
                const float mass = p->getMass();
                ci::Vec3f velocity = *(p->getVelocity());
                velocity += force / (mass*t);
                ci::Vec3f position = *(p->getPosition());
                position += velocity / t;
			}
		}
	}

} } // namespace traer::physics