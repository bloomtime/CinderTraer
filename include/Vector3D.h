#pragma once

namespace traer { namespace physics {

class Vector3D
{
public: 

	float x;
	float y;
	float z;

	Vector3D( float X, float Y, float Z );
	Vector3D();
	Vector3D( Vector3D p );
		
	float z();
	float y();
	float x();
	
	void setX( float X );
	void setY( float Y );
	void setZ( float Z );
	
	void set( float X, float Y, float Z );
	
	void set( Vector3D p );
	
	void add( Vector3D p );
	void subtract( Vector3D p );
	  
	void add( float a, float b, float c );
	void subtract( float a, float b, float c );
		  
	Vector3D multiplyBy( float f );
	
	float distanceTo( Vector3D p );
	
	float distanceSquaredTo( Vector3D p );
	
	float distanceTo( float x, float y, float z );
	
	float dot( Vector3D p );
	float length();
	float lengthSquared();
	  
	void clear();

	String toString();

	Vector3D cross( Vector3D p );
	
	bool isZero();

};

} } // namespace traer::physics