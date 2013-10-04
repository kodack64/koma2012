
#pragma once

#include "Common.h"
#include "GameCommon.h"
#include "b2Object.h"

class b2RandomQueue{
private:
	vector <b2Object*> q;
	int c;
	int kind;
	int number;

	GraphicApi* gapi;
	b2Body* cursor;
	int img_ball;
	int img_square;
	int img_triangle;
public:
	b2RandomQueue(GraphicApi* gapi,int img_ball,int img_square,int img_triangle);
	virtual ~b2RandomQueue();
	virtual void Init(int queueNumber,int kind,int number,b2Body* cursor);
	virtual void Close();
	virtual void Draw(bool inputReady);
	virtual b2Object* Pop();
	virtual b2Object* CreateBallObject(b2Vec2 p,b2Vec2 v);
	virtual b2Object* CreateSquareObject(b2Vec2 p,b2Vec2 v);
	virtual b2Object* CreateTriangleObject(b2Vec2 p,b2Vec2 v);
	virtual void MoreNumber();
};