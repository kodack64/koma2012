
#pragma once

#include "GameCommon.h"
#include "b2MyContact.h"
#include "b2Connection.h"
#include "b2RandomQueue.h"

class b2Factory{
private:
	GraphicApi* gapi;
	InputApi* iapi;
	vector <b2Body*> deadBodyList;
	vector <b2Body*> deadParticleList;
	vector <b2Body*> deadScoreList;

	vector <b2Body*> bodyStock;

	int maxMagnetNum;
	int balltimediv;
	int prevballtime;

	long frameCount;
	int frameDiv;
	int currentScore;
	int restCount;
	int showScore;
	int magnetCount;
	int magnetNum;
	bool isAllSleep;
	bool inputReady;
	int inputCount;

	b2World* world;
	b2World* fxworld;
//	b2Body* magnet[MAX_MAGNET];
	b2Body* cursor;
	b2ContactListener * lis;
	b2Connection* b2c;
public:
	b2RandomQueue* b2r;
private:

	ImageId img_ball;
	ImageId img_cursor;
	ImageId img_square;
	ImageId img_trace;
	ImageId img_light;
	ImageId img_triangle;
	ImageId img_gameover;

	bool br;
	bool bg;
	bool bb;

public:
	/*Const-Dest*/
	b2Factory();
	virtual ~b2Factory();

	/*about initialize*/
public:
	virtual int Init(GraphicApi*,InputApi*);
	virtual void Reset();
private:
	virtual void LoadResource();
	virtual void CreateField();
	virtual void CreateFxField();
	virtual void CreateCursor();

	/*about process*/
public:
	virtual void UpdateFrame();
	virtual void Draw();

public:
	virtual void ProcessWaitStable();
	virtual void ProcessWaitShot();
	virtual void ProcessWaitGameover();

	virtual void ProcessInput();
	virtual bool CheckIsEnd();
	virtual bool CheckIsStable();
	virtual int GetCurrentScore(){return currentScore;};
	virtual int GetShowScore(){return showScore;};
	virtual int GetMagnetNum(){return magnetNum;};
	virtual int GetRestCount(){return restCount;};
	virtual int GetFrameCount(){return frameCount;};
	virtual bool GetInputReady(){return inputReady;};

private:
	virtual void ProcessWorld();
	virtual void ProcessFxWorld();

	virtual void ProcessTime();

	virtual void ProcessCursor();

//	virtual void CreateBall(b2Vec2 p,b2Vec2 v,int number);
//	virtual void CreateSquare(b2Vec2 p,b2Vec2 v,int number);
	virtual void CreateBody();
	virtual void CreateRandomBody();
	virtual void UpdateStableFlag();
	virtual void UpdateDeadBodyList();
	virtual void RemoveDeadBody();

	virtual void CreateParticle(int,b2Vec2,Color4f);
	virtual void UpdateDeadParticleList();
	virtual void RemoveDeadParticle();

	virtual void CreateScoreParticle(b2Vec2,Color4f);
	virtual void RemoveScoreParticle();

	/*about close*/
public:
	virtual int Close();
private:
	virtual void DestroyAll();
};