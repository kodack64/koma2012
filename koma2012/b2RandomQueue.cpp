
#include "b2RandomQueue.h"

b2RandomQueue::b2RandomQueue(GraphicApi* _gapi,int _img_ball,int _img_square,int _img_triangle){
	gapi=_gapi;
	img_ball=_img_ball;
	img_square=_img_square;
	img_triangle=_img_triangle;
}

b2RandomQueue::~b2RandomQueue(){
}

Color4f BallColor[8]={
	Color4f(220,20,20,255),
	Color4f(20,220,20,255),
	Color4f(20,20,220,255),
	Color4f(20,220,220,255),
	Color4f(220,20,220,255),
	Color4f(220,220,20,255),
	Color4f(220,220,220,255),
	Color4f(20,20,20,255)
};

void b2RandomQueue::MoreNumber(){
	number++;
	if(number>8)number=8;
}

b2Object* b2RandomQueue::CreateBallObject(b2Vec2 p,b2Vec2 v){
	b2Object* obj;
	
	obj=new b2Object(gapi);
	obj->InitAsBall(img_ball);
	obj->bodyDef.position=p;
	obj->bodyDef.linearVelocity=v;
	obj->number=rand()%number;
	obj->toColor=obj->myColor=BallColor[obj->number];
	return obj;
}

b2Object* b2RandomQueue::CreateSquareObject(b2Vec2 p,b2Vec2 v){
	b2Object* obj;
	
	obj=new b2Object(gapi);
	obj->InitAsSquare(img_square);
	obj->bodyDef.position=p;
	obj->bodyDef.linearVelocity=v;
	obj->number=rand()%number;
	obj->toColor=obj->myColor=BallColor[obj->number];
	return obj;
}
b2Object* b2RandomQueue::CreateTriangleObject(b2Vec2 p,b2Vec2 v){
	b2Object* obj;
	
	obj=new b2Object(gapi);
	obj->InitAsTriangle(img_triangle);
	obj->bodyDef.position=p;
	obj->bodyDef.linearVelocity=v;
	obj->number=rand()%number;
	obj->toColor=obj->myColor=BallColor[obj->number];
	return obj;
}

void b2RandomQueue::Init(int queueNumber,int _kind,int _number,b2Body* _cursor){
	cursor=_cursor;
	kind=_kind;
	number=_number;
	for(int i=0;i<queueNumber;i++){
		switch(rand()%_kind){
		case 0:
			q.push_back(this->CreateBallObject(b2Vec2(0,0),b2Vec2(0,0)));
			break;
		case 1:
			q.push_back(this->CreateSquareObject(b2Vec2(0,0),b2Vec2(0,0)));
			break;
		case 2:
			q.push_back(this->CreateTriangleObject(b2Vec2(0,0),b2Vec2(0,0)));
			break;
		}
	}
	c=0;
}
void b2RandomQueue::Close(){
	for(unsigned int i=0;i<q.size();i++){
		delete q[i];
	}
	q.resize(0);
}
void b2RandomQueue::Draw(bool inputReady){
	for(unsigned int i=0;i<q.size();i++){
		b2Object* obj=q[(i+c)%q.size()];
		float zc=obj->zoom;
		Color4f cc=obj->myColor;
		gapi->DrawImage(640,60+i*45,0,0,0,0,zc/1.5f,obj->rot,cc,obj->myImage);
	}
	if(inputReady){
		Color4f qc = q[c]->myColor;
	//	gapi->DrawImage(60,60,0,0,0,0,q[c]->zoom,q[c]->rot,qc,q[c]->myImage);
		qc.alpha=200;
		gapi->DrawImage(M2P(cursor->GetPosition().x),100,0,0,0,0,q[c]->zoom,q[c]->rot,qc,q[c]->myImage);
	}
}
b2Object* b2RandomQueue::Pop(){
	b2Object* obj;
	obj=q[c];
	switch(rand()%kind){
	case 0:
		q[c]=(this->CreateBallObject(b2Vec2(0,0),b2Vec2(0,0)));
		break;
	case 1:
		q[c]=(this->CreateSquareObject(b2Vec2(0,0),b2Vec2(0,0)));
		break;
	case 2:
		q[c]=(this->CreateTriangleObject(b2Vec2(0,0),b2Vec2(0,0)));
		break;
	}
	c=(c+1)%q.size();
	return obj;
}
