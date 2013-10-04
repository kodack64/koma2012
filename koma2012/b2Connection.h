

#pragma once

#include "GameCommon.h"

class b2Connection{
private:
	b2Body** node;
	int** con;
	int* checked;
	int* belongGraph;
	vector<vector <int> > graph;
public:
	b2Connection();
	virtual ~b2Connection();
	virtual void Init();
	virtual void Reset();
	virtual void Close();
	virtual void MakeNode(b2Body* body);
	virtual void DestroyNode(b2Body* body); 
	virtual void MakeRelation(b2Body* body1,b2Body* body2);
	virtual void DestroyRelation(b2Body* body1,b2Body* body2);
	virtual bool IsConnected(b2Body* body1,b2Body* body2);
	virtual void UpdateGraph();
	virtual void RecursiveSearch(int id,int graphId);
	virtual int GetGraphElements(b2Body* body);
};