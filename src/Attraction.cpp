// attract positive repel negative

#include "Attraction.h"
#include <cmath>

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

	void Attraction::setA( Particle* p )
	{
		a = p;
	}

	void Attraction::setB( Particle* p )
	{
		b = p;
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
		if ( on && ( a->isFree() || b->isFree() ) )
		{
			float a2bX = a->getPosition()->x - b->getPosition()->x;
			float a2bY = a->getPosition()->y - b->getPosition()->y;
			float a2bZ = a->getPosition()->z - b->getPosition()->z;

			float a2bDistanceSquared = a2bX*a2bX + a2bY*a2bY + a2bZ*a2bZ;

			if ( a2bDistanceSquared < distanceMinSquared )
				a2bDistanceSquared = distanceMinSquared;

			float force = k * a->getMass() * b->getMass() / a2bDistanceSquared;

			float length = sqrt( a2bDistanceSquared );
			
			// make unit vector
			
			a2bX /= length;
			a2bY /= length;
			a2bZ /= length;
			
			// multiply by force 
			
			a2bX *= force;
			a2bY *= force;
			a2bZ *= force;

			// apply
			
			if ( a->isFree() )
				a->getForce()->add( -a2bX, -a2bY, -a2bZ );
			if ( b->isFree() )
				b->getForce()->add( a2bX, a2bY, a2bZ );
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