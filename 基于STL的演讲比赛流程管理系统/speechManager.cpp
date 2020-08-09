#include "speechManager.h"

speechManager::speechManager() {
	this->initSpeech();
	this->createSpeaker();

}

speechManager::~speechManager() {


}

void speechManager::showMenu() {
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void speechManager::exitSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
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
		string name = "ѡ��";
		name += nameSed[i];   // ��ţ�ѧ����

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
	cout << "�� <<" << this->mIndex << ">> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

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
	cout << "------------- ��" << this->mIndex << "����ʽ������ʼ��------------- " << endl;

	multimap<double, int, greater<int>> groupScore; // greater��������
	
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
			double score = (rand() % 401 + 600) / 10.f; // ����һ��600 + rand������������1001
			// .f��ʾ���ո���������
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f); // ���һ������ʼֵ��
		double avg = sum / (double)d.size();

		this->mSpeaker[*it].mScore[this->mIndex - 1] = avg;

		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0) {

			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); ++it) {
				cout << "��ţ�" << it->second << "������" << this->mSpeaker[it->second].mName << "�ɼ�" << this->mSpeaker[it->second].mScore[this->mIndex - 1] << endl;

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
	cout << "------------- ��" << this->mIndex << "�ֱ������  ------------- " << endl;
	system("pause");


}

void speechManager::showScore() {
	cout << "---------��" << this->mIndex << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	vector<int> v;
	if (this->mIndex == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << mSpeaker[*it].mName << " �÷֣� " << mSpeaker[*it].mScore[this->mIndex - 1] << endl;
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

	cout << "��¼�ѱ���" << endl;
}

void speechManager::startSpeech() {
	// ��һ��
	
	// ��ǩ
	speechDraw();
	// ����
	speechContest();
	// ��ʾ�������
	showScore();
	// �ڶ��ֱ���
	this->mIndex++;
	// ��ǩ
	speechDraw();
	// ����
	speechContest();
	// ��ʾ���շ���
	showScore();
	// �������
	saveRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}