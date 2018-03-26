#include"communication.h"
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

#define AgeCostBase 2000
#define AgeCostPerLevel 1500
#define BuildingRestrictBase 40
#define BuildingRestrictPerLevel 20
#define CostCoeff 0.5

extern	bool _updateAge;
extern vector<command1> c1;
extern vector<command2>c2;
extern State* state ;
extern vector<State* > all_state;
extern int** map;
extern bool flag;
void player0();
void player1();

struct Position_mod {
    int x;
    int y;
    Position_mod(int x = -1, int y = -1): x(x), y(y) {}
    Position_mod(Position pos): x(pos.x), y(pos.y) {}
    bool operator==(const Position_mod &rhs) {
        return (x == rhs.x && y == rhs.y);
    }
};

int correct_pos[200][200];
float params[20];
Position_mod my_base_pos = Position_mod(0,0);
vector<vector<Position_mod> > path; 
vector<vector<int> > path_counter;
vector<Position_mod> path_corner;
vector<float> path_slope;
vector<vector<int> > defense_building;
float reward[7][8];
int Programmer_num = 0;

int get_distance(Position_mod i, Position_mod j){
    return abs(i.x - j.x) + abs(i.y - j.y);
}

bool check_access(int x, int y, bool check = false){
    return (x >= 0 && x < 200 && y >= 0 && y < 200 && map[x][y] == check);
}

bool check_in_base(int x, int y){
    return (x >= my_base_pos.x - 3 && x <= my_base_pos.x + 3 &&
        y >= my_base_pos.y - 3 && y <= my_base_pos.y + 3);
}

void get_path(){
    /*
    cout<<"map:"<<endl;
    for(int x = 0; x < 200; x++){
        for(int y = 0; y < 200; y++){
            cout<<map[x][y]<<" ";
        }
        cout<<endl;
    }
    */
    bool has_corner = false;
    cout<<"Begin to get path!"<<endl;
    my_base_pos = state->building[(int)flag][0].pos;
    cout<<"Base pos ("<<my_base_pos.x<<", "<<my_base_pos.y<<")"<<endl;
    for(int xi = -7; xi <= 7; xi++){
        for(int yi = -7; yi <= 7; yi++){
            if(abs(xi) <= 6 && abs(yi) <= 6){
                //cout<<"In base pos ("<<my_base_pos.x+xi<<", "<<my_base_pos.y+yi<<")"<<endl;
                continue;
            }
            //cout<<"Check pos ("<<my_base_pos.x+xi<<", "<<my_base_pos.y+yi<<")"<<endl;
            if(check_access(my_base_pos.x+xi, my_base_pos.y+yi, true)){
                //cout<<"find path on ("<<my_base_pos.x+xi<<", "<<my_base_pos.y+yi<<")"<<endl;
                vector<Position_mod> path_single;
                int pos_x = my_base_pos.x + xi;
                int pos_y = my_base_pos.y + yi;
                path_single.push_back(Position_mod(pos_x, pos_y));
                int last_pos_x = pos_x;
                int last_pos_y = pos_y;
                int back = -2;
                while(1){
                    if(abs((199 - my_base_pos.x) - pos_x) <= 7 &&
                        abs((199 - my_base_pos.y) - pos_y) <= 7)
                        break;
                    for(int xii = -1; xii <= 1; xii++){
                        for(int yii = abs(xii) - 1; yii <= 1 - abs(xii); yii++){
                            vector<Position_mod>::iterator it = find(path_single.begin(), 
                                path_single.end(), Position_mod(pos_x+xii, pos_y+yii));
                            if(it != path_single.end()) continue;
                            if(check_access(pos_x+xii, pos_y+yii, true)){
                                pos_x += xii;
                                pos_y += yii;
                                //cout<<"find path on ("<<pos_x<<", "<<pos_y<<")"<<endl;
                                if(pos_x == pos_y && my_base_pos.x + my_base_pos.y == 199 && has_corner == false){
                                    path_corner.push_back(Position_mod(pos_x, pos_y));
                                    path_slope.push_back((float)abs(pos_y - path_single[0].y) / 
                                        (float)abs(pos_x - path_single[0].x));
                                    has_corner = true;
                                }
                                if(pos_x + pos_y == 199 && my_base_pos.x == my_base_pos.y && has_corner == false){
                                    path_corner.push_back(Position_mod(pos_x, pos_y));
                                    path_slope.push_back((float)abs(pos_y - path_single[0].y) / 
                                        (float)abs(pos_x - path_single[0].x));
                                    has_corner = true;
                                }
                                path_single.push_back(Position_mod(pos_x, pos_y));
                            }
                        }
                    }
                    if(pos_x == last_pos_x && pos_y == last_pos_y){
                        pos_x = path_single[path_single.size()+back].x;
                        pos_y = path_single[path_single.size()+back].y;
                        back -= 1;
                        cout<<"Fail to find road on ("<<last_pos_x<<", "<<last_pos_y<<"), go back!"<<endl;
                    } else {
                        back = -2;
                    }
                    last_pos_x = pos_x;
                    last_pos_y = pos_y;
                }
                path.push_back(path_single);
                cout<<"Finish get path "<<path.size()<<"!"<<endl;
                has_corner = false;
            }
        }
    }
    vector<int> tmp;
    for(int i = 0; i < 8; i++){
        tmp.push_back(0);
    }
    for(int i = 0; i < path.size(); i++){
        defense_building.push_back(tmp);
    }
}

