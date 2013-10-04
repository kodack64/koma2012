
#include "Game.h"

void Game::ProcessPlay(){
//	b2f->UpdateFrame();
	switch(playState){
	case WAIT_SHOT:
		b2f->ProcessWaitShot();
		if(iapi->mouse->GetPushNow(0)){
			b2f->ProcessInput();
//			playState=WAIT_STABLE;
		}
		iapi->key->Update();
		if(b2f->CheckIsEnd() || iapi->key->GetPush(VK_RETURN)){
			playState=GAMEOVER;
		}
		break;
	case WAIT_STABLE:
		b2f->ProcessWaitStable();
		if(iapi->mouse->GetPushNow(0)){
			b2f->ProcessInput();
			playState=WAIT_STABLE;
		}
		if(b2f->CheckIsStable()){
			if(b2f->CheckIsEnd()){
				Sleep(1000);
				playState=GAMEOVER;
			}else{
				playState=WAIT_SHOT;
			}
		}

		break;
	case GAMEOVER:
		b2f->ProcessWaitGameover();
		if(iapi->mouse->GetPushNow(0)){
			ranking->Update(b2f->GetCurrentScore());
			playState=WAIT_SHOT;
			state=TITLE;
		}
		break;
	}
}