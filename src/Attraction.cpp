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
            const ci::Vec3f p1 = *(a->getPosition());
            const ci::Vec3f p2 = *(b->getPosition());
			float a2bX = p1.x - p2.x;
			float a2bY = p1.y - p2.y;
			float a2bZ = p1.z - p2.z;

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
				*(a->getForce()) += ci::Vec3f( -a2bX, -a2bY, -a2bZ );
			if ( b->isFree() )
				*(b->getForce()) += ci::Vec3f( a2bX, a2bY, a2bZ );
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