void get_correct_pos(){
    for(int i = 0; i < state->building[(int)flag].size(); i++){
        if(state->building[(int)flag][i].building_type == __Base){
            for(int xi = -10; xi <= 10; xi++)
                for(int yi = -10; yi <= 10; yi++){
                    if(!check_access(state->building[(int)flag][i].pos.x + xi,
                        state->building[(int)flag][i].pos.y + yi))
                        continue;
                    if(abs(xi) <= 6 && abs(yi) <= 6)
                        correct_pos[state->building[(int)flag][i].pos.x + xi]
                            [state->building[(int)flag][i].pos.y + yi] = 0;
                    else{
                        correct_pos[state->building[(int)flag][i].pos.x + xi]
                            [state->building[(int)flag][i].pos.y + yi] = 1;
                        // cout<<"set pos: ("<<state->building[(int)flag][i].pos.x + xi<<", "<<
                        //     state->building[(int)flag][i].pos.y + yi<<")"<<endl;
                    }
                }
        }
        else{
            correct_pos[state->building[(int)flag][i].pos.x]
                [state->building[(int)flag][i].pos.y] = 0;
            for(int xi = -1; xi <= 1; xi ++)
                for(int yi = -1; yi <= 1; yi ++){
                    if(!check_access(state->building[(int)flag][i].pos.x + xi,
                        state->building[(int)flag][i].pos.y + yi))
                        continue;
                    if(correct_pos[xi][yi] == -1)
                        correct_pos[xi][yi] = 1;
                }
        }
    }
}

void count_path(){
    for(int i = 0; i < state->soldier[(int)flag].size(); i++){
        Position_mod soldier_pos = state->soldier[(int)flag][i].pos;
        for(int path_i = 0; path_i < path.size(); path_i++){
            vector<Position_mod>::iterator it = find(path[path_i].begin(),
                    path[path_i].end(), soldier_pos);
            if(it != path[path_i].end()){
                path_counter[path_i][state->soldier[(int)flag][i].soldier_name]++;
                break;
            }
        }
    }
}

void get_path_reward(){
    int defense_building_num = 0;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 8; j++){
            reward[i][j] = 0.0;
        }
    }
    int _type;
    for(_type = Bool; _type <= Hawkin; _type++){
        if(_type == Ohm){
            for(int i = 0; i < path_counter.size(); i++){
                for(int j = 0; j < 8; j++){
                    if(j == 1 || j == 2){
                        reward[i][_type - Bool] += 2 * path_counter[i][j];
                    } else {
                        reward[i][_type - Bool] += path_counter[i][j];
                    }
                    defense_building_num += defense_building[i][j];
                }
                if(defense_building_num == 0) defense_building_num = 1;
                reward[i][_type - Bool] /= pow((float)defense_building_num, 2);
            }
        } else if(_type == Larry_Roberts){
            for(int i = 0; i < path_counter.size(); i++){
                for(int j = 0; j < 8; j++){
                    if(j == 4){
                        reward[i][_type - Bool] += 2 * path_counter[i][j];
                    } else {
                        reward[i][_type - Bool] += path_counter[i][j];
                    }
                    defense_building_num += defense_building[i][j];
                }
                if(defense_building_num == 0) defense_building_num = 1;
                reward[i][_type - Bool] /= pow((float)defense_building_num, 2);
            }
        } else if(_type == Musk){
            for(int i = 0; i < path_counter.size(); i++){
                if(defense_building[i][_type - Bool] > 0){
                    reward[i][_type - Bool] = 0.0;
                    continue;
                }
                for(int j = 0; j < 8; j++){
                    if(j == 6 || j == 7){
                        reward[i][_type - Bool] += 3 * path_counter[i][j];
                    } else {
                        reward[i][_type - Bool] += path_counter[i][j];
                    }
                    defense_building_num += defense_building[i][j];
                }
                if(defense_building_num == 0) defense_building_num = 1;
                reward[i][_type - Bool] /= pow((float)defense_building_num, 2);
            }
        } else {
            for(int i = 0; i < path_counter.size(); i++){
                for(int j = 0; j < 8; j++){
                    reward[i][_type - Bool] += path_counter[i][j];
                    defense_building_num += defense_building[i][j];
                }
                if(defense_building_num == 0) defense_building_num = 1;
                reward[i][_type - Bool] /= pow((float)defense_building_num, 2);
            }
        }
    }
}

