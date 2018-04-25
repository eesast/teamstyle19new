#include"communication.h"
#include<vector>
#include<iostream>

using std::cout;
using std::endl;

extern State* state;
extern std::vector<State* > all_state;
extern int** ts19_map;
extern bool ts19_flag;

int can_build_map[200][200];//地图的点是否可建建筑


void player0();
void player1();


//两点距离 dist(p1,p2)
int dist(Position p1, Position p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

//该点是否在路边
bool near_a_road(Position p) {
    int x = p.x;
    int y = p.y;
    if (ts19_map[x][y] == 0) {
        if (ts19_map[x - 1][y] == 1)
            return 1;
        if (ts19_map[x + 1][y] == 1)
            return 1;
        if (ts19_map[x][y - 1] == 1)
            return 1;
        if (ts19_map[x][y + 1] == 1)
            return 1;
    }
    return 0;
}

//寻找该点边的路
Position find_road(Position p) {
    int x = p.x;
    int y = p.y;
    if (ts19_map[x][y] == 0) {
        if (ts19_map[x - 1][y] == 1)
            return Position(x - 1, y);
        if (ts19_map[x + 1][y] == 1)
            return Position(x + 1, y);
        if (ts19_map[x][y - 1] == 1)
            return Position(x, y - 1);
        if (ts19_map[x][y + 1] == 1)
            return Position(x, y + 1);
    }
    return Position(-1, -1);
}

bool near_my_base(Position p) {
    if (ts19_flag == 0) {
        if ((!(p.x<7 && p.y<7)) && p.x < 11 && p.y < 11)
            return 1;
        else
            return 0;
    }
    else {
        if ((!(p.x>192 && p.y>192)) && p.x > 188 && p.y > 188)
            return 1;
        else
            return 0;
    }
}
bool near_my_building(Position p) {
    bool yes = 0;
    for (int i = 1; i < state->building[ts19_flag].size(); i++) {
        if (dist(p, state->building[ts19_flag][i].pos) <2)
            return 0;
    }
    for (int i = 1; i < state->building[ts19_flag].size(); i++) {
        if (dist(p, state->building[ts19_flag][i].pos) <= 8 && dist(p, state->building[ts19_flag][i].pos) >= 2)
            yes = 1;
    }

    return yes;
}
bool can_cons(Position p) {
    if (ts19_map[p.x][p.y] == 0 && (near_my_base(p) || near_my_building(p)))
        return 1;
    else
        return 0;
}

int my_programmer_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Programmer)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_programmer_num_l0()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level == 0)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_programmer_num_l1()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level == 1)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_l0_cons_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type != Programmer && state->building[ts19_flag][i].level == 0)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_l1_cons_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type != Programmer && state->building[ts19_flag][i].level == 1)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_shannon_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Shannon)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_bool_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Bool)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_thevenin_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Thevenin)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_norton_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Norton)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_ohm_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Ohm)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_von_neumann_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Von_Neumann)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_mole_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Mole)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_larry_roberts_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Larry_Roberts)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_robert_kahn_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Robert_Kahn)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_berners_lee_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Berners_Lee)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_kuen_kao_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Kuen_Kao)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_turing_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Turing)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_tony_stark_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Tony_Stark)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
int my_hawkin_num()
{
    int programmer_num = 0;
    for (int i = 0; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].building_type == Hawkin)
        {
            programmer_num++;
        }
    }
    return programmer_num;
}
void choose_upgrade()
{
    int flag2 = 0;
    for (int i = 1; i < state->building[ts19_flag].size(); i++)
    {
        if (state->building[ts19_flag][i].level == 0 && flag2 <8)
        {
            upgrade(state->building[ts19_flag][i].unit_id);
            flag2++;
        }
    }
    cout << "成功升级" << flag2 << "个！" << endl;
    return;
}

