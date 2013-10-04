
#include "b2Factory.h"

void b2Factory::CreateParticle(int num,b2Vec2 dp,Color4f col){
	b2Body* body;
	b2Fixture* fixture;
	b2Object* obj;
	b2BodyDef bodyDef;

//	currentScore+=num;
	currentScore+=1;
	for(int i=0;i<num;i++){
		obj = new b2Object(gapi);
		obj->InitAsParticle(img_cursor,col);
		bodyDef = obj->bodyDef;
		bodyDef.position=dp;
		body = fxworld->CreateBody(&(bodyDef));
		body->ApplyForceToCenter(b2Vec2(P2M(rand()%1000-500),P2M(rand()%400-200)));
		fixture=body->CreateFixture(&(obj->fixtureDef));
		body->ResetMassData();
		body->SetUserData(obj);
	}
}

void b2Factory::UpdateDeadParticleList(){

	// check fx world body
	// push back deadParticleList

	b2Body* body;
	body=fxworld->GetBodyList();
	while(body!=NULL){
		if(body->GetUserData()!=NULL){
			b2Object* obj=(b2Object*)(body->GetUserData());
			if(obj!=NULL){
				if(body->GetPosition().y<P2M(0)){
					deadParticleList.push_back(body);
				}
			}
		}
		body=body->GetNext();
	}
}

void b2Factory::RemoveDeadParticle(){
	// remove elements of deadParticleList from world
	// when remove, generate ScoreParticle to the fxworld

	b2Object* obj;
	Color4f col;
	b2Vec2 deadPoint;

	for(unsigned int i=0;i<deadParticleList.size();i++){
		if(deadParticleList[i]->GetUserData()!=NULL){
			obj = (b2Object*)deadParticleList[i]->GetUserData();
			col = obj->myColor;
			deadPoint=deadParticleList[i]->GetPosition();

			if(obj->isMagnet){
				this->CreateScoreParticle(deadPoint,col);
			}
			SAFE_DELETE(obj);
			deadParticleList[i]->SetUserData(NULL);
		}
		fxworld->DestroyBody(deadParticleList[i]);
	}
	deadParticleList.clear();
}