Position_mod get_nearest_Position_mod(Position_mod &road, int _type, int cons_dis, int &best_path){
    Position_mod best_pos = Position_mod(0,0);
    float most_num = 0.;
    int best_dis = 401;
    float best_reward = 0;
    if(_type >= Bool && _type <= Hawkin){
        for(int i = 0; i < path.size(); i++){
            if(reward[i][_type - Bool] > best_reward){
                best_reward = reward[i][_type - Bool];
                best_path = i;
            }
        }
    }
    for(int x = 0; x < 200; x++){
        for(int y = 0; y < 200; y++){
            if(correct_pos[x][y] == 1){
                int dis = get_distance(Position_mod(x, y), Position_mod(199 - 
                    my_base_pos.x, 199 - my_base_pos.y));
                if((_type < Bool || _type > Hawkin) && dis < best_dis){
                    if(_type >= Shannon && _type <= Tony_Stark){
                        bool in_road = false;
                        for(int xi = -cons_dis; xi <= cons_dis; xi ++)
                            for(int yi = -abs(cons_dis - abs(xi));
                                yi <= abs(cons_dis - abs(xi)); yi++){
                                if(map[x+xi][y+yi] == 1 && !check_in_base(x+xi, y+yi)){
                                    in_road = true;
                                    road = Position_mod(x+xi, y+yi);
                                }
                            }
                        if(!in_road) continue;
                    } 
                    best_dis = dis;
                    best_pos = Position_mod(x, y);
                } else if(_type >= Bool && _type <= Hawkin) {
                    float new_x = (x + path_slope[best_path] * y + powf(path_slope[best_path], 2)
                        * path_corner[best_path].x - path_slope[best_path] * path_corner[best_path].y) /
                        (powf(path_slope[best_path], 2) + 1);
                    float new_y = path_slope[best_path] * (new_x - path_corner[best_path].x)
                         + path_corner[best_path].y;
                    int new_pos_x = (int)round(new_x);
                    int new_pos_y = (int)round(new_y);
                    if(get_distance(Position_mod(new_pos_x, new_pos_y), Position_mod(x, y)) < 
                        OriginalBuildingAttribute[_type][ORGINAL_RANGE] - 2 && 
                        get_distance(Position_mod(new_pos_x, new_pos_y), Position_mod(x, y)) < best_dis){
                        best_dis = dis;
                        best_pos = Position_mod(x, y);
                    }
                }
            }
        }
    }
    if(best_dis < 401)
        return best_pos;
    else
        return Position_mod(-1, -1);
}

bool build_inst(int _type, int &remain_resource, int &remain_building_point, int my_age){
    Position_mod road_pos = Position_mod(0, 0);
    Position_mod best_pos = Position_mod(0, 0);
    int best_path = 0;
    best_pos = get_nearest_Position_mod(road_pos, _type, 
        OriginalBuildingAttribute[_type][ORGINAL_RANGE], best_path);
    if(best_pos.x > -1){
        Position my_pos = Position(best_pos.x, best_pos.y);
        Position my_road_pos = Position(road_pos.x, road_pos.y);
        if(_type >= Bool && _type <= Hawkin)
            construct(BuildingType(_type), my_pos, my_road_pos);
        else
            construct(BuildingType(_type), my_pos);
        // cout<<((float)(my_age - BIT + 1) * CostCoeff + CostCoeff)<<endl;
        // cout<<OriginalBuildingAttribute[_type-1][ORIGINAL_RESOURCE]<<endl;
        // cout<<_type<<endl;
        // cout<<((float)(my_age - BIT + 1) * CostCoeff + CostCoeff) * 
            // OriginalBuildingAttribute[_type-1][ORIGINAL_RESOURCE]<<endl;
        if(OriginalBuildingAttribute[_type][ORIGINAL_RESOURCE] > 0)
            remain_resource -= ((float)(my_age - BIT + 1) * CostCoeff + CostCoeff) * 
                OriginalBuildingAttribute[_type][ORIGINAL_RESOURCE];
        if(OriginalBuildingAttribute[_type][ORIGINAL_BUILDING_POINT] > 0)
            remain_building_point -= ((float)(my_age - BIT + 1) * CostCoeff + CostCoeff) * 
                OriginalBuildingAttribute[_type][ORIGINAL_BUILDING_POINT];
        correct_pos[best_pos.x][best_pos.y] = 0;
        if(_type >= Bool && _type <= Hawkin){
            defense_building[best_path][_type - Bool]++;
        }
        cout<<"Construct "<<BuildingType(_type)<<" @ ("<<best_pos.x<<", "<<best_pos.y<<"); set produce pos @ ("
            <<road_pos.x<<", "<<road_pos.y<<") remain_resource: "<<remain_resource<<" remain_building_point: "
            <<remain_building_point<<endl;
        return true;
    } else {
        cout<<"No where to build "<<BuildingType(_type)<<"!"<<endl;
        return false;
    }
}

