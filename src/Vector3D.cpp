#include <string>
#include "Vector3D.h"

namespace traer { namespace physics {

	Vector3D::Vector3D( float X, float Y, float Z )	{ x = X; y = Y; z = Z; }
	Vector3D::Vector3D()                      				{ x = 0; y = 0; z = 0; }
	Vector3D::Vector3D( Vector3D p )							{ x = p.x; y = p.y; z = p.z; }
		
	float Vector3D::z()									{ return z; }
	float Vector3D::y()                   				{ return y; }
	float Vector3D::x()                   				{ return x; }
	
	void Vector3D::setX( float X )           			{ x = X; }
	void Vector3D::setY( float Y )           			{ y = Y; }
	void Vector3D::setZ( float Z )						{ z = Z; }
	
	void Vector3D::set( float X, float Y, float Z )	{ x = X; y = Y; z = Z; }
	
	void Vector3D::set( Vector3D p )						{ x = p.x; y = p.y; z = p.z; }
	
	void Vector3D::add( Vector3D p )          				{ x += p.x; y += p.y; z += p.z; }
	void Vector3D::subtract( Vector3D p )					{ x -= p.x; y -= p.y; z -= p.z; }
	  
	void Vector3D::add( float a, float b, float c )		{ x += a; y += b; z += c; } 
	void Vector3D::subtract( float a, float b, float c )		{ x -= a; y -= b; z -= c; } 
		  
	Vector3D Vector3D::multiplyBy( float f )					{ x *= f; y *= f; z*= f; return this; }
	
	float Vector3D::distanceTo( Vector3D p )  			{ return (float)Math.sqrt( distanceSquaredTo( p ) ); }
	
	float Vector3D::distanceSquaredTo( Vector3D p )		{ float dx = x-p.x; float dy = y-p.y; float dz = z-p.z; return dx*dx + dy*dy + dz*dz; }
	
	float Vector3D::distanceTo( float x, float y, float z )
	{
		float dx = this.x - x;
		float dy = this.y - y;
		float dz = this.z - z;
		return (float)Math.sqrt( dx*dx + dy*dy + dz*dz );
	}
	
	float Vector3D::dot( Vector3D p )         			{ return x*p.x + y*p.y + z*p.z; }
	float Vector3D::length()                 			{ return (float)Math.sqrt( x*x + y*y + z*z ); }
	float Vector3D::lengthSquared()						{ return x*x + y*y + z*z; }
	  
	void Vector3D::clear()                   				{ x = 0; y = 0; z = 0; }

	std::string Vector3D::toString()              				{ return "(" + x + ", " + y + ", " + z + ")"; }

	Vector3D Vector3D::cross( Vector3D p )
	{
		return new Vector3D( 	this.y*p.z - this.z*p.y, 
								this.x*p.z - this.z*p.x,
								this.x*p.y - this.y*p.x );
	}
	
	bool Vector3D::isZero()
	{
		return x == 0 && y == 0 && z == 0;
	}

} } // namespace traer::physics