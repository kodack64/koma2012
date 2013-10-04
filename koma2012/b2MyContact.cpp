
#include "b2MyContact.h"

MyContactListener::MyContactListener(b2Connection* _con){
	con=_con;
}
void MyContactListener::BeginContact(b2Contact* cont){
	b2Body* body1=cont->GetFixtureA()->GetBody();
	b2Body* body2=cont->GetFixtureB()->GetBody();
	if(body1!=body2){
		b2Object* obj1=(b2Object*)(body1->GetUserData());
		b2Object* obj2=(b2Object*)(body2->GetUserData());
		if(obj1!=NULL && obj2!=NULL){
			if(obj1->isMagnet && obj2->isMagnet){
				con->MakeRelation(body1,body2);
			}
		}
	}
}

void MyContactListener::EndContact(b2Contact* cont){
	b2Body* body1=cont->GetFixtureA()->GetBody();
	b2Body* body2=cont->GetFixtureB()->GetBody();
	if(body1!=body2){
		b2Object* obj1=(b2Object*)(body1->GetUserData());
		b2Object* obj2=(b2Object*)(body2->GetUserData());
		if(obj1!=NULL && obj2!=NULL){
			if(obj1->isMagnet && obj2->isMagnet){
				con->DestroyRelation(body1,body2);
			}
		}
	}
}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
}
void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){ 
}