void print_my_bd() {
    for (int i = 0; i < state->building[ts19_flag].size(); i++) {
        Building bd = state->building[ts19_flag][i];
        cout << "id:" << bd.unit_id << " type:" << bd.building_type << " level:" << bd.level << " HP:" << bd.heal << " pos:" << bd.pos.x << ' ' << bd.pos.y << endl;
    }
}
void print_my_sd() {
    for (int i = 0; i < state->soldier[ts19_flag].size(); i++) {
        Soldier sd = state->soldier[ts19_flag][i];
        cout << "id:" << sd.unit_id << " type:" << sd.soldier_name << " level:" << sd.level << " HP:" << sd.heal << " pos:" << sd.pos.x << ' ' << sd.pos.y << endl;
    }
}
void print_my_re() {
    cout << "resourse:" << state->resource[ts19_flag].resource << endl;
}
void print_my_base() {
    for (int i = 0; i < state->building[ts19_flag].size(); i++) {
        if (state->building[ts19_flag][i].building_type == 0) {
            cout << "baseHP:" << state->building[ts19_flag][i].heal << endl;
        }
    }
}

void print_info() {
    cout << "turn:" << state->turn << endl;
    print_my_re();
    print_my_base();
    //print_my_bd();
    //print_my_sd();
    cout << "programmer_num:" << my_programmer_num() << endl;
    cout << "programmer_num_0ji:" << my_programmer_num_l0() << endl;
    cout << "programmer_num_1ji:" << my_programmer_num_l1() << endl;
    cout << "l1_cons_num:" << my_l1_cons_num() << endl;

    cout << "shnnon_num:" << my_shannon_num() << endl;
    cout << "bool_num:" << my_bool_num() << endl;
    cout << "thevenin_num,norton_num,ohm_num:" << my_thevenin_num() << "," << my_norton_num() << "," << my_ohm_num() << endl;
    cout << "buiding_num:" << state->building[ts19_flag].size() << endl;
    cout << "my_age:" << state->age[ts19_flag] << endl;
}

void change_map(Position p)
{
    can_build_map[p.x][p.y] = 3;
    can_build_map[p.x + 1][p.y] = 3;
    can_build_map[p.x - 1][p.y] = 3;
    can_build_map[p.x][p.y + 1] = 3;
    can_build_map[p.x][p.y - 1] = 3;
    can_build_map[p.x + 1][p.y + 1] = 3;
    can_build_map[p.x + 1][p.y - 1] = 3;
    can_build_map[p.x - 1][p.y + 1] = 3;
    can_build_map[p.x - 1][p.y - 1] = 3;
}
void rechange_map(Position p)
{
    can_build_map[p.x][p.y] = 0;
    can_build_map[p.x + 1][p.y] = 0;
    can_build_map[p.x - 1][p.y] = 0;
    can_build_map[p.x][p.y + 1] = 0;
    can_build_map[p.x][p.y - 1] = 0;
    can_build_map[p.x + 1][p.y + 1] = 0;
    can_build_map[p.x + 1][p.y - 1] = 0;
    can_build_map[p.x - 1][p.y + 1] = 0;
    can_build_map[p.x - 1][p.y - 1] = 0;
}


////////////////////////////////////////////////////////////
void f_player()
{
    //给我自己定义的地图（用来记录该点是否有建筑的）赋初值--原始地图值
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            can_build_map[i][j] = ts19_map[i][j];
        }
    }

    if (ts19_flag == 0) {
        player0();
    }
    else
        player1();

    print_info();
    cout << endl;
};




