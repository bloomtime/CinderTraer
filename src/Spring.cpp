/*
 * May 29, 2005
 */

#include "Spring.h"

namespace traer { namespace physics {

    /**
    * @author jeffrey traer bernstein
    *
    */
    
    Spring::Spring( Particle A, Particle B, float ks, float d, float r )
    {
        springConstant = ks;
        damping = d;
        restLength = r;
        a = A;
        b = B;
        on = true;
    }
    
    void Spring::turnOff()
    {
        on = false;
    }
    
    void Spring::turnOn()
    {
        on = true;
    }
    
    bool Spring::isOn()
    {
        return on;
    }
    
    bool Spring::isOff()
    {
        return !on;
    }
    
    Particle Spring::getOneEnd()
    {
        return a;
    }
    
    Particle Spring::getTheOtherEnd()
    {
        return b;
    }
    
    float Spring::currentLength()
    {
        return a.position().distanceTo( b.position() );
    }
    
    float Spring::restLength()
    {
        return restLength;
    }
    
    float Spring::strength()
    {
        return springConstant;
    }
    
    void Spring::setStrength( float ks )
    {
        springConstant = ks;
    }
    
    float Spring::damping()
    {
        return damping;
    }
    
    void Spring::setDamping( float d )
    {
        damping = d;
    }
    
    void Spring::setRestLength( float l )
    {
        restLength = l;
    }
    
    void Spring::apply()
    {	
        if ( on && ( a.isFree() || b.isFree() ) )
        {
            float a2bX = a.position().x - b.position().x;
            float a2bY = a.position().y - b.position().y;
            float a2bZ = a.position().z - b.position().z;
            
            float a2bDistance = (float)Math.sqrt( a2bX*a2bX + a2bY*a2bY + a2bZ*a2bZ );
            
            if ( a2bDistance == 0 )
            {
                a2bX = 0;
                a2bY = 0;
                a2bZ = 0;
            }
            else
            {
                a2bX /= a2bDistance;
                a2bY /= a2bDistance;
                a2bZ /= a2bDistance;
            }
            
        
            // spring force is proportional to how much it stretched 
            
            float springForce = -( a2bDistance - restLength ) * springConstant; 
            
            
            // want velocity along line b/w a & b, damping force is proportional to this
            
            float Va2bX = a.velocity().x - b.velocity().x;
            float Va2bY = a.velocity().y - b.velocity().y;
            float Va2bZ = a.velocity().z - b.velocity().z;
                                
            float dampingForce = -damping * ( a2bX*Va2bX + a2bY*Va2bY + a2bZ*Va2bZ );
            
            
            // forceB is same as forceA in opposite direction
            
            float r = springForce + dampingForce;
            
            a2bX *= r;
            a2bY *= r;
            a2bZ *= r;
            
            if ( a.isFree() )
                a.force().add( a2bX, a2bY, a2bZ );
            if ( b.isFree() )
                b.force().add( -a2bX, -a2bY, -a2bZ );
        }
    }
    
    void Spring::setA( Particle p )
    {
        a = p;
    }
    
    void Spring::setB( Particle p )
    {
        b = p;
    }

} } // namespace traer::physics