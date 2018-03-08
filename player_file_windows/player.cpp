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
	//player start at here;
	//获取全局状态用state指针 具体见communication中State的定义
	//以下几个命令是提供给选手的全部接口
/*	void updateAge();
	void construct(BuildingType building_type, Position pos, Position solider_pos); //The solier position is not set now
	void upgrade(int unit_id);
	void sell(int unit_id);
	void toggleMaintain(int unit_id);*/
	//没有逻辑意义的测试通信的代码
	/*construct(BuildingType(1), Position(3, 3), Position(4, 4));
	construct(BuildingType(2), Position(5, 5), Position(5, 6));
	construct(BuildingType(1), Position(5, 3), Position(5, 2));
	upgrade(0);
	upgrade(1);
	upgrade(2);
	updateAge();*/
	construct(BuildingType(4), Position(10, 10), Position(7, 7));
};