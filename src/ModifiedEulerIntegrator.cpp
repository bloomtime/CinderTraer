#include "ModifiedEulerIntegrator.h"

namespace traer { namespace physics {

	ModifiedEulerIntegrator::ModifiedEulerIntegrator( ParticleSystem *system )
	{
		s = system;
	}
	
	void ModifiedEulerIntegrator::step( const float &t )
	{
		s->clearForces();
		s->applyForces();
		
		float halftt = 0.5f*t*t;
		
		for ( int i = 0; i < s->numberOfParticles(); i++ )
		{
			Particle* p = s->getParticle( i );
			if ( p->isFree() )
			{
				float ax = p->getForce()->x/p->getMass();
				float ay = p->getForce()->y/p->getMass();
				float az = p->getForce()->z/p->getMass();
				
				p->getPosition()->add( p->getVelocity()->x/t, p->getVelocity()->y/t, p->getVelocity()->z/t );
				p->getPosition()->add( ax*halftt, ay*halftt, az*halftt );
				p->getVelocity()->add( ax/t, ay/t, az/t );
			}
		}
	}

} } // namespace traer::physics