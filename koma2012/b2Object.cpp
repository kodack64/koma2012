
#include "b2Object.h"

b2Object::b2Object(GraphicApi* _gapi){
	gapi=_gapi;
}

b2Object::~b2Object(){
}

void b2Object::InitAsCursor(ImageId img){
	light=false;
	trace.clear();
	rot=0.0;
	zoom=0.75f;
	myImage=img;
	isMagnet=false;

	toColor=myColor=Color4f(0,0,0,255);
	bodyDef.type=b2_kinematicBody;
	bodyDef.position=b2Vec2(P2M(300),P2M(300));
	size=gapi->GetImageWidth(img)*zoom/2;
	circleShape.m_radius=P2M(size);
	fixtureDef.shape=&circleShape;
	fixtureDef.density=10.0;
	fixtureDef.isSensor=true;
}

void b2Object::InitAsBall(ImageId img){
	myImage=img;
	nodeId=-1;
	trace.clear();
	light=false;
	rot=0.0;
	zoom=0.2f+0.02f*(rand()%10-5);
	isMagnet=true;

	number=0;
	toColor=myColor=Color4f(255,255,255,255);

	bodyDef.type=b2_dynamicBody;
	bodyDef.linearDamping=1.0f;
	bodyDef.angularDamping=1.0f;
	bodyDef.allowSleep=true;
	size=gapi->GetImageWidth(img)*zoom/2;
	circleShape.m_radius=P2M(size);
	fixtureDef.shape=&circleShape;
	fixtureDef.density=1.0f;
	fixtureDef.friction=0.4f;
	fixtureDef.restitution=0.3f;
}

void b2Object::InitAsSquare(ImageId img){
	nodeId=-1;
	myImage=img;
	trace.clear();
	light=false;
	isMagnet=true;
	rot=0.0;
	zoom=0.2f+0.02f*(rand()%10-5);

	number=0;
	toColor=myColor=Color4f(255,255,255,255);

	size=gapi->GetImageWidth(img)*zoom/2;
	polygonShape.SetAsBox(P2M(gapi->GetImageWidth(img)*zoom/2),P2M(gapi->GetImageHeight(img)*zoom/2),b2Vec2(0,0),rot);
	bodyDef.type=b2_dynamicBody;
	bodyDef.linearDamping=1.0f;
	bodyDef.angularDamping=1.0f;
	bodyDef.allowSleep=true;
	fixtureDef.shape=&polygonShape;
	fixtureDef.density=0.2f;
	fixtureDef.friction=0.4f;
	fixtureDef.restitution=0.3f;
}

void b2Object::InitAsTriangle(ImageId img){
	nodeId=-1;
	myImage=img;
	trace.clear();
	light=false;
	isMagnet=true;
	rot=0.0;
	zoom=0.2f;

	number=0;
	toColor=myColor=Color4f(255,255,255,255);

	size=gapi->GetImageWidth(img)*zoom/2;
	polygonShape.SetAsBox(P2M(gapi->GetImageWidth(img)*zoom/2),P2M(gapi->GetImageHeight(img)*zoom/2),b2Vec2(0,0),rot);
	bodyDef.type=b2_dynamicBody;
	bodyDef.linearDamping=1.0f;
	bodyDef.angularDamping=1.0f;
	bodyDef.allowSleep=true;
	fixtureDef.shape=&polygonShape;
	fixtureDef.density=0.2f;
	fixtureDef.friction=0.4f;
	fixtureDef.restitution=0.3f;
}

void b2Object::InitAsParticle(ImageId img,Color4f col){
	light=false;
	trace.clear();

	number=rand()%10;

	rot=0.0;
	zoom=0.25f;
	myImage=img;
	myColor=col;
	myColor.alpha/=2;
	toColor=myColor;
	myColor.alpha=255;
	toColor.alpha=255;
	isMagnet=false;

	bodyDef.type=b2_dynamicBody;
	bodyDef.position=b2Vec2(P2M(300),P2M(300));
	size=gapi->GetImageWidth(img)*zoom/2;
	circleShape.m_radius=P2M(size);
	fixtureDef.shape=&circleShape;
	fixtureDef.density=1.0;
	fixtureDef.isSensor=true;
}

void b2Object::InitAsScoreParticle(ImageId img,Color4f col){
	light=false;
	trace.clear();
	rot=0.0;
	zoom=0.20f;
	myImage=img;
	myColor=col;
	myColor.alpha=255;
	toColor=myColor;
	toColor.alpha=255;
	isMagnet=false;

	bodyDef.type=b2_dynamicBody;
	bodyDef.position=b2Vec2(P2M(300),P2M(300));
	size=gapi->GetImageWidth(img)*zoom/2;
	circleShape.m_radius=P2M(size);
	fixtureDef.shape=&circleShape;
	fixtureDef.density=1.0;
	fixtureDef.isSensor=false;
}

