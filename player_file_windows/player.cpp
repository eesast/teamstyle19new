#include"communication.h"
#include<vector>
#include<iostream>

using std::cout;
using std::endl;

extern State* state;
extern std::vector<State* > all_state;
extern int** ts19_map;
extern bool ts19_flag;


void player0();
void player1();



int dist(Position p1, Position p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
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
    for (int i = 0; i < state->building[ts19_flag].size(); i++) {
        if (dist(p, state->building[ts19_flag][i].pos) <= 8)
            yes = 1;
        if (p.x == state->building[ts19_flag][i].pos.x && p.y == state->building[ts19_flag][i].pos.y)
            yes = 0;
    }
    return yes;
}
bool can_cons(Position p) {
    if (ts19_map[p.x][p.y] == 0 && (near_my_base(p) || near_my_building(p)))
        return 1;
    else
        return 0;
}
void print_my_bd() {
    for (int i = 0; i < state->building[ts19_flag].size(); i++) {
        Building bd = state->building[ts19_flag][i];
        cout << "id:" << bd.unit_id << " type:" << bd.building_type << " HP:" << bd.heal << " pos:" << bd.pos.x << ' ' << bd.pos.y << endl;
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
    print_my_bd();
}
void f_player()
{
    /*
    if (state->turn == 1) {
    for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 200; j++) {
    cout << ts19_map[i][j];
    }
    cout << endl;
    }
    }
    */
    if (ts19_flag == 0)
        player0();
    else
        player1();

    print_info();


};
void player0() {
    int ins_num = 0;
    if (state->turn < 100) {
        for (int i = 6; i < 20; i++) {
            for (int j = 6; j < 20; j++) {
                if (can_cons(Position(i, j))) {
                    if (near_a_road(Position(i, j)) && state->resource[ts19_flag].resource >= 1000)
                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                    else
                        construct(Programmer, Position(i, j), Position(0, 0));
                    ins_num++;
                    if (ins_num > 50)
                        return;
                }
            }
        }
    }
}
void player1() {
    int ins_num = 0;
    if (state->turn < 100) {
        for (int i = 193; i > 180; i--) {
            for (int j = 193; j > 180; j--) {
                if (can_cons(Position(i, j))) {
                    if (near_a_road(Position(i, j)) && state->resource[ts19_flag].resource >= 1000)
                        construct(Shannon, Position(i, j), find_road(Position(i, j)));
                    else
                        construct(Programmer, Position(i, j), Position(0, 0));
                    ins_num++;
                    if (ins_num > 50)
                        return;
                }
            }
        }
    }
}
