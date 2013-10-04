
#include "Game.h"
#include "Common.h"

#ifdef _DEBUG
#pragma comment(lib,"Box2D.lib")
#else
#pragma comment(lib,"Box2D.lib")
#endif

Game* Game::myInstance=NULL;

Package* Game::CreateInstance(){
	if(myInstance==NULL){
		myInstance=new Game;
	}
	return myInstance;
}
void Game::DestroyInstance(){
	if(myInstance!=NULL){
		SAFE_DELETE(myInstance);
	}
}

int Game::Init(GraphicApi* _gapi,AudioApi* _aapi,InputApi* _iapi){
	ShowCursor(true);
	srand((unsigned)time(NULL));

	gapi=_gapi;
	iapi=_iapi;
	aapi=_aapi;

	this->LoadResource();

	b2f=new b2Factory;
	b2f->Init(gapi,iapi);

	ranking = new Ranking;
	ranking->Init("score.txt");

	Reset();

	return 0;
}

void Game::LoadResource(){
	img_white=gapi->CreateImageFromFile("image\\white2.png",Color4f(0,0,0,0));
	img_backr=gapi->CreateImageFromFile("image\\back6.png",Color4f(0,0,0,0));
	img_gameoverLine=gapi->CreateImageFromFile("image\\back7.png",Color4f(255,255,255,255));
	img_gameover=gapi->CreateImageFromFile("image\\gameover.png",Color4f(255,255,255,255));
	img_title=gapi->CreateImageFromFile("image\\title4.png",Color4f(0,0,0,0));
	img_backstr=gapi->CreateImageFromFile("image\\backstr2.png",Color4f(255,255,255,255));
	char buf[1024];
	for(int i=0;i<10;i++){
		sprintf_s(buf,"image\\%d.png",i);
		img_num[i]=gapi->CreateImageFromFile(buf);
	}
}

int Game::Reset(){
	b2f->Reset();
	ranking->Reset();
	state=TITLE;
	playState=WAIT_SHOT;
	return 0;
}

int Game::Close(){
	this->ReleaseResource();
	b2f->Close();
	SAFE_DELETE(b2f);
	ranking->Close();
	SAFE_DELETE(ranking);
	return 0;
}

void Game::ReleaseResource(){
	gapi->ReleaseImage(img_backr);
	gapi->ReleaseImage(img_white);
	gapi->ReleaseImage(img_title);
	gapi->ReleaseImage(img_backstr);
	gapi->ReleaseImage(img_gameover);
	gapi->ReleaseImage(img_gameoverLine);
	for(int i=0;i<10;i++){
		gapi->ReleaseImage(img_num[i]);
	}
}

int Game::End(){
	return 0;
}
int Game::Run(){

	iapi->mouse->Update();
	switch(state){
	case TITLE:
		this->ProcessTitle();
		break;
	case PLAY:
		this->ProcessPlay();
		break;
	}
	return 0;
}

void Game::ProcessTitle(){
//	iapi->Update();
	if(iapi->mouse->GetPushNow(0)){
		b2f->Reset();
		state=PLAY;
	}
}

int Game::GraphicCallback(){

	switch(state){
	case TITLE:
		gapi->DrawImageLU(0,0,img_title);
		this->DrawNumber(ranking->getLastScore(),400,240);
		this->DrawNumber(ranking->getHighScore(),400,315);
		break;
	case PLAY:
		gapi->DrawImageLU(0,0,img_white);
		b2f->Draw();
		gapi->DrawImageLU(0,0,img_gameoverLine);
		gapi->DrawImageLU(600,0,img_backr);
		gapi->DrawImageLU(600,0,img_backstr);
		this->DrawNumber(b2f->GetShowScore(),770,50);
		this->DrawNumber(b2f->GetMagnetNum(),770,130);
		this->DrawNumber(b2f->GetFrameCount()/60,770,200);
		b2f->b2r->Draw(b2f->GetInputReady());
		if(playState==GAMEOVER){
			gapi->DrawImageLU(200,300,img_gameover);
		}
		break;
	}
	return 0;
}

void Game::DrawNumber(int score,int x,int y){
	if(score==0){
		gapi->DrawImageLU(x,y,img_num[0]);
	}else{
		for(int i=0;score>0;i++){
			gapi->DrawImageLU(x-i*32,y,img_num[score%10]);
			score/=10;
		}
	}
}

int Game::AudioCallback(float* in,float* out,int frames){
	int i;
	float left,right;
	for(i=0;i<frames;i++){
		left=right=0.0f;
		aapi->GetWaveDataAll(&left,&right);
		*out++ = left;
		*out++ = right;
	}
	return 0;
}
