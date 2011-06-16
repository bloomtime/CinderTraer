// adapted from http://murderandcreate.com/physics/random_arboretum/

#include <sstream>
#include "cinder/app/AppCocoaTouch.h"
#include "cinder/app/TouchEvent.h"
#include "cinder/app/Renderer.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Spring.h"

using namespace ci;
using namespace ci::app;
using namespace traer::physics;

#define NODE_SIZE 10
#define EDGE_LENGTH 20
#define EDGE_STRENGTH 0.2
#define SPACER_STRENGTH 1000

class RandomArboretumApp : public AppCocoaTouch {
  public:
	virtual void	setup();
	virtual void	update();
	virtual void	draw();
	virtual void	touchesBegan( TouchEvent event );
	virtual void	touchesMoved( TouchEvent event );

    void drawNetwork();
    void updateCentroid();
    void addSpacersToNode( Particle *p, Particle *r );
    void makeEdgeBetween( Particle *a, Particle *b );
    void initialize();
    void addNode();    

    ParticleSystem* physics;
    float scale;
    float centroidX;
    float centroidY;
    
    float prevT;
};

void RandomArboretumApp::setup()
{
    scale = 1;
    centroidX = 0;
    centroidY = 0;    

    prevT = getElapsedSeconds();
    
    //size( 400, 400 );
    //smooth();
    //strokeWeight( 2 );
    //ellipseMode( CENTER );       
    
    physics = new ParticleSystem( 0, 0.1 );
    
    // Runge-Kutta, the default integrator is stable and snappy,
    // but slows down quickly as you add particles.
    // 500 particles = 7 fps on my machine
    
    // Try this to see how Euler is faster, but borderline unstable.
    // 500 particles = 24 fps on my machine
    //physics.setIntegrator( ParticleSystem.MODIFIED_EULER ); 
    
    // Now try this to see make it more damped, but stable.
    //physics.setDrag( 0.2 );
    
    
    //textFont( loadFont( "AkzidenzGroteskBQ-Regular-14.vlw" ) );
    
    initialize();    
}

void RandomArboretumApp::touchesBegan( TouchEvent event )
{
    if (event.getTouches.size() > 1) {
        physics->clear();
    }
    else {
        addNode();
    }
}

void RandomArboretumApp::touchesMoved( TouchEvent event )
{
    addNode();
}

void RandomArboretumApp::update()
{
    physics->tick(); 
    if ( physics->numberOfParticles() > 1 ) {
        updateCentroid();
    }
}

void RandomArboretumApp::draw()
{
    gl::clear( Color( 1.0f, 1.0f, 1.0f ) );
    gl::setMatricesWindow( getWindowSize() );        
    
    float t = getElapsedSeconds();
    float fps = 1.0/(t-prevT);
    prevT = t;
    
    //std::stringstream ss;
    console() << physics->numberOfParticles() << " PARTICLES " << fps << " FPS" << std::endl;
    //gl::drawString( ss.str(), Vec2f(10, 20), Color( 0, 0, 0 ) );

    gl::pushModelView();
    gl::translate( getWindowCenter() );
    gl::scale( Vec3f( scale, scale, 1.0f ) );
    gl::translate( Vec2f(-centroidX, -centroidY) );
    drawNetwork(); 
    gl::popModelView();
}


// ME ////////////////////////////////////////////

void RandomArboretumApp::drawNetwork()
{      
    // draw vertices
    gl::color(Color(0.63f, 0.63f, 0.63f));
    for ( int i = 0; i < physics->numberOfParticles(); ++i )
    {
        Particle* v = physics->getParticle( i );
        gl::drawSolidCircle( Vec2f(v->getPosition()->x, v->getPosition()->y), NODE_SIZE/2.0f );
    }
    
    // draw edges 
    gl::color(Color::black());
    for ( int i = 0; i < physics->numberOfSprings(); ++i )
    {
        Spring* e = physics->getSpring( i );
        Particle* a = e->getOneEnd();
        Particle* b = e->getTheOtherEnd();
        gl::drawLine( Vec2f(a->getPosition()->x, a->getPosition()->y), Vec2f(b->getPosition()->x, b->getPosition()->y) );                 
    }
}


void RandomArboretumApp::updateCentroid()
{
    float xMax = -FLT_MAX, 
          xMin =  FLT_MAX, 
          yMin =  FLT_MAX, 
          yMax = -FLT_MAX;
    
    for ( int i = 0; i < physics->numberOfParticles(); ++i )
    {
        Particle* p = physics->getParticle( i );
        xMax = math<float>::max( xMax, p->getPosition()->x );
        xMin = math<float>::min( xMin, p->getPosition()->x );
        yMin = math<float>::min( yMin, p->getPosition()->y );
        yMax = math<float>::max( yMax, p->getPosition()->y );
    }
    float deltaX = xMax-xMin;
    float deltaY = yMax-yMin;
    
    centroidX = xMin + 0.5*deltaX;
    centroidY = yMin + 0.5*deltaY;
    
    if ( deltaY > deltaX )
        scale = getWindowHeight()/(deltaY+50);
    else
        scale = getWindowWidth()/(deltaX+50);
}

void RandomArboretumApp::addSpacersToNode( Particle* p, Particle* r )
{
    for ( int i = 0; i < physics->numberOfParticles(); ++i )
    {
        Particle* q = physics->getParticle( i );
        if ( p != q && p != r )
            physics->makeAttraction( p, q, -SPACER_STRENGTH, 20 );
    }
}

void RandomArboretumApp::makeEdgeBetween( Particle* a, Particle* b )
{
    physics->makeSpring( a, b, EDGE_STRENGTH, EDGE_STRENGTH, EDGE_LENGTH );
}

void RandomArboretumApp::initialize()
{
    physics->clear();
    physics->makeParticle();
}

void RandomArboretumApp::addNode()
{ 
    Particle* p = physics->makeParticle();
    Particle* q = physics->getParticle( Rand::randInt(0, physics->numberOfParticles() - 1) );
    while ( q == p )
        q = physics->getParticle( Rand::randInt(0, physics->numberOfParticles() - 1) );
    addSpacersToNode( p, q );
    makeEdgeBetween( p, q );
    Vec2f jiggle = Rand::randVec2f();
    p->getPosition()->set( q->getPosition()->x + jiggle.x, q->getPosition()->y + jiggle.y, 0 );
}

CINDER_APP_COCOA_TOUCH( RandomArboretumApp, RendererGl )
