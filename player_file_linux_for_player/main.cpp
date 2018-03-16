#include"communication.h"
#include<pthread.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<semaphore.h>
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
bool use=false;
pthread_mutex_t mt;
sem_t* sg=NULL;

void* Listen(void* arg)
{
	//pthread_mutex_lock(&mt);
	State* t;
	while (goon)
	{
		State* s = cilent.recv_state();
		t=state;
		state = s;
		delete t;
		//pthread_mutex_unlock(&mt);
		sem_post(sg);
	}
	return NULL;
}

int main()
{
	if(sg==NULL)
		cout<<"ASDASD"<<endl;
	//pthread_mutex_init(&mt,NULL);
	cilent.start_connection();
	map = cilent.map;
	flag = cilent.flag;
	if(flag==0)
		sg=sem_open("/temp0",O_CREAT,0644,0);
	else
		sg=sem_open("/temp1",O_CREAT,0644,0);
    pthread_t com_thread;
    pthread_create(&com_thread,NULL,Listen,(void*)NULL);
/*	while (state == NULL)
	{

	}*/
	//state=cilent.recv_state();
	sem_wait(sg);
	State* laststate = NULL;
	cout<<"++++++++"<<endl;
	//pthread_mutex_lock(&mt);
	cout<<"ASDASDASD"<<endl;
	int c;
	while (state->turn < 1000)
	{
		/*if (state == NULL)
			continue;
		if (state == laststate)
			continue;
		laststate = state;*/
		cout<<"*********"<<state->turn<<endl;
		if (state->winner != 2)
			break;
		f_player();
		if(!use)
			cilent.send_command(_updateAge,c1,c2);
		_updateAge = false;
		c1.clear();
		c2.clear();
		sem_wait(sg);
	//	pthread_mutex_lock(&mt);
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