void player0()
{
    int ins_num = 0;

    //前10回合
    if (state->turn <= 10)
    {
        if (state->turn == 2)
        {
            for (int i = 6; i < 20; i++) {
                for (int j = 6; j < 20; j++) {
                    if (can_cons(Position(i, j)) && can_build_map[i][j] == 0)
                    {
                        if (near_a_road(Position(i, j)) && state->resource[ts19_flag].resource >= 150 && state->resource[ts19_flag].building_point >= 15)
                        {
                            construct(Shannon, Position(i, j), find_road(Position(i, j)));
                            change_map(Position(i, j));
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= 6; i++) {
            for (int j = 7; j < 199; j++) {
                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 10 && can_build_map[i][j] == 0) {
                    construct(Programmer, Position(i, j), Position(0, 0));
                    change_map(Position(i, j));
                }
            }
        }
    }

    //10-20回合，建码农
    else if (state->turn <20)
    {
        if (state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 40)
        {
            if (my_programmer_num()<30)
            {
                for (int i = 1; i <= 6; i++) {
                    for (int j = 7; j < 199; j++) {
                        if (can_cons(Position(i, j)) && can_build_map[i][j] == 0) {
                            int build_size_before;
                            build_size_before = state->building[ts19_flag].size();
                            construct(Programmer, Position(i, j), Position(0, 0));
                            change_map(Position(i, j));
                            if (build_size_before < state->building[ts19_flag].size())
                                ins_num++;
                            if (ins_num > 50)
                            {
                                cout << "too many command" << ins_num << "commands" << endl; return;
                            }//判断指令数超过50
                        }
                    }
                }
            }
            else if (state->resource[ts19_flag].building_point >= 15)
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 1; i < k; i++)
                    {
                        int j = k - i;
                        if (can_cons(Position(i, j)) && can_build_map[i][j] == 0)
                        {
                            int build_size_before;
                            build_size_before = state->building[ts19_flag].size();
                            if (near_a_road(Position(i, j)))
                            {
                                if (my_shannon_num()<3)
                                    construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                else if (my_bool_num()<3)
                                    construct(Bool, Position(i, j), find_road(Position(i, j)));
                                else if (my_shannon_num()<5)
                                    construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                else
                                    construct(Bool, Position(i, j), find_road(Position(i, j)));
                            }

                            if (build_size_before < state->building[ts19_flag].size())
                                ins_num++;
                            if (ins_num > 50) { cout << "too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                        }
                    }
                }
            }
        }
    }

    //20-1000回合
    else if (state->turn < 1000)
    {
        //若为时代BIT
        if (state->age[ts19_flag] == 0)
        {
            cout << "时代0!!!" << endl;
            if (state->resource[ts19_flag].resource >= 2000)
                updateAge();
            if (state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 40)
            {
                if (my_programmer_num()<30)
                {
                    for (int i = 1; i <= 6; i++) {
                        for (int j = 7; j < 199; j++) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0) {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50)
                                {
                                    cout << "too many command" << ins_num << "commands" << endl; return;
                                }//判断指令数超过50
                            }
                        }
                    }
                }
                else if (state->resource[ts19_flag].building_point >= 15)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                if (near_a_road(Position(i, j)))
                                {
                                    if (my_shannon_num()<3)
                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                    else if (my_bool_num()<3)
                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                    else if (my_shannon_num()<5)
                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                    else
                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                }

                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }
        }//时代0

         //时代1
        else if (state->age[ts19_flag] == 1)
        {
            cout << "时代1!!!" << endl;
            if (state->resource[ts19_flag].resource >= 3501)
                updateAge();

            //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 1 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农


             //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                if (my_programmer_num()<35)
                {
                    for (int i = 1; i <= 6; i++) {
                        for (int j = 7; j < 199; j++) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量



             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                if (my_shannon_num() != 3)
                {
                    if (my_shannon_num() >3)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() < 3)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                if (my_bool_num() != 3)
                {
                    if (my_bool_num() >3)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <3)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //建造1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 1; i < k; i++)
                    {
                        int j = k - i;
                        if (can_cons(Position(i, j)))
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<3)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <11)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() <2)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }


            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

             //choose_upgrade();
        }//age=1




         //时代2
        else if (state->age[ts19_flag] == 2)
        {
            cout << "时代2!!!" << endl;
            if (state->resource[ts19_flag].resource >= 5000)
                updateAge();

            //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 2 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 80)//防无效指令超50判定
            {
                if (my_programmer_num()<40)
                {
                    for (int i = 1; i <= 6; i++) {
                        for (int j = 7; j < 199; j++) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量



             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 80)//防无效指令超50判定
            {
                if (my_shannon_num() != 3)
                {
                    if (my_shannon_num() >3)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() <3)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 80)//防无效指令超50判定
            {
                if (my_bool_num() != 3)
                {
                    if (my_bool_num() >3)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <3)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量
             //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 80)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 1; i < k; i++)
                    {
                        int j = k - i;
                        if (can_cons(Position(i, j)))
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<3)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <20)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<8)
                                    construct(Ohm, Position(i, j));
                                else if (my_thevenin_num() <2)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代2


         //时代3
        else if (state->age[ts19_flag] == 3)
        {
            cout << "时代3!!!" << endl;
            if (state->resource[ts19_flag].resource >= 6500)
                updateAge();
            //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                if (my_programmer_num()<50)
                {
                    for (int i = 1; i <= 6; i++) {
                        for (int j = 7; j < 199; j++) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量

             //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 3 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                if (my_shannon_num() != 6)
                {
                    if (my_shannon_num() >6)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() <6)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                if (my_bool_num() != 7)
                {
                    if (my_bool_num() >7)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <7)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 1; i < k; i++)
                    {
                        int j = k - i;
                        if (can_cons(Position(i, j)))
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<13)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <12)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() <11)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代3




         //时代4
        else if (state->age[ts19_flag] == 4)
        {
            cout << "时代4!!!" << endl;
            if (state->resource[ts19_flag].resource >= 8000)
                updateAge();

            //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_programmer_num()<50)
                {
                    for (int j = 1; j <= 6; j++) {
                        for (int i = 7; i < 199; i++) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量

             //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 4 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_shannon_num() != 6)
                {
                    if (my_shannon_num() >6)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() <6)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_bool_num() != 7)
                {
                    if (my_bool_num() >7)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <7)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //建造拉力罗伯茨Larry_Roberts
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_larry_roberts_num()<2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Larry_Roberts, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造罗伯特卡恩Robert_Kahn
            if (state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Robert_Kahn, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造博纳斯李Berners_Lee
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Berners_Lee, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//博纳斯李

             //建造高琨Kuen_Kao
            if (state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_kuen_kao_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Kuen_Kao, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Kuen_kao
             //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 1; i < k; i++)
                    {
                        int j = k - i;
                        if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 120)
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<13)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <12)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() <11)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代4

         //时代5
        else if (state->age[ts19_flag] == 5)
        {
            cout << "时代5!!!" << endl;

            //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_programmer_num()<60)
                {
                    for (int j = 1; j <= 6; j++) {
                        for (int i = 7; i < 199; i++) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 140 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量

             //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 5 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_shannon_num() != 6)
                {
                    if (my_shannon_num() >6)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() <6)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_bool_num() != 7)
                {
                    if (my_bool_num() >7)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <7)
                    {
                        for (int k = 7; k < 30; k++)
                        {
                            for (int i = 1; i < k; i++)
                            {
                                int j = k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //建造拉力罗伯茨Larry_Roberts
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_larry_roberts_num()<2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Larry_Roberts, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造罗伯特卡恩Robert_Kahn
            if (state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Robert_Kahn, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造博纳斯李Berners_Lee
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Berners_Lee, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//博纳斯李

             //建造高琨Kuen_Kao
            if (state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_kuen_kao_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Kuen_Kao, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Kuen_kao

             //建造图灵Turing
            if (state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_turing_num() < 3)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Turing, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//turing

             //建造霍金Hawkin
            if (state->resource[ts19_flag].building_point >= 50 && state->resource[ts19_flag].resource >= 500 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_hawkin_num() < 3)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Hawkin, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Hawkin

             //建造托尼-斯塔克Tony_Stark
            if (state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                int flag4 = 0;
                for (int i = 0; i<state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Thevenin)
                    {
                        Position pp;
                        pp = state->building[ts19_flag][i].pos;
                        sell(state->building[ts19_flag][i].unit_id);
                        construct(Tony_Stark, pp, find_road(pp));
                        flag4 = 1;
                        break;
                    }
                }
                if (flag4 == 0)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 1; i < k; i++)
                        {
                            int j = k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Tony_Stark, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Tony_Stark
             //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 1; i < k; i++)
                    {
                        int j = k - i;
                        if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 140)
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0) {
                                    construct(Ohm, Position(i, j));
                                    change_map(Position(i, j));
                                }
                                else if (my_norton_num() == 0) {
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                }
                                else if (my_ohm_num()<13) {
                                    construct(Ohm, Position(i, j));
                                    change_map(Position(i, j));
                                }
                                else if (my_norton_num() <12) {
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                }


                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代5
    }//turn
}





void player1()
{
    int ins_num = 0;

    //前10回合
    if (state->turn <= 10)
    {
        if (state->turn == 2)
        {
            for (int i = 193; i > 179; i--) {
                for (int j = 193; j > 179; j--) {
                    if (can_cons(Position(i, j)) && can_build_map[i][j] == 0)
                    {
                        if (near_a_road(Position(i, j)) && state->resource[ts19_flag].resource >= 150 && state->resource[ts19_flag].building_point >= 15)
                        {
                            construct(Shannon, Position(i, j), find_road(Position(i, j)));
                            change_map(Position(i, j));

                        }
                    }
                }
            }
        }
        for (int i = 198; i >= 193; i--) {
            for (int j = 192; j > 1; j--) {
                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 10 && can_build_map[i][j] == 0) {
                    construct(Programmer, Position(i, j), Position(0, 0));
                    change_map(Position(i, j));
                }
            }
        }
    }

    //10-20回合，建码农
    else if (state->turn <20)
    {
        if (state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 40)
        {
            if (my_programmer_num()<30)
            {
                for (int i = 198; i >= 193; i--) {
                    for (int j = 192; j > 1; j--) {
                        if (can_cons(Position(i, j)) && can_build_map[i][j] == 0) {
                            int build_size_before;
                            build_size_before = state->building[ts19_flag].size();
                            construct(Programmer, Position(i, j), Position(0, 0));
                            change_map(Position(i, j));
                            if (build_size_before < state->building[ts19_flag].size())
                                ins_num++;
                            if (ins_num > 50)
                            {
                                cout << "too many command" << ins_num << "commands" << endl; return;
                            }//判断指令数超过50
                        }
                    }
                }
            }
            else if (state->resource[ts19_flag].building_point >= 15)
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 198; i >199 - k; i--)
                    {
                        int j = 398 - k - i;
                        if (can_cons(Position(i, j)) && can_build_map[i][j] == 0)
                        {
                            int build_size_before;
                            build_size_before = state->building[ts19_flag].size();
                            if (near_a_road(Position(i, j)))
                            {
                                if (my_shannon_num()<3)
                                    construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                else if (my_bool_num()<3)
                                    construct(Bool, Position(i, j), find_road(Position(i, j)));
                                else if (my_shannon_num()<5)
                                    construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                else
                                    construct(Bool, Position(i, j), find_road(Position(i, j)));
                            }

                            if (build_size_before < state->building[ts19_flag].size())
                                ins_num++;
                            if (ins_num > 50) { cout << "too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                        }
                    }
                }
            }
        }
    }

    //20-1000回合
    else if (state->turn < 1000)
    {
        //若为时代BIT
        if (state->age[ts19_flag] == 0)
        {
            cout << "时代0!!!" << endl;
            if (state->resource[ts19_flag].resource >= 2000)
                updateAge();
            if (state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 40)
            {
                if (my_programmer_num()<30)
                {
                    for (int i = 198; i >= 193; i--) {
                        for (int j = 192; j>1; j--) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0) {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50)
                                {
                                    cout << "too many command" << ins_num << "commands" << endl; return;
                                }//判断指令数超过50
                            }
                        }
                    }
                }
                else if (state->resource[ts19_flag].building_point >= 15)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                if (near_a_road(Position(i, j)))
                                {
                                    if (my_shannon_num()<3)
                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                    else if (my_bool_num()<3)
                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                    else if (my_shannon_num()<5)
                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                    else
                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                }

                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }
        }//时代0

         //时代1
        else if (state->age[ts19_flag] == 1)
        {
            cout << "时代1!!!" << endl;
            if (state->resource[ts19_flag].resource >= 3501)
                updateAge();

            //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 1 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                if (my_programmer_num()<35)
                {
                    for (int i = 198; i >= 193; i--) {
                        for (int j = 192; j > 1; j--) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量


             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                if (my_shannon_num() != 3)
                {
                    if (my_shannon_num() >3)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() < 3)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                if (my_bool_num() != 3)
                {
                    if (my_bool_num() >3)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <3)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //建造1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 60)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 198; i >199 - k; i--)
                    {
                        int j = 398 - k - i;
                        if (can_cons(Position(i, j)))
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<3)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <11)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() <2)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑
             //choose_upgrade();
        }//age=1




         //时代2
        else if (state->age[ts19_flag] == 2)
        {
            cout << "时代2!!!" << endl;
            if (state->resource[ts19_flag].resource >= 5000)
                updateAge();

            //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 2 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 80)//防无效指令超50判定
            {
                if (my_programmer_num()<40)
                {
                    for (int i = 198; i >= 193; i--) {
                        for (int j = 192; j > 1; j--) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量

             //控制shannon数量


            if (my_shannon_num() != 3)
            {
                if (my_shannon_num() >3)
                {
                    for (int i = 0; i<state->building[ts19_flag].size(); i++)
                    {
                        if (state->building[ts19_flag][i].building_type == Shannon)
                        {
                            sell(state->building[ts19_flag][i].unit_id);
                            ins_num++;
                            rechange_map(state->building[ts19_flag][i].pos);
                            break;
                        }
                    }
                }
                if (my_shannon_num() <3 && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 80)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();

                                    construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }
                            }
                        }
                    }
                }
            }
            //shannon数量
            //控制bool数量

            if (my_bool_num() != 3)
            {
                if (my_bool_num() >3)
                {
                    for (int i = 0; i<state->building[ts19_flag].size(); i++)
                    {
                        if (state->building[ts19_flag][i].building_type == Shannon)
                        {
                            sell(state->building[ts19_flag][i].unit_id);
                            rechange_map(state->building[ts19_flag][i].pos);
                            ins_num++;
                            break;
                        }
                    }
                }
                if (my_bool_num() <3 && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 80)//防无效指令超50判定
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();

                                    construct(Bool, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }
                            }
                        }
                    }
                }
            }
            //bool数量

            //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 80)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 198; i >199 - k; i--)
                    {
                        int j = 398 - k - i;
                        if (can_cons(Position(i, j)))
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<3)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <20)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<8)
                                    construct(Ohm, Position(i, j));
                                else if (my_thevenin_num() <2)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代2


         //时代3
        else if (state->age[ts19_flag] == 3)
        {
            cout << "时代3!!!" << endl;
            if (state->resource[ts19_flag].resource >= 6500)
                updateAge();
            //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                if (my_programmer_num()<50)
                {
                    for (int i = 198; i >= 193; i--) {
                        for (int j = 192; j > 1; j--) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量

             //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 3 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农


             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                if (my_shannon_num() != 6)
                {
                    if (my_shannon_num() >6)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() <6)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                if (my_bool_num() != 7)
                {
                    if (my_bool_num() >7)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <7)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 100)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 198; i >199 - k; i--)
                    {
                        int j = 398 - k - i;
                        if (can_cons(Position(i, j)))
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<13)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <12)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() <11)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代3




         //时代4
        else if (state->age[ts19_flag] == 4)
        {
            cout << "时代4!!!" << endl;
            if (state->resource[ts19_flag].resource >= 8000)
                updateAge();

            //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_programmer_num()<50)
                {
                    for (int i = 198; i >= 193; i--) {
                        for (int j = 192; j > 1; j--) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量

             //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 4 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_shannon_num() != 6)
                {
                    if (my_shannon_num() >6)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() <6)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_bool_num() != 7)
                {
                    if (my_bool_num() >7)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <7)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //建造拉力罗伯茨Larry_Roberts
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_larry_roberts_num()<2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Larry_Roberts, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造罗伯特卡恩Robert_Kahn
            if (state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Robert_Kahn, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造博纳斯李Berners_Lee
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Berners_Lee, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//博纳斯李

             //建造高琨Kuen_Kao
            if (state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                if (my_kuen_kao_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 120)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Kuen_Kao, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Kuen_kao
             //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 120)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 198; i >199 - k; i--)
                    {
                        int j = 398 - k - i;
                        if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 120)
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() == 0)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() == 0)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                else if (my_ohm_num()<13)
                                    construct(Ohm, Position(i, j));
                                else if (my_norton_num() <12)
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                else if (my_thevenin_num() <11)
                                    construct(Thevenin, Position(i, j), find_road(Position(i, j)));

                                construct(Thevenin, Position(i, j), find_road(Position(i, j)));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代4

         //时代5
        else if (state->age[ts19_flag] == 5)
        {
            cout << "时代5!!!" << endl;

            //控制码农数量
            if (state->resource[ts19_flag].resource >= 100 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_programmer_num()<60)
                {
                    for (int i = 198; i >= 193; i--) {
                        for (int j = 192; j > 1; j--) {
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 10 && state->building[ts19_flag].size() <= 140 && state->resource[ts19_flag].resource >= 100)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();
                                construct(Programmer, Position(i, j), Position(0, 0));
                                change_map(Position(i, j));
                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "控制码农数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }
                        }
                    }
                }
            }//码农数量

             //升级码农
            if (state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)//防无效指令超50判定
            {
                for (int i = 1; i < state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Programmer && state->building[ts19_flag][i].level < 5 && state->resource[ts19_flag].resource >= 50 && state->resource[ts19_flag].building_point >= 5)
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级码农

             //控制shannon数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_shannon_num() != 6)
                {
                    if (my_shannon_num() >6)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                ins_num++;
                                rechange_map(state->building[ts19_flag][i].pos);
                                break;
                            }
                        }
                    }
                    if (my_shannon_num() <6)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制shannon数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//shannon数量
             //控制bool数量
            if (state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_bool_num() != 7)
                {
                    if (my_bool_num() >7)
                    {
                        for (int i = 0; i<state->building[ts19_flag].size(); i++)
                        {
                            if (state->building[ts19_flag][i].building_type == Shannon)
                            {
                                sell(state->building[ts19_flag][i].unit_id);
                                rechange_map(state->building[ts19_flag][i].pos);
                                ins_num++;
                                break;
                            }
                        }
                    }
                    if (my_bool_num() <7)
                    {
                        for (int k = 7; k < 50; k++)
                        {
                            for (int i = 198; i >199 - k; i--)
                            {
                                int j = 398 - k - i;
                                if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 15 && state->resource[ts19_flag].building_point >= 150 && can_build_map[i][j] == 0)
                                {
                                    if (near_a_road(Position(i, j)))
                                    {
                                        int build_size_before;
                                        build_size_before = state->building[ts19_flag].size();

                                        construct(Bool, Position(i, j), find_road(Position(i, j)));
                                        change_map(Position(i, j));
                                        if (build_size_before < state->building[ts19_flag].size())
                                            ins_num++;
                                        if (ins_num > 50) { cout << "控制bool数量too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                    }
                                }
                            }
                        }
                    }
                }
            }//bool数量

             //建造拉力罗伯茨Larry_Roberts
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_larry_roberts_num()<2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Larry_Roberts, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造罗伯特卡恩Robert_Kahn
            if (state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 2)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 45 && state->resource[ts19_flag].resource >= 450 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Robert_Kahn, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }

            }
            //建造博纳斯李Berners_Lee
            if (state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_robert_kahn_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 25 && state->resource[ts19_flag].resource >= 250 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Berners_Lee, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//博纳斯李

             //建造高琨Kuen_Kao
            if (state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_kuen_kao_num() < 5)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 40 && state->resource[ts19_flag].resource >= 400 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Kuen_Kao, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Kuen_kao

             //建造图灵Turing
            if (state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_turing_num() < 3)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Turing, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//turing

             //建造霍金Hawkin
            if (state->resource[ts19_flag].building_point >= 50 && state->resource[ts19_flag].resource >= 500 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                if (my_hawkin_num() < 3)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Hawkin, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Hawkin

             //建造托尼-斯塔克Tony_Stark
            if (state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                int flag4 = 0;
                for (int i = 0; i<state->building[ts19_flag].size(); i++)
                {
                    if (state->building[ts19_flag][i].building_type == Thevenin)
                    {
                        Position pp;
                        pp = state->building[ts19_flag][i].pos;
                        sell(state->building[ts19_flag][i].unit_id);
                        construct(Tony_Stark, pp, find_road(pp));
                        flag4 = 1;
                        break;
                    }
                }
                if (flag4 == 0)
                {
                    for (int k = 7; k < 50; k++)
                    {
                        for (int i = 198; i >199 - k; i--)
                        {
                            int j = 398 - k - i;
                            if (can_cons(Position(i, j)) && can_build_map[i][j] == 0 && state->resource[ts19_flag].building_point >= 60 && state->resource[ts19_flag].resource >= 600 && state->building[ts19_flag].size() <= 140)
                            {
                                if (near_a_road(Position(i, j)))
                                {
                                    int build_size_before;
                                    build_size_before = state->building[ts19_flag].size();
                                    construct(Tony_Stark, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                    if (build_size_before < state->building[ts19_flag].size())
                                        ins_num++;
                                    if (ins_num > 50) { cout << "建造larry_robertstoo many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                                }

                            }
                        }
                    }
                }
            }//Tony_Stark
             //控制1时代3种建筑
            if (state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 140)//防无效指令超50判定
            {
                for (int k = 7; k < 50; k++)
                {
                    for (int i = 198; i >199 - k; i--)
                    {
                        int j = 398 - k - i;
                        if (can_cons(Position(i, j)) && state->resource[ts19_flag].building_point >= 20 && state->resource[ts19_flag].resource >= 200 && state->building[ts19_flag].size() <= 140)
                        {
                            if (near_a_road(Position(i, j)) && can_build_map[i][j] == 0)
                            {
                                int build_size_before;
                                build_size_before = state->building[ts19_flag].size();

                                if (my_ohm_num() == 0) {
                                    construct(Ohm, Position(i, j));
                                    change_map(Position(i, j));
                                }
                                else if (my_norton_num() == 0) {
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                }
                                else if (my_ohm_num()<13) {
                                    construct(Ohm, Position(i, j));
                                    change_map(Position(i, j));
                                }
                                else if (my_norton_num() <12) {
                                    construct(Norton, Position(i, j), find_road(Position(i, j)));
                                    change_map(Position(i, j));
                                }


                                if (build_size_before < state->building[ts19_flag].size())
                                    ins_num++;
                                if (ins_num > 50) { cout << "建造1时代建筑too many command" << ins_num << "commands" << endl; return; }//判断指令数超过50
                            }

                        }
                    }
                }
            }

            //升级建筑
            for (int i = 1; i < state->building[ts19_flag].size(); i++)
            {
                if (state->resource[ts19_flag].resource >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][6]
                    && state->resource[ts19_flag].building_point >= OriginalBuildingAttribute[state->building[ts19_flag][i].building_type][7])//防无效指令超50判定
                {
                    if (state->building[ts19_flag][i].level < state->age[ts19_flag])
                    {
                        upgrade(state->building[ts19_flag][i].unit_id);
                    }
                }

            }//升级建筑

        }//时代5
    }//turn
}
