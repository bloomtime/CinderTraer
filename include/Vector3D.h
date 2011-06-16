#pragma once

#include <string>

namespace traer { namespace physics {

class Vector3D
{
public: 

	float x;
	float y;
	float z;

	Vector3D( const float &x, const float &y, const float &z );
	Vector3D();
	Vector3D( const Vector3D &p );
		
	float getX();
	float getY();
	float getZ();
	
	void setX( const float &X );
	void setY( const float &Y );
	void setZ( const float &Z );
	
	void set( const float &x, const float &y, const float &z );
	
	void set( const Vector3D &p );
	
	void add( const Vector3D &p );
	void subtract( const Vector3D &p );
	  
	void add( const float &a, const float &b, const float &c );
	void subtract( const float &a, const float &b, const float &c );

    // FIXME for C++: is there a chainable alternative here?
//	Vector3D multiplyBy( float f );
	void multiplyBy( const float &f );
	
	float distanceTo( const Vector3D &p ) const;
	
	float distanceSquaredTo( const Vector3D &p ) const;
	
	float distanceTo( const float &x, const float &y, const float &z ) const;
	
	float dot( const Vector3D &p ) const;
	float length() const;
	float lengthSquared() const;
	  
	void clear();

    std::string toString() const;

	Vector3D cross( const Vector3D &p ) const;
	
	bool isZero() const;

};

} } // namespace traer::physics