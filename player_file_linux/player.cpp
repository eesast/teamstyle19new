#include"communication.h"
#include<vector>
using namespace std;

extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2>c2;
extern State* state ;
extern bool** map;
extern bool flag;
void f_player()
{
	construct(BuildingType(1), Position(3, 3), Position(4, 4));
	construct(BuildingType(2), Position(5, 5), Position(5, 6));
	construct(BuildingType(1), Position(5, 3), Position(5, 2));
	upgrade(0);
	upgrade(1);
	upgrade(2);
	updateAge();
};