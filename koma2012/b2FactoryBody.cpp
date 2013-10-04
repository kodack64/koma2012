
#include "b2Factory.h"

void b2Factory::CreateBody(){
	b2Object* obj;
	b2Body* body;
	b2Fixture* fixture;
	obj = b2r->Pop();
	obj->bodyDef.position=b2Vec2(cursor->GetPosition().x,P2M(100));
	obj->bodyDef.linearVelocity=b2Vec2(0,0);
	body=world->CreateBody(&(obj->bodyDef));
	fixture=body->CreateFixture(&(obj->fixtureDef));
	body->ResetMassData();
	body->SetUserData(obj);
	b2c->MakeNode(body);
//	magnet[magnetNum]=body;
	magnetNum++;
}

void b2Factory::CreateRandomBody(){
	b2Object* obj;
	b2Body* body;
	b2Fixture* fixture;

	switch(rand()%2){
	case 0:
		obj=b2r->CreateBallObject(b2Vec2(0,0),b2Vec2(0,0));
		break;
	case 1:
		obj=b2r->CreateSquareObject(b2Vec2(0,0),b2Vec2(0,0));
		break;
	}
	if(rand()%2){
		obj->bodyDef.position=b2Vec2(P2M(40),P2M(140));
		obj->bodyDef.linearVelocity=b2Vec2(P2M(rand()%100),0);
	}else{
		obj->bodyDef.position=b2Vec2(P2M(560),P2M(140));
		obj->bodyDef.linearVelocity=b2Vec2(P2M(-rand()%100),0);
	}
	body=world->CreateBody(&(obj->bodyDef));
	fixture=body->CreateFixture(&(obj->fixtureDef));
	body->ResetMassData();
	body->SetUserData(obj);
	b2c->MakeNode(body);
	magnetNum++;
}

void b2Factory::UpdateStableFlag(){
	// update sleep flag of elements in world
	// update flag isAllSleep
	// find dead body and update deadBodyList

	isAllSleep=true;
	b2Body* body;
	b2Vec2 v;
	Color4f c;

	body=world->GetBodyList();
	magnetCount=0;
	while(body!=NULL){
		if(body->GetUserData()!=NULL){
			b2Object* obj=(b2Object*)(body->GetUserData());
			if(obj!=NULL){
				// kind is magnet , has velocity
				if(obj->isMagnet){
					if(body->GetLinearVelocity().Length()>P2M(10)){
						isAllSleep=false;
					}
					body->SetSleepingAllowed(true);
				}
				// count rest objects
				if(obj->isMagnet && obj->light){
					magnetCount++;
				}
			}
		}
		body=body->GetNext();
	}
}
void b2Factory::UpdateDeadBodyList(){

	// update sleep flag of elements in world
	// update flag isAllSleep
	// find dead body and update deadBodyList

	b2Body* body;
	b2Object* obj;
	b2Vec2 v;
	Color4f c;
	int graphElements;

	body=world->GetBodyList();
	magnetCount=0;

	b2c->UpdateGraph();
	while(body!=NULL){
		if(body->GetUserData()!=NULL){
			obj=(b2Object*)(body->GetUserData());
			if(obj!=NULL){
				// kind is magnet , has velocity
				if(obj->isMagnet){
					// if hit , remove body
					graphElements=b2c->GetGraphElements(body);
					obj->light=(graphElements>=2);
//					if(graphElements>=4 && isAllSleep){
					if(graphElements>=4){
						deadBodyList.push_back(body);
					}
				}
				// count rest objects
				if(obj->isMagnet && obj->light){
					magnetCount++;
				}
			}
		}
		body=body->GetNext();
	}
}

void b2Factory::RemoveDeadBody(){

	// remove elements of deadBodyList from world
	// when remove, generate DeadParticle

	Color4f col;
	b2Object* obj;
	b2Vec2 deadPoint;
	magnetNum-=deadBodyList.size();
	for(unsigned int i=0;i<deadBodyList.size();i++){
		if(deadBodyList[i]->GetUserData()!=NULL){

			obj = (b2Object*)deadBodyList[i]->GetUserData();
			col = obj->myColor;

			deadPoint = deadBodyList[i]->GetPosition();

			if(obj->isMagnet){
				b2c->DestroyNode(deadBodyList[i]);
				this->CreateParticle(5,deadPoint,col);
			}

			SAFE_DELETE(obj);
			deadBodyList[i]->SetUserData(NULL);
		}
		world->DestroyBody(deadBodyList[i]);
	}
	deadBodyList.clear();
}
