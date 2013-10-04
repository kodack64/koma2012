

#include "b2Factory.h"

void b2Factory::CreateField(){
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2ChainShape chain;
	int cent;
	b2Vec2 v[4];

	bodyDef.type=b2_staticBody;
	bodyDef.userData=NULL;

	cent= min(gapi->GetScreenHeight() , gapi->GetScreenWidth())/2;
	bodyDef.position=b2Vec2(P2M(cent),P2M(cent));
	v[0].Set(P2M(-cent),P2M(-cent));
	v[1].Set(P2M(-cent),P2M(cent));
	v[2].Set(P2M(cent),P2M(cent));
	v[3].Set(P2M(cent),P2M(-cent));
	chain.CreateLoop(v,4);
	fixtureDef.shape=&chain;

	b2Body* body=world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
}

void b2Factory::CreateFxField(){
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2EdgeShape edge;

	bodyDef.type=b2_staticBody;
	bodyDef.userData=NULL;
	bodyDef.position=b2Vec2(P2M(gapi->GetScreenHeight()),P2M(gapi->GetScreenHeight()/2));
	edge.Set(b2Vec2(0,P2M(-gapi->GetScreenHeight())),b2Vec2(0,P2M(gapi->GetScreenHeight())));
	fixtureDef.shape=&edge;
	body=fxworld->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	bodyDef.position=b2Vec2(P2M(gapi->GetScreenWidth()),P2M(gapi->GetScreenHeight()/2));
	body=fxworld->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);


	bodyDef.type=b2_staticBody;
	bodyDef.userData=NULL;
	bodyDef.position=b2Vec2(P2M(700),P2M(260));
	edge.Set(
		b2Vec2(P2M(-200),0)
		,b2Vec2(P2M(200),0)
		);
	fixtureDef.shape=&edge;
	body=fxworld->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

}

void b2Factory::CreateCursor(){
	b2Body* body;
	b2Fixture* fixture;
	b2Object* obj=new b2Object(gapi);
	obj->InitAsCursor(img_cursor);
	body=world->CreateBody(&(obj->bodyDef));
	fixture=body->CreateFixture(&(obj->fixtureDef));
	body->ResetMassData();
	body->SetUserData(obj);
	cursor=body;
}


