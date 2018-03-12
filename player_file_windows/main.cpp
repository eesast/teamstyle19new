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
		if (state->winner != 2)
			break;
		f_player();
		cilent.send_command(_updateAge,c1,c2);
		_updateAge = false;
		c1.clear();
		c2.clear();
	}
	if (state->winner == 1)
		cout << "Winner is 1" << endl;
	else if (state->winner == 0)
		cout << "Winner is 0" << endl;
	else if (state->winner == 2)
		cout << "Draw" << endl;
	goon = false;
	Sleep(1000);
	delete state;
	th_communication.join();
}