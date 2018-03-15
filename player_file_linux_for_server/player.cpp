#include"communication.h"
#include<iostream>
#include<vector>
using namespace std;

extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2>c2;
extern State* state ;
extern int** map;
extern bool flag;
void f_player()
{
	for(int i=0;i<200;i++)
	{	for(int j=0;j<200;j++)
		{
			cout<<map[i][j];
		}
		cout<<endl;
	}
};