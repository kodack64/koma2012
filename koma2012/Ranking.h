
#pragma once

#include "Common.h"

class Ranking{
private:
	string fileName;
	vector <int> ranking;
	int latestScore;
	int highScore;
public:
	Ranking();
	virtual ~Ranking();
	virtual bool Init(string _fileName);
	virtual bool Reset();
	virtual int Update(int newScore);
	virtual bool Close();
	virtual int getLastScore(){return latestScore;};
	virtual int getHighScore(){return highScore;};
};