int reward_func(){
    return 0;
}

void f_player(){
    cout<<"Start! I'm player "<<(int)flag<<endl;
    cout<<"Building num: "<<state->building[(int)flag].size()<<endl;
    cout<<"Soldier num: "<<state->soldier[(int)flag].size()<<endl;
    int remain_resource = state->resource[(int)flag].resource;
    int remain_building_point = state->resource[(int)flag].building_point;
    int my_age = state->age[(int)flag];
    int inst_num = 0;
    cout<<"remain resource: "<<remain_resource<<endl;
    cout<<"remain building point: "<<remain_building_point<<endl;
    cout<<"Age: "<<my_age<<endl;
    if(path.size() == 0){
        get_path();
        for(int i = 0; i < path_slope.size(); i++){
            cout<<"path["<<i<<"]: "<<path_slope[i]<<" / ("<<path_corner[i].x
                <<", "<<path_corner[i].y<<")"<<endl;
        }
    }
    path_counter.clear();
    for(int i = 0; i < path.size(); i++){
        vector<int> tmp;
        for(int j = 0; j < 8; j++){
            tmp.push_back(0);
        }
        path_counter.push_back(tmp);
    }
    count_path();
    // cout<<"path counter: "<<path_counter.size()<<endl;
    // for(int i = 0; i < path_counter.size(); i++){
    //     for(int j = 0; j < 8; j++){
    //         cout<<path_counter[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    get_path_reward();
    // cout<<"reward: "<<endl;
    // for(int i = 0; i < path.size(); i++){
    //     for(int j = 0; j < 8; j++){
    //         cout<<reward[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    for(int x = 0; x < 200; x++)
        for(int y = 0; y < 200; y++)
            correct_pos[x][y] = -1;
    get_correct_pos();
    if(my_age < AI){
        if(remain_resource > 
            (my_age - BIT) * AgeCostPerLevel + AgeCostBase){
            updateAge();
            inst_num++;
            remain_resource -= (state->age[(int)flag] - BIT) * AgeCostPerLevel + AgeCostBase;
            cout<<"Update age: from "<<state->age[(int)flag]<<" to "<<state->age[(int)flag]+1<<endl;
        }
    }
    float max_reward = -1.0;
    int todo_defence_building = 0;
    for(int path_i = 0; path_i < path.size(); path_i++){
        int tech_level_def[6] = {1, 2, 3, 4, 6, 8};
        for(int defence = 0; defence < tech_level_def[my_age]; defence++){
            if(reward[path_i][defence] > max_reward && reward[path_i][defence] > 3.0){
                max_reward = reward[path_i][defence];
                todo_defence_building = defence;
            }
        }
    }
    if(inst_num >= 50){
        return;
    }
    build_inst((BuildingType)(Bool + todo_defence_building), remain_resource, remain_building_point, my_age);
    inst_num++;
    while(remain_resource > ((my_age - BIT + 1) * CostCoeff + CostCoeff) * 
        OriginalBuildingAttribute[Programmer][ORIGINAL_RESOURCE] && 
        state->building[(int)flag].size() <= 0.7 * (BuildingRestrictBase + my_age * BuildingRestrictPerLevel) &&
        Programmer_num <= 0.5 * (BuildingRestrictBase + my_age * BuildingRestrictPerLevel)){
        if(inst_num >= 50)
            break;
        if(!build_inst(Programmer, remain_resource, remain_building_point, my_age))
            break;
        inst_num++;
        Programmer_num++;
    }
    int tech_level_att[6] = {0, 2, 3, 3, 4, 7};
    while(remain_resource > ((my_age - BIT + 1) * CostCoeff + CostCoeff) * 
        OriginalBuildingAttribute[Shannon + tech_level_att[my_age]][ORIGINAL_RESOURCE] && 
        remain_building_point > ((my_age - BIT + 1) * CostCoeff + CostCoeff) *
        OriginalBuildingAttribute[Shannon + tech_level_att[my_age]][ORIGINAL_BUILDING_POINT]){
        if(inst_num >= 50)
            break;
        if(!build_inst(Shannon + tech_level_att[my_age], remain_resource, remain_building_point, my_age))
            break;
        inst_num++;
    }
    
    return;
}

void player0(){
    f_player();
}

void player1(){
    f_player();
}