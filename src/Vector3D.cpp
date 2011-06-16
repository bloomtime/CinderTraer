#include <string>
#include <sstream>
#include <cmath>
#include "Vector3D.h"

namespace traer { namespace physics {

	Vector3D::Vector3D( const float &X, const float &Y, const float &Z )	{ x = X; y = Y; z = Z; }
	Vector3D::Vector3D()                      				{ x = 0; y = 0; z = 0; }
	Vector3D::Vector3D( const Vector3D &p )							{ x = p.x; y = p.y; z = p.z; }
		
	float Vector3D::getZ()									{ return z; }
	float Vector3D::getY()                   				{ return y; }
	float Vector3D::getX()                   				{ return x; }
	
	void Vector3D::setX( const float &X )           			{ x = X; }
	void Vector3D::setY( const float &Y )           			{ y = Y; }
	void Vector3D::setZ( const float &Z )						{ z = Z; }
	
	void Vector3D::set( const float &X, const float &Y, const float &Z )	{ x = X; y = Y; z = Z; }
	
	void Vector3D::set( const Vector3D &p )						{ x = p.x; y = p.y; z = p.z; }
	
	void Vector3D::add( const Vector3D &p )          				{ x += p.x; y += p.y; z += p.z; }
	void Vector3D::subtract( const Vector3D &p )					{ x -= p.x; y -= p.y; z -= p.z; }
	  
	void Vector3D::add( const float &a, const float &b, const float &c )		{ x += a; y += b; z += c; } 
	void Vector3D::subtract( const float &a, const float &b, const float &c )		{ x -= a; y -= b; z -= c; } 
		  
	void Vector3D::multiplyBy( const float &f )	{ x *= f; y *= f; z*= f; }
	
	float Vector3D::distanceTo( const Vector3D &p ) const { return sqrt( distanceSquaredTo( p ) ); }
	
	float Vector3D::distanceSquaredTo( const Vector3D &p ) const { float dx = x-p.x; float dy = y-p.y; float dz = z-p.z; return dx*dx + dy*dy + dz*dz; }
	
	float Vector3D::distanceTo( const float &X, const float &Y, const float &Z ) const
	{
		float dx = x - X;
		float dy = y - Y;
		float dz = z - Z;
		return sqrt( dx*dx + dy*dy + dz*dz );
	}
	
	float Vector3D::dot( const Vector3D &p ) const  			{ return x*p.x + y*p.y + z*p.z; }
	float Vector3D::length() const               			{ return sqrt( x*x + y*y + z*z ); }
	float Vector3D::lengthSquared() const						{ return x*x + y*y + z*z; }
	  
	void Vector3D::clear()                   				{ x = 0; y = 0; z = 0; }

    // FIXME for C++: overload << operator instead
	std::string Vector3D::toString() const
    { 
        std::stringstream ss;
        ss << "(" << x << ", " << y << ", " << z << ")";
        return ss.str(); 
    }

	Vector3D Vector3D::cross( const Vector3D &p ) const
	{
		return Vector3D( y*p.z - z*p.y, 
                         x*p.z - z*p.x,
                         x*p.y - y*p.x );
	}
	
	bool Vector3D::isZero() const
	{
		return x == 0 && y == 0 && z == 0;
	}

} } // namespace traer::physics