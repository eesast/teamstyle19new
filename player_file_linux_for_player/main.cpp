#include"communication.h"
#include<pthread.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<semaphore.h>
#include <chrono>  
#include <random>  
#include<sstream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

bool fail=false;
extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2> c2;
void f_player();

State* state=NULL;
State* _state=NULL;
vector<State* > all_state;
MyClient cilent;
int** ts19_map;
bool ts19_flag;
bool goon = true;
bool use=false;
sem_t *sg=new sem_t;
bool discon=false;

void* Listen(void* arg)
{
	State* t;
	while (goon)
	{
		State* s = cilent.recv_state();
		if(discon)
			{
				sem_post(sg);
				break;
			}
		_state=s;
		all_state.push_back(_state);
		sem_post(sg);
		if(_state->winner!=2)
			break;	
	}
	return NULL;
}

int main()
{
	cilent.start_connection();
	if(fail)
	{
		return 0;
	}
	ts19_map = cilent.map;
	ts19_flag = cilent.flag;
	#ifdef __APPLE__
	{
		unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 g1(seed1);
		int r1=g1();
		int r2=r1+1;
		stringstream s;
		if(ts19_flag==0)
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
		if(v==-1)
		{
			cout<<"信号量启动失败,程序自动退出"<<endl;
			exit(0);
		}
	}
	#endif
    pthread_t com_thread;
    pthread_create(&com_thread,NULL,Listen,(void*)NULL);
	sem_wait(sg);
	while (_state->turn < 1000)
	{
		if (_state->winner != 2)
			break;
		state=_state;
		f_player();
		if(!use)
			cilent.send_command(_updateAge,c1,c2);
		_updateAge = false;
		c1.clear();
		c2.clear();
		if(_state->winner!=2)
			break;
		sem_wait(sg);
		if(discon)
		{
			return 0;
		}
	}
	if (_state->winner == 1)
		cout << "Winner is 1" << endl;
	else if (_state->winner == 0)
		cout << "Winner is 0" << endl;
	else if (_state->winner == 2)
		cout << "draw" << endl;
	goon = false;

	pthread_join(com_thread,NULL);
}
