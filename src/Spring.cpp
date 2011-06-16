/*
 * May 29, 2005
 */

#include <cmath>
#include "Spring.h"

namespace traer { namespace physics {

    /**
    * @author jeffrey traer bernstein
    *
    */
    
    Spring::Spring( Particle* A, Particle* B, const float &ks, const float &d, const float &r )
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
    
    bool Spring::isOn() const
    {
        return on;
    }
    
    bool Spring::isOff() const
    {
        return !on;
    }
    
    Particle* Spring::getOneEnd() const
    {
        return a;
    }
    
    Particle* Spring::getTheOtherEnd() const
    {
        return b;
    }
    
    float Spring::currentLength() const
    {
        return a->getPosition()->distanceTo( *(b->getPosition()) );
    }
    
    float Spring::getRestLength() const
    {
        return restLength;
    }
    
    float Spring::getStrength() const
    {
        return springConstant;
    }
    
    void Spring::setStrength( const float &ks )
    {
        springConstant = ks;
    }
    
    float Spring::getDamping() const
    {
        return damping;
    }
    
    void Spring::setDamping( const float &d )
    {
        damping = d;
    }
    
    void Spring::setRestLength( const float &l )
    {
        restLength = l;
    }
    
    void Spring::apply()
    {	
        if ( on && ( a->isFree() || b->isFree() ) )
        {
            float a2bX = a->getPosition()->x - b->getPosition()->x;
            float a2bY = a->getPosition()->y - b->getPosition()->y;
            float a2bZ = a->getPosition()->z - b->getPosition()->z;
            
            float a2bDistance = sqrt( a2bX*a2bX + a2bY*a2bY + a2bZ*a2bZ );
            
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
            
            float Va2bX = a->getVelocity()->x - b->getVelocity()->x;
            float Va2bY = a->getVelocity()->y - b->getVelocity()->y;
            float Va2bZ = a->getVelocity()->z - b->getVelocity()->z;
                                
            float dampingForce = -damping * ( a2bX*Va2bX + a2bY*Va2bY + a2bZ*Va2bZ );
            
            
            // forceB is same as forceA in opposite direction
            
            float r = springForce + dampingForce;
            
            a2bX *= r;
            a2bY *= r;
            a2bZ *= r;
            
            if ( a->isFree() )
                a->getForce()->add( a2bX, a2bY, a2bZ );
            if ( b->isFree() )
                b->getForce()->add( -a2bX, -a2bY, -a2bZ );
        }
    }
    
    void Spring::setA( Particle* p )
    {
        a = p;
    }
    
    void Spring::setB( Particle* p )
    {
        b = p;
    }

} } // namespace traer::physics