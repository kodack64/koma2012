

#include "b2Factory.h"


void b2Factory::CreateScoreParticle(b2Vec2 dp,Color4f col){
	b2Body* body;
	b2Fixture* fixture;
	b2Object* obj;
	
	obj=new b2Object(gapi);
	obj->InitAsScoreParticle(img_cursor,col);
	b2BodyDef bodyDef = obj->bodyDef;
//	bodyDef.position=dp;
	b2Vec2 fv(700,600);
	fv.x+=(dp.x/600.0f)*100.0f;
	fv.x=P2M(fv.x);
	fv.y=P2M(fv.y);

	bodyDef.position=fv;
	body=fxworld->CreateBody(&(bodyDef));
	body->ApplyForceToCenter(b2Vec2(P2M(rand()%400-200),0));
	fixture=body->CreateFixture(&(obj->fixtureDef));
	body->ResetMassData();
	body->SetUserData(obj);
	bodyStock.push_back(body);
}

void b2Factory::RemoveScoreParticle(){
	if(bodyStock.size()>30){
		for(int i=0;i<30;i++){
			fxworld->DestroyBody(bodyStock[i]);
		}
		bodyStock.erase(bodyStock.begin(),bodyStock.begin()+30);
	}
}

