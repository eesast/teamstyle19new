#include"communication.h"
#include<vector>
#include<iostream>
using namespace std;

extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2>c2;
extern State* state ;
extern int** map;
extern bool flag;


void player0();
void player1();



int dist(Position p1, Position p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
bool near_a_road(Position p) {
    int x = p.x;
    int y = p.y;
    if (map[x][y] == 0) {
        if (map[x - 1][y] == 1)
            return 1;
        if (map[x + 1][y] == 1)
            return 1;
        if (map[x][y - 1] == 1)
            return 1;
        if (map[x][y + 1] == 1)
            return 1;
    }
    return 0;
}
Position find_road(Position p) {
    int x = p.x;
    int y = p.y;
    if(map[x][y] == 0){
        if (map[x - 1][y] == 1)
            return Position(x - 1, y);
        if (map[x + 1][y] == 1)
            return Position(x + 1, y);
        if (map[x][y - 1] == 1)
            return Position(x, y - 1);
        if (map[x][y + 1] == 1)
            return Position(x, y + 1);
    }
}
bool near_my_base(Position p) {
    if (flag == 0) {
        if (p.x < 11 && p.y < 11)
            return 1;
        else
            return 0;
    }
    else {
        if (p.x > 188 && p.y > 18)
            return 1;
        else
            return 0;
    }
}
bool near_my_building(Position p) {
    bool yes = 0;
    int my_bd_num = state->building[flag].size();
    for (int i = 0; i < my_bd_num; i++) {
        if (dist(p, state->building[flag][i].pos) <= 8)
            yes = 1;
        if (p.x == state->building[flag][i].pos.x && p.y == state->building[flag][i].pos.y)
            yes = 0;
    }
    return yes;
}
bool can_cons(Position p) {
    if (map[p.x][p.y] == 0 && (near_my_base(p) || near_my_building(p)))
        return 1;
    else
        return 0;
}
void print_my_bd() {
    int my_bd_num = state->building[flag].size();
    for (int i = 0; i < my_bd_num; i++) {
        Building bd = state->building[flag][i];
        cout << "id:" << bd.unit_id << " type:" << bd.building_type << " pos:" << bd.pos.x << ' ' << bd.pos.y << endl;
    }
}
void print_my_re() {
    cout << "resourse:" << state->resource[flag].resource << endl;
}
void print_info() {
    cout << "turn:" << state->turn << endl;
    print_my_re();
    print_my_bd();
}
void f_player()
{
    if (state->turn == 1) {
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 200; j++) {
                cout << map[i][j];
            }
            cout << endl;
        }
    }
    if (flag == 0)
        player0();
    else
        player1();
    print_info();
    
    
};
void player0() {
    if (state->turn < 100) {
        for (int i = 6; i < 200; i++) {
            for (int j = 6; j < 200; j++) {
                if (can_cons(Position(i, j))) {
                    if (near_a_road(Position(i, j))) 
                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                    else
                        construct(Programmer, Position(i, j), Position(0, 0));
                }
            }
        }
    }
}
void player1() {
    if (state->turn < 100) {
        for (int i = 193; i > 0; i--) {
            for (int j = 193; j > 0; j--) {
                if (can_cons(Position(i, j))) {
                    if (near_a_road(Position(i, j)))
                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                    else
                        construct(Programmer, Position(i, j), Position(0, 0));
                }
            }
        }
    }
}
