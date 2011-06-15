#pragma once

#include <vector>
#include "Integrator.h"
#include "ParticleSystem.h"

namespace traer { namespace physics {

class RungeKuttaIntegrator : public Integrator
{

public:

	std::vector<Vector3D> originalPositions;
	std::vector<Vector3D> originalVelocities;
	std::vector<Vector3D> k1Forces;
	std::vector<Vector3D> k1Velocities;
	std::vector<Vector3D> k2Forces;
	std::vector<Vector3D> k2Velocities;
	std::vector<Vector3D> k3Forces;
	std::vector<Vector3D> k3Velocities;
	std::vector<Vector3D> k4Forces;
	std::vector<Vector3D> k4Velocities;
	
	ParticleSystem s;
	
	public RungeKuttaIntegrator( ParticleSystem s );
	
	void allocateParticles();
	
	void step( float deltaT );

};

} } // namespace traer::physics