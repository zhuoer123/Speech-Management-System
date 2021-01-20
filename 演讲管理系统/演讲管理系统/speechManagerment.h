#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<map>
#include<numeric>
#include "speaker.h"
#include<algorithm>
#include<fstream>

using namespace std;

class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//�˵���ʾ����
	void showMenu();

	//����ѡ�� ���� 12��
	vector<int> v1;

	//��һ�ֽ��� 6��
	vector<int> v2;

	//ʤ��ǰ3������ 
	vector<int> vVictory;

	//��ű�� ���ڵľ���ѡ������
	map<int, Speaker> m_Speaker;

	//��¼��������
	int m_index = 0;

	//��ʼ������
	void initSpeaker();

	//����12��ѡ��
	void createSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ����
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//�ļ�Ϊ�յı�־
	bool FileIsEmpty;

	//�����¼
	map<int, vector<string>> m_Record;

	//��ʾ��¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//�˳��˵�
	void exit_System();

	//��������
	~SpeechManager();
};