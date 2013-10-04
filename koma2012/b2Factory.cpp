
#include "b2Factory.h"
#include "Logger.h"
#include "b2Object.h"
#include "b2MyContact.h"
#include "GameParam.h"

#define PUT_INTERVAL (60)
#define FIRST_PUT_SPEED (60*5)
#define PUT_SPEED_UP_DIV (60*10)
#define PUT_SPEED_MAX (60/2)
#define PUT_SPEED_UP_P (0.95)
#define MORE_KIND_SPEED (60*40)
#define FIRST_KIND (4)

b2Factory::b2Factory()
:gapi(NULL)
,iapi(NULL)
,world(NULL)
,fxworld(NULL)
{
}

b2Factory::~b2Factory(){
}

void ennear(int* src,int to,int spd){
	int from=(*src);
	if(from+spd<to){
		(*src)+=spd;
	}else if(from<to){
		(*src)+=to-from;
	}if(from-spd>to){
		(*src)-=spd;
	}else{
		(*src)-=from-to;
	}
}

int b2Factory::Init(GraphicApi* _gapi,InputApi* _iapi){
	gapi=_gapi;
	iapi=_iapi;
	magnetNum=0;

	this->LoadResource();

	/*Init Instance*/
	world=new b2World(b2Vec2(0.0f,10.0f));
	b2c = new b2Connection();
	b2c->Init();
	b2r = new b2RandomQueue(gapi,img_ball,img_square,img_triangle);
	lis =new MyContactListener(b2c);
	world->SetContactListener(lis);
	world->SetAllowSleeping(false);
	fxworld=new b2World(b2Vec2(0.0f,-10.0f));

	Reset();

	return 0;
}

void b2Factory::LoadResource(){
	/*Load Graphic*/
	img_ball=gapi->CreateImageFromFile("Image\\circle.png",Color4f(0,0,0,255));
	img_square=gapi->CreateImageFromFile("Image\\square.png",Color4f(0,0,0,255));
//	img_triangle=gapi->CreateImageFromFile("Image\\triangle.png",Color4f(0,0,0,255));
	img_cursor=gapi->CreateImageFromFile("Image\\cursor4.png");
	img_trace=gapi->CreateImageFromFile("Image\\cursor4.png");
	img_light=gapi->CreateImageFromFile("Image\\particle0.png");
}

void b2Factory::Reset(){
	/*Reset Field and Insntance*/
	DestroyAll();
	deadBodyList.clear();
	deadParticleList.clear();
	deadScoreList.clear();
	bodyStock.clear();

	currentScore=0;
	showScore=0;
	frameCount=0;
	frameDiv=FIRST_PUT_SPEED;

	inputReady=true;
	inputCount=0;

	restCount=FIRSTCOUNT;
	magnetNum=0;
	maxMagnetNum=FIRSTBALL;
	br=bg=bb=false;

	balltimediv=10;
	prevballtime=0;

	this->CreateField();
	this->CreateFxField();
	this->CreateCursor();
	b2r->Close();
	b2r->Init(15,2,FIRST_KIND,cursor);
}

void b2Factory::ProcessWaitShot(){
	this->UpdateFrame();
	this->ProcessCursor();

	this->RemoveDeadBody();
	this->RemoveDeadParticle();
	this->RemoveScoreParticle();

	this->ProcessWorld();
	this->ProcessFxWorld();
	this->ProcessTime();

	this->UpdateDeadBodyList();
	this->UpdateDeadParticleList();
}

void b2Factory::ProcessWaitStable(){
	this->UpdateFrame();
	this->ProcessCursor();

	this->RemoveDeadBody();
	this->RemoveDeadParticle();
	this->RemoveScoreParticle();

	this->ProcessWorld();
	this->ProcessFxWorld();
	this->ProcessTime();

	this->UpdateStableFlag();
	this->UpdateDeadBodyList();
	this->UpdateDeadParticleList();
}
void b2Factory::ProcessWaitGameover(){
	this->ProcessCursor();
}

int b2Factory::Close(){
	this->DestroyAll();
	gapi->ReleaseImage(img_ball);
	gapi->ReleaseImage(img_square);
//	gapi->ReleaseImage(img_triangle);
	gapi->ReleaseImage(img_cursor);
	gapi->ReleaseImage(img_trace);
	gapi->ReleaseImage(img_light);
	b2c->Close();
	b2r->Close();
	SAFE_DELETE(b2c);
	SAFE_DELETE(b2r);
	SAFE_DELETE(lis);
	SAFE_DELETE(world);
	SAFE_DELETE(fxworld);
	return 0;
}

void b2Factory::UpdateFrame(){
	frameCount++;
	if(frameCount%1==0 && currentScore>showScore){
		showScore++;
	}
}

void b2Factory::ProcessWorld(){
	// step world
	world->Step(1.0f/60.0f,6,2);
}

void b2Factory::ProcessFxWorld(){
	// step fxworld
	fxworld->Step(1.0f/60.0f,6,2);
}

void b2Factory::ProcessTime(){
	if(!inputReady){
		inputCount++;
		if(inputCount>=PUT_INTERVAL){
			inputCount=0;
			inputReady=true;
		}
	}

	//fast
	if(frameCount!=0 && frameCount%(PUT_SPEED_UP_DIV)==0)frameDiv*=PUT_SPEED_UP_P;
	if(frameDiv<PUT_SPEED_MAX)frameDiv=PUT_SPEED_MAX;

	//many
	if(frameCount!=0 && frameCount%(MORE_KIND_SPEED)==0){
		b2r->MoreNumber();
	}

	if(frameCount%frameDiv==0){
		CreateRandomBody();
	}
}

bool b2Factory::CheckIsEnd(){
	// check is end
	bool endCheck=false;
	b2Body* body=world->GetBodyList();
	while(body!=NULL){
		b2Object* obj=(b2Object*)body->GetUserData();
		if(obj!=NULL){
			if(obj->isMagnet){
				if(M2P(body->GetPosition().y)<60){
					endCheck=true;
				}
			}
		}
		body=body->GetNext();
	}
	return endCheck;
}

bool b2Factory::CheckIsStable(){
	return isAllSleep;
}

void b2Factory::DestroyAll(){
	//destroy all
	b2Body* body=world->GetBodyList();
	for(;body!=NULL;){
		b2Body* sub=body->GetNext();
		if(body->GetUserData()!=NULL){
			b2Object* obj=(b2Object*)(body->GetUserData());
			SAFE_DELETE(obj);
			body->SetUserData(NULL);
		}
		world->DestroyBody(body);
		body=sub;
	}
	body=fxworld->GetBodyList();
	for(;body!=NULL;){
		b2Body* sub=body->GetNext();
		if(body->GetUserData()!=NULL){
			b2Object* obj=(b2Object*)(body->GetUserData());
			SAFE_DELETE(obj);
			body->SetUserData(NULL);
		}
		fxworld->DestroyBody(body);
		body=sub;
	}
	b2c->Reset();
}
