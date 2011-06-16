#include "RungeKuttaIntegrator.h"

namespace traer { namespace physics {

	RungeKuttaIntegrator::RungeKuttaIntegrator( ParticleSystem* system )
	{
		s = system;
	}
	
	void RungeKuttaIntegrator::allocateParticles()
	{
		while ( s->particles.size() > originalPositions.size() )
		{
			originalPositions.push_back( ci::Vec3f() );
			originalVelocities.push_back( ci::Vec3f() );
			k1Forces.push_back( ci::Vec3f() );
			k1Velocities.push_back( ci::Vec3f() );
			k2Forces.push_back( ci::Vec3f() );
			k2Velocities.push_back( ci::Vec3f() );
			k3Forces.push_back( ci::Vec3f() );
			k3Velocities.push_back( ci::Vec3f() );
			k4Forces.push_back( ci::Vec3f() );
			k4Velocities.push_back( ci::Vec3f() );
		}
	}
	
	void RungeKuttaIntegrator::step( const float &deltaT )
	{	
		allocateParticles();
		/////////////////////////////////////////////////////////
		// save original position and velocities
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{		
				originalPositions[i].set( *(p->getPosition()) );
				originalVelocities[i].set( *(p->getVelocity()) );
			}
			
			p->getForce()->set(0,0,0);	// and clear the forces
		}
		
		////////////////////////////////////////////////////////
		// get all the k1 values
		
		s->applyForces();
		
		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				k1Forces[i].set( *(p->getForce()) );
				k1Velocities[i].set( *(p->getVelocity()) );                
			}
			
			p->getForce()->set(0,0,0);	// and clear the forces
		}
		
		////////////////////////////////////////////////////////////////
		// get k2 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				ci::Vec3f originalPosition = originalPositions[i];
				ci::Vec3f k1Velocity = k1Velocities[i];
				
                ci::Vec3f position = *(p->getPosition());
                
                position.set( originalPosition + (k1Velocity * (0.5f * deltaT)) );
				
				ci::Vec3f originalVelocity = originalVelocities[i];
				ci::Vec3f k1Force = k1Forces[i];

                ci::Vec3f velocity = *(p->getVelocity());

				velocity.set( originalVelocity + k1Force * 0.5f * deltaT / p->getMass() );
			}
		}
		
		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				k2Forces[i].set( *(p->getForce()) );
				k2Velocities[i].set( *(p->getVelocity()) );                
			}
			
			p->getForce()->set(0,0,0);	// and clear the forces now that we are done with them
		}
		
		
		/////////////////////////////////////////////////////
		// get k3 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
                ci::Vec3f originalPosition = originalPositions[i];
                ci::Vec3f k2Velocity = k2Velocities[i];
				
                ci::Vec3f position = *(p->getPosition());
                position.set( originalPosition + k2Velocity * 0.5f * deltaT );
				
                ci::Vec3f originalVelocity = originalVelocities[i];
                ci::Vec3f k2Force = k2Forces[i];

                ci::Vec3f velocity = *(p->getVelocity());
                velocity.set( originalVelocity + k2Force * 0.5f * deltaT / p->getMass() );
			}
		}
        
		s->applyForces();
		
		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				k3Forces[i].set( *(p->getForce()) );
				k3Velocities[i].set( *(p->getVelocity()) );                
			}
			
			p->getForce()->set(0,0,0);	// and clear the forces now that we are done with them
		}
		
		
		//////////////////////////////////////////////////
		// get k4 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
                ci::Vec3f originalPosition = originalPositions[i];
				ci::Vec3f k3Velocity = k3Velocities[i];
				
                ci::Vec3f position = *(p->getPosition());
				position.set( originalPosition + k3Velocity * deltaT);
				
				ci::Vec3f originalVelocity = originalVelocities[i];
				ci::Vec3f k3Force = k3Forces[i];

                ci::Vec3f velocity = *(p->getVelocity());
				velocity.set( originalVelocity + k3Force * deltaT / p->getMass());
			}
		}
		
		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				k4Forces[i].set( *(p->getForce()) );
				k4Velocities[i].set( *(p->getVelocity()) );                
			}			
		}
		
		
		/////////////////////////////////////////////////////////////
		// put them all together and what do you get?
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			p->setAge(p->getAge() + deltaT);
			if ( p->isFree() )
			{
				// update position
				
                ci::Vec3f originalPosition = originalPositions[i];
				ci::Vec3f k1Velocity = k1Velocities[i];
				ci::Vec3f k2Velocity = k2Velocities[i];
				ci::Vec3f k3Velocity = k3Velocities[i];
				ci::Vec3f k4Velocity = k4Velocities[i];
				
                ci::Vec3f position = *(p->getPosition());
				position.set( originalPosition + deltaT / 6.0f * ( k1Velocity + 2.0f*k2Velocity + 2.0f*k3Velocity + k4Velocity ) );
				
				// update velocity
				
                ci::Vec3f originalVelocity = originalVelocities[i];
				ci::Vec3f k1Force = k1Forces[i];
				ci::Vec3f k2Force = k2Forces[i];
				ci::Vec3f k3Force = k3Forces[i];
				ci::Vec3f k4Force = k4Forces[i];
				
                ci::Vec3f velocity = *(p->getVelocity());
                velocity.set( originalVelocity + deltaT / ( 6.0f * p->getMass() ) * ( k1Force + 2.0f*k2Force + 2.0f*k3Force + k4Force ) );
			}
		}
	}

} } // namespace traer::physics