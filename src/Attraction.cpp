// attract positive repel negative

#include <cmath>
#include "cinder/Vector.h"
#include "Attraction.h"

namespace traer { namespace physics {
	
    Attraction::Attraction( Particle* _a, Particle* _b, float _k, float _distanceMin )
	{
		a = _a;
		b = _b;
		k = _k;
		on = true;
		distanceMin = _distanceMin;
		distanceMinSquared = distanceMin*distanceMin;
	}

	float Attraction::getMinimumDistance()
	{
		return distanceMin;
	}

	void Attraction::setMinimumDistance( float d )
	{
		distanceMin = d;
		distanceMinSquared = d*d;
	}

	void Attraction::turnOff()
	{
		on = false;
	}

	void Attraction::turnOn()
	{
		on = true;
	}

	void Attraction::setStrength( float _k )
	{
		k = k;
	}

	Particle* Attraction::getOneEnd()
	{
		return a;
	}

	Particle* Attraction::getTheOtherEnd()
	{
		return b;
	}

	void Attraction::apply()
	{
		if ( on && ( !a->fixed || !b->fixed ) )
		{
            ci::Vec3f a2b = a->position - b->position;

			float a2bDistanceSquared = a2b.lengthSquared();

			if ( a2bDistanceSquared < distanceMinSquared )
				a2bDistanceSquared = distanceMinSquared;

			float force = k * a->mass * b->mass / a2bDistanceSquared;

			// make unit vector
			
            a2b /= sqrt(a2bDistanceSquared);
			
			// multiply by force 
			
			a2b *= force;

			// apply
			
			if ( !a->fixed )
				a->force -= a2b;
			if ( !b->fixed )
				b->force += a2b;
		}
	}

	float Attraction::getStrength()
	{
		return k;
	}

	bool Attraction::isOn() const
	{
		return on;
	}

	bool Attraction::isOff() const
	{
		return !on;
	}


} } // namespace traer::physics