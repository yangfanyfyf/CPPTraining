#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <numeric>
#include <string >
#include <algorithm>
#include <fstream>
#include "speaker.h"

using namespace std;

class speechManager {
public:
	speechManager();

	~speechManager();

	void  showMenu();

	void exitSystem();

	void initSpeech();

	void createSpeaker();

	void startSpeech();

	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	vector<int> v1;
	vector<int> v2;
	vector<int> vVictory;
	map<int, speaker> mSpeaker;
	int mIndex;
};