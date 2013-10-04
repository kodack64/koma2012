
#pragma once

#include "GameCommon.h"

using namespace std;

enum b2ObjectKind{
	Circle,
	Square
};

//match=-1 : cursor
//match=-2 : magnet
//match=0  : particle/scoreParticle

class b2Object{
public:
	int nodeId;
	bool light;
	bool isMagnet;
	
	int number;

	float zoom;
	float rot;
	double size;

	vector <b2Vec2> trace;

	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;
	b2CircleShape circleShape;
	b2PolygonShape polygonShape;

	ImageId myImage;
	Color4f myColor;
	Color4f toColor;

	GraphicApi *gapi;

	b2Object(GraphicApi* _gapi);
	virtual ~b2Object();

	virtual void InitAsCursor(ImageId img);
	virtual void InitAsBall(ImageId img);
	virtual void InitAsSquare(ImageId img);
	virtual void InitAsTriangle(ImageId img);
	virtual void InitAsParticle(ImageId img,Color4f col);
	virtual void InitAsScoreParticle(ImageId img,Color4f col);

};