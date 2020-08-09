#include "speechManager.h"

speechManager::speechManager() {
	this->initSpeech();
	this->createSpeaker();

}

speechManager::~speechManager() {


}

void speechManager::showMenu() {
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void speechManager::exitSystem() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void speechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->mSpeaker.clear();
	this->mIndex = 1;
}

void speechManager::createSpeaker() {
	string nameSed = "ABCDEFGHIJKL";
	for (int i = 0; i != nameSed.size(); ++i) {
		string name = "选手";
		name += nameSed[i];   // 编号！学到了

		speaker sp;
		sp.mName = name;
		for (int j = 0; j != 2; ++j) {
			sp.mScore[j] = 0;
		}

		this->v1.push_back(i + 10001);

		this->mSpeaker.insert(make_pair(i + 10001, sp));

	}
}

void speechManager::speechDraw() {
	cout << "第 <<" << this->mIndex << ">> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->mIndex == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;

	system("pause");
	cout << endl;
}

void speechManager::speechContest() {
	cout << "------------- 第" << this->mIndex << "轮正式比赛开始：------------- " << endl;

	multimap<double, int, greater<int>> groupScore; // greater用来排序？
	
	int num = 0;
	vector<int> vSrc;
	if (this->mIndex == 1) {
		vSrc = v1;
	}
	else {
		vSrc = v2;
	}

	for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); ++it) {
		num++;

		deque<double> d;
		for (int i = 0; i != 10; ++i) {
			double score = (rand() % 401 + 600) / 10.f; // 生成一个600 + rand的数！不包括1001
			// .f表示按照浮点数处理
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f); // 最后一个是起始值？
		double avg = sum / (double)d.size();

		this->mSpeaker[*it].mScore[this->mIndex - 1] = avg;

		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0) {

			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); ++it) {
				cout << "编号：" << it->second << "姓名：" << this->mSpeaker[it->second].mName << "成绩" << this->mSpeaker[it->second].mScore[this->mIndex - 1] << endl;

			}

			int count = 0;

			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count != 3; ++it, ++count) {
				if (this->mIndex == 1) {
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();
			cout << endl;
		}
		
	}
	cout << "------------- 第" << this->mIndex << "轮比赛完毕  ------------- " << endl;
	system("pause");


}

void speechManager::showScore() {
	cout << "---------第" << this->mIndex << "轮晋级选手信息如下：-----------" << endl;
	vector<int> v;
	if (this->mIndex == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		cout << "选手编号：" << *it << " 姓名： " << mSpeaker[*it].mName << " 得分： " << mSpeaker[*it].mScore[this->mIndex - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void speechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); ++it) {
		ofs << *it << ", " << mSpeaker[*it].mScore[1] << ", ";
	}
	ofs << endl;

	ofs.close();

	cout << "记录已保存" << endl;
}

void speechManager::startSpeech() {
	// 第一轮
	
	// 抽签
	speechDraw();
	// 比赛
	speechContest();
	// 显示晋级结果
	showScore();
	// 第二轮比赛
	this->mIndex++;
	// 抽签
	speechDraw();
	// 比赛
	speechContest();
	// 显示最终分数
	showScore();
	// 保存分数
	saveRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}