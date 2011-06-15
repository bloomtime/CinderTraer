// adapted from http://murderandcreate.com/physics/random_arboretum/

#include "cinder/app/AppCocoaTouch.h"
#include "cinder/app/Renderer.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Spring.h"

using namespace ci;
using namespace ci::app;
using namespace traer::physics;

#define NODE_SIZE 10;
#define EDGE_LENGTH 20;
#define EDGE_STRENGTH 0.2;
#define SPACER_STRENGTH 1000;

class RandomArboretumApp : public AppCocoaTouch {
  public:
	virtual void	setup();
	virtual void	update();
	virtual void	draw();
	virtual void	mouseDown( MouseEvent event );
	virtual void	mouseDrag( MouseEvent event );

    void drawNetwork();
    void updateCentroid();
    void addSpacersToNode( Particle p, Particle r );
    void makeEdgeBetween( Particle a, Particle b );
    void initialize();
    void addNode();    

    ParticleSystem physics;
    float scale;
    float centroidX;
    float centroidY;
};

void RandomArboretumApp::setup()
{
    scale = 1;
    centroidX = 0;
    centroidY = 0;    

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

void RandomArboretumApp::mouseDown( MouseEvent event )
{
    addNode();
}

void RandomArboretumApp::mouseDrag( MouseEvent event )
{
    addNode();
}

void RandomArboretumApp::update()
{
    physics.tick(); 
    if ( physics.numberOfParticles() > 1 ) {
        updateCentroid();
    }
}

void RandomArboretumApp::draw()
{
    gl::clear( Color( 1.0f, 1.0f, 1.0f ) );
    gl::setMatricesWindow( getWindowSize() );        
    
    gl::drawString( "" + physics.numberOfParticles() + " PARTICLES\n" + (int)getFrameRate() + " FPS",
                    Vec2f(10, 20), ColorA( 0, 0, 0, 0 ) );

    gl::pushModelView();
    gl::translate( getWindowCenter() );
    gl::scale( Vec2f( scale, scale ) );
    gl::translate( Vec2f(-centroidX, -centroidY) );
    
    drawNetwork(); 

    gl::popModelView();
}


// ME ////////////////////////////////////////////

void RandomArboretumApp::drawNetwork()
{      
    // draw vertices
    fill( 160 );
    noStroke();
    for ( int i = 0; i < physics.numberOfParticles(); ++i )
    {
        Particle v = physics.getParticle( i );
        ellipse( v.position().x(), v.position().y(), NODE_SIZE, NODE_SIZE );
    }
    
    // draw edges 
    stroke( 0 );
    beginShape( LINES );
    for ( int i = 0; i < physics.numberOfSprings(); ++i )
    {
        Spring e = physics.getSpring( i );
        Particle a = e.getOneEnd();
        Particle b = e.getTheOtherEnd();
        vertex( a.position().x(), a.position().y() );
        vertex( b.position().x(), b.position().y() );
    }
    endShape();
}


void RandomArboretumApp::updateCentroid()
{
    float 
    xMax = Float.NEGATIVE_INFINITY, 
    xMin = Float.POSITIVE_INFINITY, 
    yMin = Float.POSITIVE_INFINITY, 
    yMax = Float.NEGATIVE_INFINITY;
    
    for ( int i = 0; i < physics.numberOfParticles(); ++i )
    {
        Particle p = physics.getParticle( i );
        xMax = max( xMax, p.position().x() );
        xMin = min( xMin, p.position().x() );
        yMin = min( yMin, p.position().y() );
        yMax = max( yMax, p.position().y() );
    }
    float deltaX = xMax-xMin;
    float deltaY = yMax-yMin;
    
    centroidX = xMin + 0.5*deltaX;
    centroidY = yMin +0.5*deltaY;
    
    if ( deltaY > deltaX )
        scale = getWindowHeight()/(deltaY+50);
    else
        scale = getWindowWidth()/(deltaX+50);
}

void RandomArboretumApp::addSpacersToNode( Particle p, Particle r )
{
    for ( int i = 0; i < physics.numberOfParticles(); ++i )
    {
        Particle q = physics.getParticle( i );
        if ( p != q && p != r )
            physics.makeAttraction( p, q, -SPACER_STRENGTH, 20 );
    }
}

void RandomArboretumApp::makeEdgeBetween( Particle a, Particle b )
{
    physics.makeSpring( a, b, EDGE_STRENGTH, EDGE_STRENGTH, EDGE_LENGTH );
}

void RandomArboretumApp::initialize()
{
    physics.clear();
    physics.makeParticle();
}

void RandomArboretumApp::addNode()
{ 
    Particle p = physics.makeParticle();
    Particle q = physics.getParticle( (int)random( 0, physics.numberOfParticles()-1) );
    while ( q == p )
        q = physics.getParticle( (int)random( 0, physics.numberOfParticles()-1) );
    addSpacersToNode( p, q );
    makeEdgeBetween( p, q );
    p.position().set( q.position().x() + random( -1, 1 ), q.position().y() + random( -1, 1 ), 0 );
}

CINDER_APP_COCOA_TOUCH( RandomArboretumApp, RendererGl )
