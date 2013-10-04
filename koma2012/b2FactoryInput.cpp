
#include "b2Factory.h"


void b2Factory::ProcessCursor(){

	// update cursor position and cursor velocity for my input process

	POINT p=iapi->mouse->GetPoint();
	b2Vec2 pv;

	pv=b2Vec2(P2M(max(20,min(580,p.x))),P2M(p.y));
	pv=pv-cursor->GetPosition();
	cursor->SetLinearVelocity(b2Vec2(pv.x*10,pv.y*10));
}



void b2Factory::ProcessInput(){

	// process click
	// generate new body to world
	// apply force by input data

	if(restCount>0 && inputReady){
		inputReady=false;
//		restCount--;
		this->CreateBody();
	}
}
