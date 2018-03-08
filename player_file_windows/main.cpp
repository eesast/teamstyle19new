#include"communication.h"
#include<thread>
#include<vector>
#include<iostream>
//#include<ctime>
using namespace std;

extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2> c2;
void f_player();

State* state=NULL;
MyClient cilent;
bool** map;
bool flag;
bool goon = true;

void Listen()
{
	State* t;
	while (goon)
	{
		State* s = cilent.recv_state();
		t=state;
		state=s;
		delete t;
	}
}

int main()
{
	for (int i = 0; i < 50; i++)
		c1.push_back(command1(i, 3));
	for (int i = 0; i < 50; i++)
		c2.push_back(command2(6, i + 10, 4, 4, 5, 5)); //�����õ�
	cilent.start_connection();
	map = cilent.map;
	flag = cilent.flag;
	int turn = 0;
	thread th_communication(Listen);
	while (state == NULL)
	{

	}
	State* laststate = NULL;
	while (state->turn < 1000)
	{
		if (state == NULL)
			continue;
		if (state == laststate)
			continue;
		laststate = state;
	/*	if (state->turn == 30)
		{
			int ee;
			cin >> ee;
		}*/
	//	cout << "********************"<<state->winner <<"****************************"<< endl;
		if (state->winner != 2)//������ʤ����
			break;
		f_player();
		cilent.send_command(_updateAge,c1,c2);
		_updateAge = false;
		c1.clear();//ע ���f_player()�ǿյ� ���ȥ��clear ����ᷢ��ָ�� û����
		c2.clear();
		//Sleep(100);
	//	cout << "********************************************************" << endl;
	}
	if (state->winner == 1)
		cout << "Winner is 1" << endl;
	else if (state->winner == 0)
		cout << "Winner is 0" << endl;
	else if (state->winner == 2)
		cout << "draw" << endl;
	goon = false;
	Sleep(1000);
	delete sstate;
	goon = false;
	th_communication.join();
}