#include "speechManagerment.h"

SpeechManager::SpeechManager()
{
	//初始化选手
	this->initSpeaker();

	//创建选手
	this->createSpeaker();

	//查看记录
	this->loadRecord();
}

//菜单显示函数
void SpeechManager::showMenu()
{
	cout << "******************************" << endl;
	cout << "****** 欢迎参加演讲比赛 ******" << endl;
	cout << "****** 1. 开始演讲比赛  ******" << endl;
	cout << "****** 2. 查看往届比赛  ******" << endl;
	cout << "****** 3. 清空比赛记录  ******" << endl;
	cout << "****** 0. 退出演讲比赛  ******" << endl;
	cout << "******************************" << endl;
	cout << endl;
}

//退出系统
void SpeechManager::exit_System()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化属性
void SpeechManager::initSpeaker()
{
	//保证容器为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	//初始化比赛轮数
	this->m_index = 1;
}

//创建选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//12名选手编号
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//开始比赛
void SpeechManager::startSpeech()
{
	//第1轮比赛
	//1.抽签
	speechDraw();
	//2.比赛
	speechContest();
	//3.显示晋级结果
	showScore();
	
    //第2轮比赛
	this->m_index++;
	//1.抽签
	speechDraw();
	//2.比赛
	speechContest();
	//3.显示最终结果
	showScore();
	//4.保存分数
	saveRecord();

	//防止比赛完后不能马上显示新纪录
    //初始化选手
	this->initSpeaker();

	//创建选手
	this->createSpeaker();

	//查看记录
	this->loadRecord();
	
	cout << "本届比赛比赛完毕" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_index << "轮比赛选手正在抽签" << endl;
	cout << "----------------------" << endl;
	cout << "抽签后的顺序如下：" << endl;
	if (this->m_index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "------------" << endl;
	system("pause");
	cout << endl;
}

//比赛
void SpeechManager::speechContest()
{
	cout << "------第" << this->m_index << "轮比赛正式开始：------" << endl;
	
	multimap<double, int, greater<int>> groupScore;

	int num = 0; //记录人数组，6个为一组

	vector<int> v_Src; //比赛队员容器
	if (this->m_index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 60 ~ 100
			//cout << "score = " << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_back(); //去掉最低分
		d.pop_front();//去掉最高分

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		//每个人平均分
		//cout << "编号：" << *it << "选手：" << this->m_Speaker[this->m_index - 1].m_Name << "获取平均分：" << ave << endl;
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;

		//6个人一组 用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_Name << " 成绩："
					<< this->m_Speaker[it->second].m_Score[this->m_index - 1] << endl;
			}
			int count = 0;
			//取前三名
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end()&& count < 3; it++, count++)
			{
				if (this->m_index == 1)
				{
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
	cout << "------第" << this->m_index << "轮比赛完毕------" << endl;
	system("pause");
}

//显示分数
void SpeechManager::showScore()
{
	cout << "------第" << this->m_index << "轮比赛晋级名单为：------" << endl;
	vector<int> v;
	if (this->m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << " 得分："
			<< this->m_Speaker[*it].m_Score[m_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.txt", ios::out | ios::app);

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();

	cout << "记录已保存" << endl;
	this->FileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.txt", ios::in);

	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->FileIsEmpty = false;

	ifs.putback(ch);//读取的单个字符放回去

	string data;
	int index = 0; //届数

	while (ifs >> data)
	{
		//cout << data << endl;
		//10001, 83.4125, 10009, 83.1375, 10005, 81.175,
		vector<string> v;
		
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

//显示记录
void SpeechManager::showRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在，或者为空！" << endl;
	}

	for (int i = 0; i < m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届比赛"
			<< " 冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
			<< " 亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
			<< " 季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
	}

	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确定清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.txt", ios::trunc);
		ofs.close();

		this->initSpeaker();

		this->createSpeaker();

		this->loadRecord();
	}

	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager(){}