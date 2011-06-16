#include "RungeKuttaIntegrator.h"

namespace traer { namespace physics {

	RungeKuttaIntegrator::RungeKuttaIntegrator( ParticleSystem* system )
	{
		s = system;
		
//		originalPositions = new ArrayList();
//		originalVelocities = new ArrayList();
//		k1Forces = new ArrayList();
//		k1Velocities = new ArrayList();
//		k2Forces = new ArrayList();
//		k2Velocities = new ArrayList();
//		k3Forces = new ArrayList();
//		k3Velocities = new ArrayList();
//		k4Forces = new ArrayList();
//		k4Velocities = new ArrayList();
	}
	
	void RungeKuttaIntegrator::allocateParticles()
	{
		while ( s->particles.size() > originalPositions.size() )
		{
			originalPositions.push_back( Vector3D() );
			originalVelocities.push_back( Vector3D() );
			k1Forces.push_back( Vector3D() );
			k1Velocities.push_back( Vector3D() );
			k2Forces.push_back( Vector3D() );
			k2Velocities.push_back( Vector3D() );
			k3Forces.push_back( Vector3D() );
			k3Velocities.push_back( Vector3D() );
			k4Forces.push_back( Vector3D() );
			k4Velocities.push_back( Vector3D() );
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
			
			p->getForce()->clear();	// and clear the forces
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
			
			p->getForce()->clear();	// and clear the forces
		}
		
		////////////////////////////////////////////////////////////////
		// get k2 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				Vector3D originalPosition = originalPositions[i];
				Vector3D k1Velocity = k1Velocities[i];
				
				p->getPosition()->set( originalPosition.x + k1Velocity.x * 0.5f * deltaT,
                                       originalPosition.y + k1Velocity.y * 0.5f * deltaT,
                                       originalPosition.z + k1Velocity.z * 0.5f * deltaT );
				
				Vector3D originalVelocity = originalVelocities[i];
				Vector3D k1Force = k1Forces[i];
				
				p->getVelocity()->set( originalVelocity.x + k1Force.x * 0.5f * deltaT / p->getMass(),
                                       originalVelocity.y + k1Force.y * 0.5f * deltaT / p->getMass(),
                                       originalVelocity.z + k1Force.z * 0.5f * deltaT / p->getMass() );
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
			
            p->getForce()->clear();	// and clear the forces now that we are done with them
		}
		
		
		/////////////////////////////////////////////////////
		// get k3 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				Vector3D originalPosition = originalPositions[i];
				Vector3D k2Velocity = k2Velocities[i];
				
				p->getPosition()->set( originalPosition.x + k2Velocity.x * 0.5f * deltaT,
                                      originalPosition.y + k2Velocity.y * 0.5f * deltaT,
                                      originalPosition.z + k2Velocity.z * 0.5f * deltaT );
				
				Vector3D originalVelocity = originalVelocities[i];
				Vector3D k2Force = k2Forces[i];
				
				p->getVelocity()->set( originalVelocity.x + k2Force.x * 0.5f * deltaT / p->getMass(),
                                      originalVelocity.y + k2Force.y * 0.5f * deltaT / p->getMass(),
                                      originalVelocity.z + k2Force.z * 0.5f * deltaT / p->getMass() );
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
			
            p->getForce()->clear();	// and clear the forces now that we are done with them
		}
		
		
		//////////////////////////////////////////////////
		// get k4 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( p->isFree() )
			{
				Vector3D originalPosition = originalPositions[i];
				Vector3D k3Velocity = k3Velocities[i];
				
				p->getPosition()->set( originalPosition.x + k3Velocity.x * deltaT,
                                      originalPosition.y + k3Velocity.y * deltaT,
                                      originalPosition.z + k3Velocity.z * deltaT );
				
				Vector3D originalVelocity = originalVelocities[i];
				Vector3D k3Force = k3Forces[i];
				
				p->getVelocity()->set( originalVelocity.x + k3Force.x * deltaT / p->getMass(),
                                      originalVelocity.y + k3Force.y * deltaT / p->getMass(),
                                      originalVelocity.z + k3Force.z * deltaT / p->getMass() );
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
				
				Vector3D originalPosition = originalPositions[i];
				Vector3D k1Velocity = k1Velocities[i];
				Vector3D k2Velocity = k2Velocities[i];
				Vector3D k3Velocity = k3Velocities[i];
				Vector3D k4Velocity = k4Velocities[i];
				
				p->getPosition()->set( 
                    originalPosition.x + deltaT / 6.0f * ( k1Velocity.x + 2.0f*k2Velocity.x + 2.0f*k3Velocity.x + k4Velocity.x ),
                    originalPosition.y + deltaT / 6.0f * ( k1Velocity.y + 2.0f*k2Velocity.y + 2.0f*k3Velocity.y + k4Velocity.y ),
                    originalPosition.z + deltaT / 6.0f * ( k1Velocity.z + 2.0f*k2Velocity.z + 2.0f*k3Velocity.z + k4Velocity.z ) 
                );
				
				// update velocity
				
				Vector3D originalVelocity = originalVelocities[i];
				Vector3D k1Force = k1Forces[i];
				Vector3D k2Force = k2Forces[i];
				Vector3D k3Force = k3Forces[i];
				Vector3D k4Force = k4Forces[i];
				
                p->getVelocity()->set(
                    originalVelocity.x + deltaT / ( 6.0f * p->getMass() ) * ( k1Force.x + 2.0f*k2Force.x + 2.0f*k3Force.x + k4Force.x ),
                    originalVelocity.y + deltaT / ( 6.0f * p->getMass() ) * ( k1Force.y + 2.0f*k2Force.y + 2.0f*k3Force.y + k4Force.y ),
                    originalVelocity.z + deltaT / ( 6.0f * p->getMass() ) * ( k1Force.z + 2.0f*k2Force.z + 2.0f*k3Force.z + k4Force.z )
                );
			}
		}
	}

} } // namespace traer::physics