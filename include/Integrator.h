
#pragma once

namespace traer { namespace physics {

class Integrator 
{
public:
	virtual void step( float t ) = 0;
};

} } // namespace traer::physics