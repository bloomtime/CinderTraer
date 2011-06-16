// adapted from http://murderandcreate.com/physics/cloth/
#import <CoreMotion/CoreMotion.h>
#include <sstream>
#include <vector>
#include "cinder/app/AppCocoaTouch.h"
#include "cinder/app/TouchEvent.h"
#include "cinder/app/Renderer.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "ParticleSystem.h"
#include "ModifiedEulerIntegrator.h"
#include "Particle.h"
#include "Spring.h"

using namespace ci;
using namespace ci::app;
using namespace traer::physics;
using std::vector;

#define NODE_SIZE 10
#define SPRING_STRENGTH 0.1
#define SPRING_DAMPING 0.01
#define GRID_X_RES 15
#define GRID_Y_RES 20

class Cloth : public AppCocoaTouch {
  public:
	virtual void	setup();
	virtual void	update();
	virtual void	draw();
	virtual void	accelerated( AccelEvent event );
	virtual void	touchesBegan( TouchEvent event );
	virtual void	touchesMoved( TouchEvent event );
	virtual void	touchesEnded( TouchEvent event );
	
    void drawNetwork();
    void initialize();
	
    ParticleSystem*		physics;
	vector<Particle*>	particles;
	
	Particle*			selectedParticle;
	
	Vec3f				gravityDir;
};

void Cloth::setup()
{
	enableAccelerometer();
	
    physics	= new ParticleSystem( 0.0f, 0.0002f );
	physics->clear();
    
	float gridStepX = (float)( getWindowWidth() * 0.9f / GRID_X_RES );
	float gridStepY = (float)( getWindowHeight() * 0.9f / GRID_Y_RES );
	
	for( int y=0; y<GRID_Y_RES; y++ ){
		for( int x=0; x<GRID_X_RES; x++ ){
			Vec3f pos = Vec3f( x * gridStepX + getWindowWidth() * 0.05f, y * gridStepY + 20.0f, 0.0f );
			particles.push_back( physics->makeParticle( 0.2f, pos.x, pos.y, pos.z ) );
			if( x > 0 )
				physics->makeSpring( particles[y*GRID_X_RES + x - 1], particles[y*GRID_X_RES + x], SPRING_STRENGTH, SPRING_DAMPING, gridStepX );
		}
	}

	
	for( int y=1; y<GRID_Y_RES; y++ ){
		for( int x=0; x<GRID_X_RES; x++ ){
			physics->makeSpring( particles[ (y - 1) * GRID_X_RES + x], particles[y*GRID_X_RES + x], SPRING_STRENGTH, SPRING_DAMPING, gridStepY );
		}
	}
	
	int p1i = 0;
	int p2i = GRID_X_RES-1;
	int p3i = (GRID_Y_RES-1)*GRID_X_RES;
	int p4i = (GRID_Y_RES-1)*GRID_X_RES+GRID_X_RES-1;
	
	particles[p1i]->setFixed( true );
	particles[p2i]->setFixed( true );
	particles[p3i]->setFixed( true );
	particles[p4i]->setFixed( true );
	
	particles[p1i]->setLocked( true );
	particles[p2i]->setLocked( true );
	particles[p3i]->setLocked( true );
	particles[p4i]->setLocked( true );
	
	particles[p1i]->position.set( 0.0f, 0.0f, 0.0f );
	particles[p2i]->position.set( getWindowWidth(), 0.0f, 0.0f );
	particles[p3i]->position.set( 0.0f, getWindowHeight(), 0.0f );
	particles[p4i]->position.set( getWindowWidth(), getWindowHeight(), 0.0f );
}

void Cloth::accelerated( AccelEvent event )
{
	gravityDir = event.getData() * Vec3f( 0.1f, -0.1f, 0.1f );
}

void Cloth::touchesBegan( TouchEvent event )
{
	const vector<TouchEvent::Touch> touches = getActiveTouches();
    if( touches.size() == 1 ){
		Vec2f pos = touches.begin()->getPos();
		Particle* closest;
		float closestDist = 1000.0f;
		
		vector<Particle*>::iterator it;
		for( it = particles.begin(); it != particles.end(); ++it ){
			float dist = (*it)->position.distance( Vec3f( pos, 0.0f ) );
			if( dist < closestDist ){
				closestDist = dist;
				closest = (*it);
			}
		}
		
		selectedParticle = closest;
		selectedParticle->setFixed( true );
		selectedParticle->position.set( pos.x, pos.y, 0);
		selectedParticle->velocity.set( 0.0f, 0.0f, 0.0f );
    }
}

void Cloth::touchesMoved( TouchEvent event )
{
	const vector<TouchEvent::Touch> touches = getActiveTouches();
    if( touches.size() == 1 ){
		Vec2f pos = touches.begin()->getPos();
		selectedParticle->position.set( pos.x, pos.y, 0);
		selectedParticle->velocity.set( 0.0f, 0.0f, 0.0f );
    }
}

void Cloth::touchesEnded( TouchEvent event )
{
	selectedParticle->setFixed( false );
}

void Cloth::update()
{
	physics->setGravity( gravityDir.x, gravityDir.y, gravityDir.z );
    physics->tick(); 
}

void Cloth::draw()
{
    gl::clear( Color( 1.0f, 1.0f, 1.0f ) );
    gl::setMatricesWindow( getWindowSize() );        
	drawNetwork();
	
//	if( getElapsedFrames()%30 == 0 )
//		console() << physics->numberOfParticles() << " PARTICLES " << getAverageFps() << " FPS" << std::endl;

   
}


// ME ////////////////////////////////////////////

void Cloth::drawNetwork()
{      
    // draw vertices
    gl::color(Color(0.63f, 0.63f, 0.63f));
    for ( int i = 0; i < physics->numberOfParticles(); ++i )
    {
        Particle* v = physics->getParticle( i );
        gl::drawSolidCircle( v->position.xy(), NODE_SIZE/2.0f );
    }
    
    // draw springs 
    gl::color(Color::black());
    for ( int i = 0; i < physics->numberOfSprings(); ++i )
    {
        Spring* e = physics->getSpring( i );
        Particle* a = e->getOneEnd();
        Particle* b = e->getTheOtherEnd();
        gl::drawLine( a->position.xy(), b->position.xy() );                 
    }
}



CINDER_APP_COCOA_TOUCH( Cloth, RendererGl )
