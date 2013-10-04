

#include "b2Factory.h"

void b2Factory::Draw(){

	// process lighting
/*	if(br)((b2Object*)(cursor->GetUserData()))->myColor.red+=2;
	else((b2Object*)(cursor->GetUserData()))->myColor.red-=2;
	if(((b2Object*)(cursor->GetUserData()))->myColor.red>255){
		br=!br;
		((b2Object*)(cursor->GetUserData()))->myColor.red=255;
	}
	if(((b2Object*)(cursor->GetUserData()))->myColor.red<0){
		br=!br;
		((b2Object*)(cursor->GetUserData()))->myColor.red=0;
	}
	if(bg)((b2Object*)(cursor->GetUserData()))->myColor.green+=3;
	else((b2Object*)(cursor->GetUserData()))->myColor.green-=3;
	if(((b2Object*)(cursor->GetUserData()))->myColor.green>255){
		bg=!bg;
		((b2Object*)(cursor->GetUserData()))->myColor.green=255;
	}	
	if(((b2Object*)(cursor->GetUserData()))->myColor.green<0){
		bg=!bg;
		((b2Object*)(cursor->GetUserData()))->myColor.green=0;
	}
	if(bb)((b2Object*)(cursor->GetUserData()))->myColor.blue+=5;
	else((b2Object*)(cursor->GetUserData()))->myColor.blue-=5;
	if(((b2Object*)(cursor->GetUserData()))->myColor.blue>255){
		bb=!bb;
		((b2Object*)(cursor->GetUserData()))->myColor.blue=255;
	}
	if(((b2Object*)(cursor->GetUserData()))->myColor.blue<0){
		bb=!bb;
		((b2Object*)(cursor->GetUserData()))->myColor.blue=0;
	}*/


	//add trace
	//draw all game worlds body
	b2Vec2 v;
	Color4f c;
	b2Body* body;
	b2Object* obj;
	float zc;
	Color4f cc;

	body=world->GetBodyList();
	while(body!=NULL){
		if(body->GetUserData()!=NULL && body!=cursor){

			obj=(b2Object*)(body->GetUserData());
			c = obj->myColor;

			obj->trace.push_back(body->GetPosition());
			if(obj->trace.size()>=MAX_TRACE){
				obj->trace.erase(obj->trace.begin());
			}
			obj->rot=body->GetAngle();

			zc=obj->zoom;
			cc=obj->myColor;
			if(obj->light)gapi->DrawImage(M2P(obj->trace[0].x),M2P(obj->trace[0].y),0,0,0,0,zc*3,obj->rot,cc,img_light);
			gapi->DrawImage(M2P(obj->trace[0].x),M2P(obj->trace[0].y),0,0,0,0,zc,obj->rot,cc,obj->myImage);
		}
		body=body->GetNext();
	}

	//draw fx world all body
	body=fxworld->GetBodyList();
	while(body!=NULL){
		if(body->GetUserData()!=NULL){
			b2Object* obj=(b2Object*)(body->GetUserData());
			c = obj->myColor;

			obj->trace.push_back(body->GetPosition());
			if(obj->trace.size()>=MAX_TRACE){
				obj->trace.erase(obj->trace.begin());
			}
			obj->rot=body->GetAngle();

			double zc=obj->zoom;
			Color4f cc=obj->myColor;
			for(int i=obj->trace.size()-1;i>=0;i--){
				gapi->DrawImage(M2P(obj->trace[i].x),M2P(obj->trace[i].y),0,0,0,0,zc,obj->rot,cc,obj->myImage);
				zc=(int)(zc*0.8);
				cc.alpha=(int)(cc.alpha*0.5);
			}
		}
		body=body->GetNext();
	}
}
