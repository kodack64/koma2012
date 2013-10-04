
#pragma once
#include "GameCommon.h"
#include "b2Object.h"
#include "b2Connection.h"

class MyContactListener : public b2ContactListener
{
private:
	b2Connection* con;
public:
	MyContactListener(b2Connection* _con);
	void BeginContact(b2Contact* cont);
	void EndContact(b2Contact* cont);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};