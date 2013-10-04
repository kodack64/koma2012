
#pragma once

#include "package.h"
#include "b2Factory.h"
#include "Ranking.h"
#include "GameState.h"
#include "GamePlayState.h"

class Game:public Package{
private:

	ImageId img_back;
	ImageId img_backr;
	ImageId img_backstr;
	ImageId img_title;
	ImageId img_white;
	ImageId img_num[10];
	ImageId img_gameover;
	ImageId img_gameoverLine;

	/*State*/
	GameState state;
	GamePlayState playState;

	/*Field*/
	int frameCount;

	/*Box2D*/
	b2Factory* b2f;

	/*Ranking*/
	Ranking* ranking;

private:
	static Game* myInstance;
public:
	virtual int Init(GraphicApi* _gapi,AudioApi* _aapi,InputApi* _iapi);
	virtual int Reset();
	virtual int Close();
	virtual int End();
	virtual int Run();
	virtual int AudioCallback(float* in,float* out,int frames);
	virtual int GraphicCallback();

	static Package* CALLBACK CreateInstance();
	static void CALLBACK DestroyInstance();

private:
	virtual void LoadResource();
	virtual void ReleaseResource();
	virtual void DrawNumber(int score,int x,int y);
	virtual void ProcessTitle();
	virtual void ProcessPlay();
};