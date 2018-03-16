#include"communication.h"
#include<pthread.h>
#include<vector>
#include<iostream>
#include<fstream>
//#include<ctime>
using namespace std;

extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2> c2;
void f_player();

State* state=NULL;
MyClient cilent;
int** map;
bool flag;
bool goon = true;
pthread_mutex_t mt;

void* Listen(void* arg)
{
	pthread_mutex_lock(&mt);
	State* t;
	while (goon)
	{
		State* s = cilent.recv_state();
		t=state;
		state = s;
		delete t;
		pthread_mutex_unlock(&mt);
	}
	return NULL;
}

int main()
{
	pthread_mutex_init(&mt,NULL);
	cilent.start_connection();
	map = cilent.map;
	flag = cilent.flag;
    pthread_t com_thread;
    pthread_create(&com_thread,NULL,Listen,(void*)NULL);
	/*while (state == NULL)
	{

	}
	State* laststate = NULL;*/
	cout<<"++++++++"<<endl;
	pthread_mutex_lock(&mt);
	cout<<"ASDASDASD"<<endl;
	int c;
	while (state->turn < 1000)
	{
		/*if (state == NULL)
			continue;
		if (state == laststate)
			continue;
		laststate = state;*/
		if (state->winner != 2)
			break;
		f_player();
		cilent.send_command(_updateAge,c1,c2);
		_updateAge = false;
		c1.clear();
		c2.clear();
		pthread_mutex_lock(&mt);
	}
	if (state->winner == 1)
		cout << "Winner is 1" << endl;
	else if (state->winner == 0)
		cout << "Winner is 0" << endl;
	else if (state->winner == 2)
		cout << "draw" << endl;
	goon = false;

	pthread_join(com_thread,NULL);
}
