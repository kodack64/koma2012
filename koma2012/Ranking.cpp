
#include "Ranking.h"
#include "Logger.h"

Ranking::Ranking(){
	latestScore=0;
	highScore=0;
}

Ranking::~Ranking(){
}

bool Ranking::Init(string _fileName){	
	fileName=_fileName;
	Reset();
	return true;
}
bool Ranking::Reset(){	
	ranking.clear();
	fstream fs;
	fs.open(fileName,ios::in);
	if(fs){
		int temp;
		fs >> temp;
		ranking.push_back(temp);
	}else{
		ranking.push_back(0);
	}
	sort(ranking.rbegin(),ranking.rend());
	highScore=ranking[0];
	return true;
}
int Ranking::Update(int newScore){
	int myrank;
	for(unsigned int i=0;i<ranking.size();i++){
		if(ranking[i]<newScore){
			myrank=i+1;
		}
		if(i+1==ranking.size())myrank=i+1;
	}
	ranking.push_back(newScore);
	sort(ranking.rbegin(),ranking.rend());
	latestScore=newScore;
	highScore=ranking[0];


	fstream fs;
	fs.open(fileName,ios::out|ios::trunc);
	if(fs){
		for(unsigned int i=0;i<ranking.size();i++){
			fs << ranking[i] << endl;
		}
	}else{
		Logger::Println("Score File Cannot Open");
	}
	return myrank;
}
bool Ranking::Close(){
	return true;
}
