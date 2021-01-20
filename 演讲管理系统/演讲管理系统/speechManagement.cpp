#include "speechManagerment.h"

SpeechManager::SpeechManager()
{
	//��ʼ��ѡ��
	this->initSpeaker();

	//����ѡ��
	this->createSpeaker();

	//�鿴��¼
	this->loadRecord();
}

//�˵���ʾ����
void SpeechManager::showMenu()
{
	cout << "******************************" << endl;
	cout << "****** ��ӭ�μ��ݽ����� ******" << endl;
	cout << "****** 1. ��ʼ�ݽ�����  ******" << endl;
	cout << "****** 2. �鿴�������  ******" << endl;
	cout << "****** 3. ��ձ�����¼  ******" << endl;
	cout << "****** 0. �˳��ݽ�����  ******" << endl;
	cout << "******************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void SpeechManager::exit_System()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ʼ������
void SpeechManager::initSpeaker()
{
	//��֤����Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	//��ʼ����������
	this->m_index = 1;
}

//����ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//12��ѡ�ֱ��
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ʼ����
void SpeechManager::startSpeech()
{
	//��1�ֱ���
	//1.��ǩ
	speechDraw();
	//2.����
	speechContest();
	//3.��ʾ�������
	showScore();
	
    //��2�ֱ���
	this->m_index++;
	//1.��ǩ
	speechDraw();
	//2.����
	speechContest();
	//3.��ʾ���ս��
	showScore();
	//4.�������
	saveRecord();

	//��ֹ���������������ʾ�¼�¼
    //��ʼ��ѡ��
	this->initSpeaker();

	//����ѡ��
	this->createSpeaker();

	//�鿴��¼
	this->loadRecord();
	
	cout << "��������������" << endl;
	system("pause");
	system("cls");
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->m_index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------" << endl;
	cout << "��ǩ���˳�����£�" << endl;
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

//����
void SpeechManager::speechContest()
{
	cout << "------��" << this->m_index << "�ֱ�����ʽ��ʼ��------" << endl;
	
	multimap<double, int, greater<int>> groupScore;

	int num = 0; //��¼�����飬6��Ϊһ��

	vector<int> v_Src; //������Ա����
	if (this->m_index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 60 ~ 100
			//cout << "score = " << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_back(); //ȥ����ͷ�
		d.pop_front();//ȥ����߷�

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		//ÿ����ƽ����
		//cout << "��ţ�" << *it << "ѡ�֣�" << this->m_Speaker[this->m_index - 1].m_Name << "��ȡƽ���֣�" << ave << endl;
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;

		//6����һ�� ����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ���"
					<< this->m_Speaker[it->second].m_Score[this->m_index - 1] << endl;
			}
			int count = 0;
			//ȡǰ����
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
	cout << "------��" << this->m_index << "�ֱ������------" << endl;
	system("pause");
}

//��ʾ����
void SpeechManager::showScore()
{
	cout << "------��" << this->m_index << "�ֱ�����������Ϊ��------" << endl;
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
		cout << "��ţ�" << *it << " ������" << this->m_Speaker[*it].m_Name << " �÷֣�"
			<< this->m_Speaker[*it].m_Score[m_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

//�����¼
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

	cout << "��¼�ѱ���" << endl;
	this->FileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.txt", ios::in);

	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->FileIsEmpty = false;

	ifs.putback(ch);//��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0; //����

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

//��ʾ��¼
void SpeechManager::showRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڣ�����Ϊ�գ�" << endl;
	}

	for (int i = 0; i < m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "�����"
			<< " �ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
			<< " �Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
			<< " ������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
	}

	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

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