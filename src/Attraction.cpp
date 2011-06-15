// attract positive repel negative

#include "Attraction.h"
#include <cmath>

namespace traer { namespace physics {
	
    Attraction::Attraction( Particle a, Particle b, float k, float distanceMin )
	{
		this.a = a;
		this.b = b;
		this.k = k;
		on = true;
		this.distanceMin = distanceMin;
		this.distanceMinSquared = distanceMin*distanceMin;
	}

	void Attraction::setA( Particle p )
	{
		a = p;
	}

	void Attraction::setB( Particle p )
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

	void Attraction::setStrength( float k )
	{
		this.k = k;
	}

	Particle Attraction::getOneEnd()
	{
		return a;
	}

	Particle Attraction::getTheOtherEnd()
	{
		return b;
	}

	void Attraction::apply()
	{
		if ( on && ( a.isFree() || b.isFree() ) )
		{
			float a2bX = a.position().x() - b.position().x();
			float a2bY = a.position().y() - b.position().y();
			float a2bZ = a.position().z() - b.position().z();

			float a2bDistanceSquared = a2bX*a2bX + a2bY*a2bY + a2bZ*a2bZ;

			if ( a2bDistanceSquared < distanceMinSquared )
				a2bDistanceSquared = distanceMinSquared;

			float force = k * a.mass * b.mass / a2bDistanceSquared;

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
			
			if ( a.isFree() )
				a.force().add( -a2bX, -a2bY, -a2bZ );
			if ( b.isFree() )
				b.force().add( a2bX, a2bY, a2bZ );
		}
	}

	float Attraction::getStrength()
	{
		return k;
	}

	bool Attraction::isOn()
	{
		return on;
	}

	bool Attraction::isOff()
	{
		return !on;
	}
}

} } // namespace traer::physics