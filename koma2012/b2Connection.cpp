
#include "b2Connection.h"
#include "b2Object.h"

b2Connection::b2Connection(){
}
b2Connection::~b2Connection(){
}
void b2Connection::Init(){
	node = new b2Body*[MAX_MAGNET];
	con= new int*[MAX_MAGNET];
	for(int i=0;i<MAX_MAGNET;i++){
		con[i] = new int[MAX_MAGNET];
	}
	checked = new int[MAX_MAGNET];
	belongGraph= new int[MAX_MAGNET];
	Reset();
}
void b2Connection::Reset(){
	for(int i=0;i<MAX_MAGNET;i++){
		node[i]=NULL;
		for(int j=0;j<MAX_MAGNET;j++){
			con[i][j]=0;
		}
	}
}
void b2Connection::Close(){
	for(int i=0;i<MAX_MAGNET;i++){
		delete[] con[i];
	}
	delete[] con;
	delete[] node;
	delete[] checked;
	delete[] belongGraph;
}
void b2Connection::MakeNode(b2Body* body){
	for(int i=0;i<MAX_MAGNET;i++){
		if(node[i]==NULL){
			node[i]=body;
			((b2Object*)body->GetUserData())->nodeId=i;
			break;
		}
		if(i==MAX_MAGNET-1){
			printf("error: node is already max\n");
		}
	}
//	printf("make node\n");
}
void b2Connection::DestroyNode(b2Body* body){
	int id=((b2Object*)body->GetUserData())->nodeId;
	for(int i=0;i<MAX_MAGNET;i++){
		con[id][i]=con[i][id]=0;
	}
	if(node[id]==NULL){
		printf("error: empty node is destroyed\n");
	}
	node[id]=NULL;
//	printf("destroy node\n");
}
void b2Connection::MakeRelation(b2Body* body1,b2Body* body2){
	int id1=((b2Object*)body1->GetUserData())->nodeId;
	int id2=((b2Object*)body2->GetUserData())->nodeId;
	if(node[id1]==NULL || node[id2]==NULL){
		printf("error: try to make relation with empty node\n");
	}
	if(con[id1][id2]==1){
		printf("error: relation is allready made\n");
	}
	con[id1][id2]=con[id2][id1]=1;
//	printf("make relation\n");
}
void b2Connection::DestroyRelation(b2Body* body1,b2Body* body2){
	int id1=((b2Object*)body1->GetUserData())->nodeId;
	int id2=((b2Object*)body2->GetUserData())->nodeId;
	if(node[id1]==NULL || node[id2]==NULL){
		printf("error: try to make relation with empty node\n");
	}
	if(con[id1][id2]==0){
		printf("error: relation is allready destroyed\n");
	}
	con[id1][id2]=con[id2][id1]=0;
//	printf("destroy relation\n");
}
bool b2Connection::IsConnected(b2Body* body1,b2Body* body2){
	int id1=((b2Object*)body1->GetUserData())->nodeId;
	int id2=((b2Object*)body2->GetUserData())->nodeId;
	return (con[id1][id2]==1);
}
void b2Connection::UpdateGraph(){

	for(int i=0;i<MAX_MAGNET;i++){
		checked[i]=0;
		belongGraph[i]=-1;
	}

	int graphId=0;
	graph.clear();
	for(int i=0;i<MAX_MAGNET;i++){
		if(node[i]!=NULL && checked[i]==0){
			checked[i]=1;
			graph.push_back(vector<int>());
			graph[graphId].push_back(i);
			belongGraph[i]=graphId;
			RecursiveSearch(i,graphId);
			graphId++;
		}
	}
}

void b2Connection::RecursiveSearch(int i,int graphId){
	b2Object *obj1,*obj2;
	for(int j=0;j<MAX_MAGNET;j++){
		if(node[j]!=NULL && checked[j]==0){
			if(con[i][j]==1){
				obj1=((b2Object*)node[i]->GetUserData());
				obj2=((b2Object*)node[j]->GetUserData());
				if(obj1->number==obj2->number){
					checked[j]=1;
					graph[graphId].push_back(j);
					belongGraph[j]=graphId;
					RecursiveSearch(j,graphId);
				}
			}
		}
	}
}

int b2Connection::GetGraphElements(b2Body* body){
	int nodeId=((b2Object*)body->GetUserData())->nodeId;
	if(belongGraph[nodeId]==-1)return -1;
	else return graph[belongGraph[nodeId]].size();
}
