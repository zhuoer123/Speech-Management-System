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
	//构造函数
	SpeechManager();

	//菜单显示函数
	void showMenu();

	//比赛选手 容器 12人
	vector<int> v1;

	//第一轮晋级 6人
	vector<int> v2;

	//胜利前3名容器 
	vector<int> vVictory;

	//存放编号 对于的具体选手容器
	map<int, Speaker> m_Speaker;

	//记录比赛轮数
	int m_index = 0;

	//初始化属性
	void initSpeaker();

	//创建12名选手
	void createSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示分数
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//文件为空的标志
	bool FileIsEmpty;

	//往届记录
	map<int, vector<string>> m_Record;

	//显示记录
	void showRecord();

	//清空记录
	void clearRecord();

	//退出菜单
	void exit_System();

	//析构函数
	~SpeechManager();
};