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
				p->getVelocity()->add( p->getForce()->x/(p->getMass()*t), 
                                       p->getForce()->y/(p->getMass()*t), 
                                       p->getForce()->z/(p->getMass()*t) );
				p->getPosition()->add( p->getVelocity()->x/t, 
                                       p->getVelocity()->y/t,
                                       p->getVelocity()->z/t );
			}
		}
	}

} } // namespace traer::physics