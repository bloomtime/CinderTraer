#pragma once

#include "Integrator.h"
#include "ParticleSystem.h"

namespace traer { namespace physics {

class ModifiedEulerIntegrator : public Integrator
{
public:

	ParticleSystem s;
	
	ModifiedEulerIntegrator( ParticleSystem s );
	
	void step( float t );

};

} } // namespace traer::physics