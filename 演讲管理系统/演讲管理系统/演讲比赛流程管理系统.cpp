#include<iostream>
#include<ctime>
#include "speechManagerment.h"

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;

	//���Դ���
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first
	//		<< " ������ " << it->second.m_Name
	//		<< " �ɼ��� " << it->second.m_Score[0] << endl;
	//}

	int choice = 0;
	while (true)
	{
		sm.showMenu();

		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch(choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0: //�˳�ϵͳ
			sm.exit_System();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}