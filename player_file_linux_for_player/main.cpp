#include"communication.h"
#include<pthread.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<semaphore.h>
#include <chrono>  
#include <random>  
#include<sstream>

//#include<ctime>
using namespace std;

extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2> c2;
void f_player();

State* state=NULL;
vector<State* > all_state;
MyClient cilent;
int** map;
bool flag;
bool goon = true;
bool use=false;
sem_t *sg=new sem_t;

void* Listen(void* arg)
{
	cout<<"start listening"<<endl;
	State* t;
	while (goon)
	{
		State* s = cilent.recv_state();
		state=s;
		all_state.push_back(state);
		cout<<"I was listening"<<state->turn<<endl;
		/*t=state;
		state = s;
		delete t;*/
		sem_post(sg);
		if(state->winner!=2)
			break;
	}
	return NULL;
}

int main()
{
	cilent.start_connection();
	map = cilent.map;
	flag = cilent.flag;
	#ifdef __APPLE__
	{
		unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 g1(seed1);
		int r1=g1();
		int r2=r1+1;
		stringstream s;
		if(flag==0)
			{
				s<<"ts_00_";
				s<<r1;
				sg=sem_open(s.str().c_str(),O_CREAT,0644,0);
			}
		else
			{
				s<<"ts_01_";
				s<<r2;
				sg=sem_open(s.str().c_str(),O_CREAT,0644,0);
			}
	}
	#else
	{
		int v=sem_init(sg,0,0);
		cout<<"VVVVV"<<v<<endl;
		if(v==-1)
		{
			cout<<"信号量启动失败,程序自动退出"<<endl;
			exit(0);
		}
	}
	#endif
    pthread_t com_thread;
    pthread_create(&com_thread,NULL,Listen,(void*)NULL);
	cout<<"end at here"<<endl;	
sem_wait(sg);
	cout<<"start at here"<<endl;
	while (state->turn < 1000)
	{
		cout<<"*********"<<state->turn<<"************"<<endl;
		if (state->winner != 2)
			break;
		f_player();
		cout<<state->winner<<endl;
		for(int i=0;i<state->building[flag].size();i++)
		{
			if(state->building[flag][i].building_type==0)
				cout<<state->building[flag][i].heal<<endl;
		}
		if(!use)
			cilent.send_command(_updateAge,c1,c2);
		_updateAge = false;
		c1.clear();
		c2.clear();
		if(state->winner!=2)
			break;
		sem_wait(sg);
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
