#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import json
import time
import os
import copy

from unit import *

random.seed(time.time())
print_info = 0

class GameMain:
    save_num = 0
    _map_size = 200
    _map = []
    for i in range(_map_size):
        _map.append([0 for j in range(_map_size)])
    turn_num = 0
    winner = 2
    total_id = 0
    description = ''

    units = [{} for _ in range(2)]

    main_base = [None,None]

    buildings = [{
        'produce': [],
        'defence': [],
        'resource': []
    } for _ in range(2)]

    status = [{
        'money': 1000,
        'tech': 0,
        'building': 60,
    } for _ in range(2)]
    
    accumulation = [{
        'money': 0,
        'tech': 0,
        'bd_cons': 1,
        'bd_up': 0,
        'bd_des': 0,
        'sd_pro': 0,
        'sd_kill': 0,
        'base_remain_hp': 0
    } for _ in range(2)]

    # 通信模块将收到的指令写入，各阶段函数从中读取指令，指令格式同api_player.h
    raw_instruments = [{
        'construct': [],  # (BuildingType,(BuildingPos.x,BuildingPos.y),(SoldierPos.x,SoldierPos.y))
        'maintain': [],  # id
        'upgrade': [],  # id
        'sell': [],  # id
        'update_age': False,
    } for _ in range(2)]

    # 各阶段函数处理过raw_instruments后将有效的指令写入，最后将其中的指令写入回放文件
    instruments = [{
        'attack': [],
        'move': [],
        'construct': [],
        'maintain': [],
        'upgrade': [],
        'sell': [],
        'update_age': [],
        'produce':[],
        'resource': False
    } for _ in range(2)]

    def init_map_random(self):
        import random
        _map = self._map
        _map_size = self._map_size

        # 生成基地，位置定在0,0和199,199处
        self.main_base[0] = Building(BuildingType.Base, Position(0, 0), 0, self.total_id,
                                     False,0,Position(0,0))
        self.total_id += 1
        self.main_base[1] = Building(BuildingType.Base, Position(199, 199), 1, self.total_id,
                                     False, 0, Position(199,199))
        self.total_id += 1
        for i in range(7):
            for j in range(7):
                _map[i][j] = 2
        for i in range(_map_size - 7, _map_size):
            for j in range(_map_size - 7, _map_size):
                _map[i][j] = 2

        # 生成中路
        i = 7
        j = 7
        _map[i][j] = 1
        while True:
            if i < _map_size / 2 - 1 and j < _map_size / 2 - 1:
                if random.randint(0, 1) == 0:
                    i += 1
                else:
                    j += 1
            elif i == _map_size / 2 - 1 and j < _map_size / 2 - 1:
                j += 1
            elif i < _map_size / 2 - 1 and j == _map_size / 2 - 1:
                i += 1
            else:
                break
            _map[i][j] = 1
        for i in range(_map_size):
            for j in range(_map_size):
                if _map[_map_size - i - 1][_map_size - j - 1] == 1:
                    _map[i][j] = 1
        _map[int(_map_size / 2) - 1][int(_map_size / 2)] = 1  # 为了让中路连续，把最中心四格都定成路，可改

        # 生成下路
        n = random.randint(1, 3)  # 随机生成3,5或7条路
        for a in range(n):
            i = 7
            x = 5  # 起点从5,3,1顺序选择
            while _map[i][x] == 1 and x >= 1:
                x -= 2
            if x <= 0:
                break
            j = x
            _map[i][j] = 3  # 用3标志暂定路线，最后处理
            while 1:
                if i + j < 200:  # 上下两部分和不同的道路使用两种不同的概率，使道路相对更分散
                    if i < _map_size - x - 1 and j < _map_size - 8:
                        if random.uniform(0, 1) >= x / 12:
                            i += 1
                            if _map[i][j - 1] != 1 and _map[i][j + 1] != 1 and _map[i + 1][j] != 1:
                                # 检查即将延伸的方向有没有其它路，避免交叉
                                pass
                            else:
                                i -= 1
                                j += 1
                                if _map[i - 1][j] != 1 and _map[i + 1][j] != 1 and _map[i][j + 1] != 1:
                                    pass
                                else:
                                    break
                        else:
                            j += 1
                            if _map[i - 1][j] != 1 and _map[i + 1][j] != 1 and _map[i][j + 1] != 1:
                                pass
                            else:
                                j -= 1
                                i += 1
                                if _map[i][j - 1] != 1 and _map[i][j + 1] != 1 and _map[i + 1][j] != 1:
                                    pass
                                else:
                                    break
                    _map[i][j] = 3
                else:
                    if i < _map_size - x - 1 and j < _map_size - 8:
                        if random.uniform(0, 1) < x / 12:
                            i += 1
                            if _map[i][j - 1] != 1 and _map[i][j + 1] != 1 and _map[i + 1][j] != 1:
                                # 检查即将延伸的方向有没有其它路，避免交叉
                                pass
                            else:
                                i -= 1
                                j += 1
                                if _map[i - 1][j] != 1 and _map[i + 1][j] != 1 and _map[i][j + 1] != 1:
                                    pass
                                else:
                                    break
                        else:
                            j += 1
                            if _map[i - 1][j] != 1 and _map[i + 1][j] != 1 and _map[i][j + 1] != 1:
                                pass
                            else:
                                j -= 1
                                i += 1
                                if _map[i][j - 1] != 1 and _map[i][j + 1] != 1 and _map[i + 1][j] != 1:
                                    pass
                                else:
                                    break
                    elif i == _map_size - x - 1 and j < _map_size - 8:
                        j += 1
                        if _map[i - 1][j + 1] != 1 and _map[i][j + 1] != 1:
                            pass
                        else:
                            break
                    elif i < _map_size - x - 1 and j == _map_size - 8:
                        i += 1
                        if _map[i - 1][j + 1] != 1 and _map[i][j + 1] != 1:
                            pass
                        else:
                            break
                    else:
                        break
                    _map[i][j] = 3
            if j == _map_size - 8 <= i < _map_size - 1:  # 路最后延伸至另一个基地
                for i in range(_map_size):
                    for j in range(_map_size):
                        if _map[i][j] == 3:
                            _map[i][j] = 1
            else:
                for i in range(_map_size):
                    for j in range(_map_size):
                        if _map[i][j] == 3:
                            _map[i][j] = 0

        # 利用中心对称生成上路
        for i in range(_map_size):
            for j in range(_map_size):
                if _map[_map_size - i - 1][_map_size - j - 1] == 1:
                    _map[i][j] = 1

    def init_map_from_bitmap(self, path):
        #from PIL import Image

        _map_size = self._map_size
        _map = self._map

        img = Image.open(path)
        size = (_map_size, _map_size)
        img = img.resize(size, Image.ANTIALIAS)  # 放缩大小，直接用一个像素对应地图上的一个点

        # 以下二值化代码来自搜索引擎……包括去噪过程
        img = img.convert("RGBA")
        pixdata = img.load()
        for y in range(img.size[1]):
            for x in range(img.size[0]):
                if pixdata[x, y][0] < 90:
                    pixdata[x, y] = (0, 0, 0, 255)
        for y in range(img.size[1]):
            for x in range(img.size[0]):
                if pixdata[x, y][1] < 136:
                    pixdata[x, y] = (0, 0, 0, 255)
        for y in range(img.size[1]):
            for x in range(img.size[0]):
                if pixdata[x, y][2] > 0:
                    pixdata[x, y] = (255, 255, 255, 255)

        # 将二值化后的图片读入_map
        for i in range(_map_size):
            for j in range(_map_size):
                if pixdata[j, i] == (0, 0, 0, 255):
                    _map[i][j] = 1

        # 个人觉得路应该是比非路少的……所以如果1多就反一下，避免底色比道路颜色深的问题
        n = 0
        for i in range(_map_size):
            for j in range(_map_size):
                if _map[i][j] == 1:
                    n += 1
        if n > _map_size * _map_size / 2:
            for i in range(_map_size):
                for j in range(_map_size):
                    if _map[i][j] == 1:
                        _map[i][j] = 0
                    else:
                        _map[i][j] = 1

        # 判断基地，个人想到的一种非常麻烦的判断方法是判断四个角的7*7，全1或者全0判为基地
        x = _map[0][0]
        flag = 0
        for i in range(7):  # 7*7中是不是全是1或0
            for j in range(7):
                if _map[i][j] == x:
                    pass
                else:
                    flag = 1
                    break
        if flag:
            pass
        else:
            for i in range(8):  # 周围一圈有没有1，即路，有路则为基地
                if _map[i][7] == 1:
                    flag = 1
                    break
            for j in range(7):
                if _map[7][j] == 1:
                    flag = 1
                    break
        if flag:  # 如果判为基地
            for i in range(7):
                for j in range(7):
                    _map[i][j] = 2

        x = _map[_map_size - 1][0]
        flag = 0
        for i in range(_map_size - 7, _map_size):
            for j in range(7):
                if _map[i][j] == x:
                    pass
                else:
                    flag = 1
                    break
        if flag:
            pass
        else:
            for i in range(_map_size - 8, _map_size):
                if _map[i][7]:
                    flag = 1
                    break
            for j in range(7):
                if _map[_map_size - 8][j]:
                    flag = 1
                    break
        if flag:  # 如果判为基地
            for i in range(_map_size - 7, _map_size):
                for j in range(7):
                    _map[i][j] = 2

        x = _map[0][_map_size - 1]
        flag = 0
        for i in range(7):
            for j in range(_map_size - 7, _map_size):
                if _map[i][j] == x:
                    pass
                else:
                    flag = 1
                    break
        if flag:
            pass
        else:
            for i in range(8):
                if _map[i][7]:
                    flag = 1
                    break
            for j in range(_map_size - 7, _map_size):
                if _map[7][j]:
                    flag = 1
                    break
        if flag:  # 如果判为基地
            for i in range(7):
                for j in range(_map_size - 7, _map_size):
                    _map[i][j] = 2

        x = _map[_map_size - 1][_map_size - 1]
        flag = 0
        for i in range(_map_size - 7, _map_size):
            for j in range(_map_size - 7, _map_size):
                if _map[i][j] == x:
                    pass
                else:
                    flag = 1
                    break
        if flag:
            pass
        else:
            for i in range(_map_size - 7, _map_size):
                if _map[i][_map_size - 8]:
                    flag = 1
                    break
            for j in range(_map_size - 7, _map_size):
                if _map[_map_size - 8][j]:
                    flag = 1
                    break
        if flag:  # 如果判为基地
            for i in range(_map_size - 7, _map_size):
                for j in range(_map_size - 7, _map_size):
                    _map[i][j] = 2

    def __init__(self):
        self.init_map_random()

    def judge_winnner(self):
       # print("judge，回合：",self.turn_num);
        if self.turn_num >= Inf:
            self.draw_judge()
        elif self.main_base[0].HP <= 0 and self.main_base[1].HP > 0:
            self.winner = 1
        elif self.main_base[1].HP <= 0 and self.main_base[0].HP > 0:
            self.winner = 0
        elif self.main_base[0].HP <= 0 and self.main_base[1].HP <= 0:
            self.winner = 3
        else:
            self.winner = 2

    def check_legal(self):


        """Remove the repeated instruments, or instruments on the wrong units"""
        from functools import reduce
        for current_flag in range(2):
            for instrument_type, instrument_list in self.raw_instruments[current_flag].items():
                if instrument_type == 'update_age':
                    continue
                # 去重，并保持原来指令次序
                del_repeat = lambda x, y: x if y in x else x + [y]
                new_instrument_list = reduce(del_repeat, [[], ] + instrument_list)
                if instrument_type == 'construct':
                    instrument_num = -1
                    while instrument_num < len(new_instrument_list)-1:
                        instrument_num += 1
                        instrument = new_instrument_list[instrument_num]
                        building_type = instrument[0]

                        new_construct_pos = Position(instrument[1][0],instrument[1][1])


                        if building_type <1 or building_type >17:
                            new_instrument_list.remove(instrument)
                            instrument_num -= 1
                            continue
                        # 生产建筑必须指定正确的生产位置
                        if building_type >0 and building_type <9:
                            # print("*******", instrument[2][0])
                            if len(instrument) <2:
                                new_instrument_list.remove(instrument)
                                instrument_num -=1
                                if print_info:
                                    print("生产建筑没有指定生产位置")
                                continue
                            if abs(instrument[2][0] - instrument[1][0]) + \
                                abs (instrument[2][1] - instrument[1][1]) > \
                                OriginalBuildingAttribute[BuildingType(instrument[0])][BuildingAttribute.ORIGINAL_RANGE]:
                                new_instrument_list.remove(instrument)
                                instrument_num -= 1
                                if print_info:
                                    print("生产建筑指定的生产位置超出范围")
                                continue
                            new_produce_pos = Position(instrument[2][0],instrument[2][1])
                        # 判断建造时代是否符合要求
                        if (OriginalBuildingAttribute[BuildingType(building_type)][BuildingAttribute.AGE].value >
                                self.status[current_flag]['tech']):
                            new_instrument_list.remove(instrument)
                            instrument_num -= 1
                            if print_info:
                                print("建造时代不符合要求")
                            continue
                        # 判断建造位置是否符合要求
                        if new_construct_pos.x < 0 or new_construct_pos.y < 0 or \
                            new_construct_pos.x > 199 or new_construct_pos.y >199:
                            new_instrument_list.remove(instrument)
                            instrument_num -= 1
                            if print_info:
                                print("建造位置超出地图")
                            continue
                        if (self._map[new_construct_pos.x][new_construct_pos.y] == 1 or
                                    self._map[new_construct_pos.x][new_construct_pos.y] == 2):
                            new_instrument_list.remove(instrument)
                            instrument_num -= 1
                            if print_info:
                                print("建造位置不在空地上")
                            continue


                        # 判断生产位置是否符合要求
                        if (OriginalBuildingAttribute[building_type][BuildingAttribute.BUILDING_TYPE] ==
                                UnitType.PRODUCTION_BUILDING):
                            if (abs(new_produce_pos.x - new_construct_pos.x) +
                                    abs(new_produce_pos.y - new_construct_pos.y) >
                                    OriginalBuildingAttribute[building_type][BuildingAttribute.ORIGINAL_RANGE]):
                                new_instrument_list.remove(instrument)
                                instrument_num -= 1
                                if print_info:
                                    print("生产建筑指定的生产位置超出范围")
                                continue
                            elif self._map[new_produce_pos.x][new_produce_pos.y] != 1:
                                new_instrument_list.remove(instrument)
                                instrument_num -= 1
                                if print_info:
                                    print("生产建筑指定的生产位置不在路上")
                                continue


                else:
                    # 去除指令对象id越界或不符合要求的情况
                    instrument_num = -1
                    while instrument_num < len(new_instrument_list)-1:
                        instrument_num += 1
                        instrument = new_instrument_list[instrument_num]
                        if instrument > self.total_id or instrument < 0:
                            new_instrument_list.remove(instrument)
                            instrument_num -= 1
                            if print_info:
                                print("指令id超过最大id")
                            continue
                        # 去除指令对象不是building的情况
                        is_building = False
                        count = 0
                        for building_list in self.buildings[current_flag].values():
                            if not building_list:
                                count += 1
                            for building in building_list:
                                if building.Unit_ID == instrument:
                                    is_building = True
                                    break
                            if count == 3:
                                is_building = True
                            if is_building:
                                break
                        if not is_building:
                            new_instrument_list.remove(instrument)
                            instrument_num -= 1
                            if print_info:
                                print("建筑id中未找到目标id或目标在该回合被摧毁")
                            continue

                            # 资源不足，建筑和时代已经到达最高级的情况已经在操作函数中处理
                            # sell指令去重之后不会出现卖空的情况
                            # 其他未考虑到的情况可以继续进行补充

                self.raw_instruments[current_flag][instrument_type] = new_instrument_list

    def attack_phase(self):
        """Defence towers attack the units and units attack towers"""

        for flag in range(2):

            # 建筑对兵种攻击
            for building in self.buildings[flag]['defence']:
                tech_factor = 0.5 * (building.level + 2)
                # Bool Attack , 1/2 概率无效，攻击最近单位
                if building.BuildingType == BuildingType.Bool:
                    can_attack = random.randint(0, 1)
                    if not can_attack:
                        continue
                    else:
                        pre_dist = OriginalBuildingAttribute[BuildingType.Bool][BuildingAttribute.ORIGINAL_RANGE] + 1
                        target = None
                        for enemy_id, enemy in self.units[1 - flag].items():
                            now_dist = abs(enemy.Position.x - building.Position.x) \
                                       + abs(enemy.Position.y - building.Position.y)
                            if now_dist < pre_dist and enemy.HP > 0 and \
                                (enemy.Soldier_Name == SoldierName.BIT_STREAM or
                                enemy.Soldier_Name == SoldierName.PACKET or
                                enemy.Soldier_Name == SoldierName.TURNING_MACHINE):
                                target = enemy
                                target_id = enemy_id
                                pre_dist = now_dist
                        if target is not None:
                            target.HP = (target.HP - (OriginalBuildingAttribute[BuildingType.Bool]
                                                     [BuildingAttribute.ORIGINAL_ATTACK] * tech_factor))
                            self.instruments[flag]['attack'].append((building.Unit_ID, target_id))

                # Ohm Attack , 同时击中V和C伤害加3倍（即乘4倍），攻击最近单位
                if building.BuildingType == BuildingType.Ohm:
                    building.CD_left = building.CD_left - 1
                    if building.CD_left <= 0:
                        building.CD_left = OriginalBuildingAttribute[BuildingType.Ohm][BuildingAttribute.CD]
                        pre_dist = OriginalBuildingAttribute[BuildingType.Ohm][BuildingAttribute.ORIGINAL_RANGE] + 1
                        target = None
                        for enemy_id, enemy in self.units[1 - flag].items():
                            now_dist = (abs(enemy.Position.x - building.Position.x) +
                                        abs(enemy.Position.y - building.Position.y))
                            if now_dist < pre_dist and enemy.HP > 0 and \
                                (enemy.Soldier_Name == SoldierName.VOLTAGE_SOURCE or
                                 enemy.Soldier_Name == SoldierName.CURRENT_SOURCE or
                                 enemy.Soldier_Name == SoldierName.ENIAC or
                                 enemy.Soldier_Name == SoldierName.OPTICAL_FIBER or
                                 enemy.Soldier_Name == SoldierName.ULTRON):
                                target = enemy
                                target_id = enemy_id
                                pre_dist = now_dist
                        if target is not None:
                            target_x = target.Position.x
                            target_y = target.Position.y
                            hit_v = False
                            hit_c = False
                            for enemy_id, enemy in self.units[1 - flag].items():
                                if (abs(enemy.Position.x - target_x) + abs(enemy.Position.y - target_y) <
                                        OriginalBuildingAttribute[BuildingType.Ohm][BuildingAttribute.AOE]
                                    and (enemy.Soldier_Name == SoldierName.VOLTAGE_SOURCE or
                                         enemy.Soldier_Name == SoldierName.CURRENT_SOURCE or
                                         enemy.Soldier_Name == SoldierName.ENIAC or
                                         enemy.Soldier_Name == SoldierName.OPTICAL_FIBER or
                                         enemy.Soldier_Name == SoldierName.ULTRON)):
                                    enemy.HP = (enemy.HP - (OriginalBuildingAttribute[BuildingType.Ohm]
                                                           [BuildingAttribute.ORIGINAL_ATTACK] * tech_factor))
                                    if enemy.Soldier_Name == SoldierName.VOLTAGE_SOURCE:
                                        hit_v = True
                                    if enemy.Soldier_Name == SoldierName.CURRENT_SOURCE:
                                        hit_c = True
                            if hit_v and hit_c:
                                for enemy_id, enemy in self.units[1 - flag].items():
                                    if (abs(enemy.Position.x - target_x) + abs(enemy.Position.y - target_y)
                                            < OriginalBuildingAttribute[BuildingType.Ohm][BuildingAttribute.AOE]
                                        and (enemy.Soldier_Name == SoldierName.VOLTAGE_SOURCE or
                                             enemy.Soldier_Name == SoldierName.CURRENT_SOURCE or
                                             enemy.Soldier_Name == SoldierName.ENIAC or
                                             enemy.Soldier_Name == SoldierName.OPTICAL_FIBER or
                                             enemy.Soldier_Name == SoldierName.ULTRON)):
                                        enemy.HP = (enemy.HP - 3 * (OriginalBuildingAttribute[BuildingType.Ohm][
                                                                BuildingAttribute.ORIGINAL_ATTACK] * tech_factor))
                            self.instruments[flag]['attack'].append((building.Unit_ID, target_id))
                # Mole Attack，连续攻击同一个目标每次翻倍
                if building.BuildingType == BuildingType.Mole:
                    pre_dist = OriginalBuildingAttribute[BuildingType.Bool][BuildingAttribute.ORIGINAL_RANGE] + 1
                    target = None
                    target_id = -1
                    find_last = False
                    # 查找上一个攻击目标是否还在攻击范围内
                    for enemy_id, enemy in self.units[1 - flag].items():
                        if (enemy.HP > 0 and enemy_id == building.last_target_id and
                                        abs(enemy.Position.x - building.Position.x) +
                                        abs(enemy.Position.y - building.Position.y) < pre_dist):
                            target = enemy
                            target_id = building.last_target_id
                            building.mult_factor *= 2
                            find_last = True
                            break
                    if not find_last:
                        building.mult_factor = 1
                        for enemy_id, enemy in self.units[1 - flag].items():
                            now_dist = abs(enemy.Position.x - building.Position.x) \
                                       + abs(enemy.Position.y - building.Position.y)
                            if (now_dist < pre_dist and enemy.HP > 0
                                and (enemy.Soldier_Name == SoldierName.VOLTAGE_SOURCE or
                                     enemy.Soldier_Name == SoldierName.CURRENT_SOURCE or
                                     enemy.Soldier_Name == SoldierName.ENIAC or
                                     enemy.Soldier_Name == SoldierName.OPTICAL_FIBER or
                                     enemy.Soldier_Name == SoldierName.ULTRON)):
                                target = enemy
                                target_id = enemy_id
                                pre_dist = now_dist
                    if target is not None:
                        building.last_target_id = target_id
                        target.HP = (target.HP - (OriginalBuildingAttribute[BuildingType.Mole][
                                        BuildingAttribute.ORIGINAL_ATTACK] * tech_factor * building.mult_factor))
                        self.instruments[flag]['attack'].append((building.Unit_ID, target_id))

                # Monte_Carlo Attack,0-2之间随机数
                if building.BuildingType == BuildingType.Monte_Carlo:
                    building.CD_left = building.CD_left - 1
                    if building.CD_left <= 0:
                        building.CD_left = OriginalBuildingAttribute[BuildingType.Monte_Carlo][BuildingAttribute.CD]
                        pre_dist = OriginalBuildingAttribute[BuildingType.Monte_Carlo][
                                       BuildingAttribute.ORIGINAL_RANGE] + 1
                        target = None
                        for enemy_id, enemy in self.units[1 - flag].items():
                            now_dist = abs(enemy.Position.x - building.Position.x) \
                                       + abs(enemy.Position.y - building.Position.y)
                            if (now_dist < pre_dist and enemy.HP> 0
                                and (enemy.Soldier_Name == SoldierName.VOLTAGE_SOURCE or
                                     enemy.Soldier_Name == SoldierName.CURRENT_SOURCE or
                                     enemy.Soldier_Name == SoldierName.ENIAC or
                                     enemy.Soldier_Name == SoldierName.OPTICAL_FIBER or
                                     enemy.Soldier_Name == SoldierName.ULTRON)):
                                target = enemy
                                target_id = enemy_id
                                pre_dist = now_dist
                        if target is not None:
                            rand_factor = random.uniform(0, 2)
                            target.HP = (target.HP - (OriginalBuildingAttribute[BuildingType.Bool]
                                                     [BuildingAttribute.ORIGINAL_ATTACK] * tech_factor * rand_factor))
                            self.instruments[flag]['attack'].append((building.Unit_ID, target_id))

                # Larry_Roberts Attack,优先数据包且对其伤害乘3
                if building.BuildingType == BuildingType.Larry_Roberts:
                    pre_dist = OriginalBuildingAttribute[BuildingType.Larry_Roberts][BuildingAttribute.ORIGINAL_RANGE] \
                               + 1
                    target = None
                    hit_packet = False
                    for enemy_id, enemy in self.units[1 - flag].items():
                        if enemy.Soldier_Name != SoldierName.PACKET:
                            continue
                        now_dist = abs(enemy.Position.x - building.Position.x) \
                                   + abs(enemy.Position.y - building.Position.y)
                        if now_dist < pre_dist and enemy.HP > 0:
                            target = enemy
                            target_id = enemy_id
                            pre_dist = now_dist
                            hit_packet = True
                    if not hit_packet:
                        for enemy_id, enemy in self.units[1 - flag].items():
                            now_dist = abs(enemy.Position.x - building.Position.x) \
                                       + abs(enemy.Position.y - building.Position.y)
                            if now_dist < pre_dist and enemy.HP > 0:
                                target = enemy
                                target_id = enemy_id
                                pre_dist = now_dist
                    if target is not None:
                        target_x = target.Position.x
                        target_y = target.Position.y
                        for enemy_id, enemy in self.units[1 - flag].items():
                            if (abs(enemy.Position.x - target_x) + abs(enemy.Position.y - target_y) <
                                    OriginalBuildingAttribute[BuildingType.Larry_Roberts][BuildingAttribute.AOE]):
                                if enemy.Soldier_Name == SoldierName.PACKET:
                                    mult_factor = 3
                                else:
                                    mult_factor = 1
                                enemy.HP = (enemy.HP - (OriginalBuildingAttribute[BuildingType.Larry_Roberts]
                                                       [BuildingAttribute.ORIGINAL_ATTACK] * tech_factor * mult_factor))
                        self.instruments[flag]['attack'].append((building.Unit_ID, target_id))

                # Robert_Kahn Attack,最大生命值10% * tech_factor
                if building.BuildingType == BuildingType.Robert_Kahn:
                    pre_dist = OriginalBuildingAttribute[BuildingType.Robert_Kahn][BuildingAttribute.ORIGINAL_RANGE] + 1
                    target = None
                    for enemy_id, enemy in self.units[1 - flag].items():
                        now_dist = abs(enemy.Position.x - building.Position.x) \
                                   + abs(enemy.Position.y - building.Position.y)
                        if now_dist < pre_dist and enemy.HP > 0 and \
                                (enemy.Soldier_Name == SoldierName.BIT_STREAM or
                                enemy.Soldier_Name == SoldierName.PACKET or
                                enemy.Soldier_Name == SoldierName.TURNING_MACHINE):
                            target = enemy
                            target_id = enemy_id
                            pre_dist = now_dist
                    if target is not None:
                        persent = 0.1 * tech_factor
                        enemy_tech_factor = 0.5 * (target.level + 2)
                        fixed_hp = OriginalBuildingAttribute[BuildingType.Robert_Kahn][BuildingAttribute.ORIGINAL_ATTACK] * \
                                tech_factor
                        target.HP = (target.HP - fixed_hp - OriginalSoldierAttribute[target.Soldier_Name][
                            SoldierAttr.SOLIDER_ORIGINAL_HP] * enemy_tech_factor * persent)
                        self.instruments[flag]['attack'].append((building.Unit_ID, target_id))

                # Hawkin Attack,秒杀三格
                if building.BuildingType == BuildingType.Hawkin:
                    building.CD_left = building.CD_left - 1
                    if building.CD_left <= 0:

                        building.CD_left = OriginalBuildingAttribute[BuildingType.Hawkin][BuildingAttribute.CD] \
                                            - building.level
                        pre_dist = OriginalBuildingAttribute[BuildingType.Hawkin][BuildingAttribute.ORIGINAL_RANGE] + 1
                        target = None
                        for enemy_id, enemy in self.units[1 - flag].items():
                            now_dist = abs(enemy.Position.x - building.Position.x) \
                                       + abs(enemy.Position.y - building.Position.y)
                            if now_dist < pre_dist and enemy.HP > 0:
                                target = enemy
                                target_id = enemy_id
                                pre_dist = now_dist
                        if target is not None:
                            target_x = target.Position.x
                            target_y = target.Position.y
                            for enemy_id, enemy in self.units[1 - flag].items():
                                if (abs(enemy.Position.x - target_x) + abs(enemy.Position.y - target_y) <
                                        OriginalBuildingAttribute[BuildingType.Hawkin][BuildingAttribute.AOE]):
                                    enemy.HP = -1
                            self.instruments[flag]['attack'].append((building.Unit_ID, target_id))

                self.clean_up_phase()
                
        for flag in range(2):
            # 兵种对建筑的攻击
            for unit_id, unit in self.units[flag].items():
                tech_factor = 0.5 * ( unit.level + 2)
                action_mode = OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.ACTION_MODE]
                pre_dist = OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.ATTACK_RANGE] + 1
                if unit.Soldier_Name == SoldierName.TURNING_MACHINE or unit.Soldier_Name == SoldierName.ULTRON:
                    can_attack = True
                    for enemy_building in self.buildings[1 - flag]["defence"]:
                        if enemy_building.BuildingType == BuildingType.Musk and \
                            abs(unit.Position.x - enemy_building.Position.x) \
                            + abs(unit.Position.y - enemy_building.Position.y) \
                            < OriginalBuildingAttribute[BuildingType.Musk][BuildingAttribute.ORIGINAL_RANGE]:
                            can_attack = False
                            break
                    if not can_attack:
                        continue
                # 推塔式与抗线式兵种的攻击
                if action_mode == ActionMode.BUILDING_ATTACK or action_mode == ActionMode.MOVING_ATTACK:
                    target = None
                    for building_list in self.buildings[1 - flag].values():
                        for enemy_building in building_list:
                            now_dist = (abs(enemy_building.Position.x - unit.Position.x) +
                                        abs(enemy_building.Position.y - unit.Position.y))
                            if now_dist < pre_dist and enemy_building.HP > 0:
                                target = enemy_building
                                pre_dist = now_dist
                    if target is None:
                        # 如果没有找到范围内的建筑，就查找基地是否在其范围内
                        # 假设flag = 0 基地在(0,0)，flag = 1 基地在(199,199)
                        if not flag:
                            now_dist_x = 0 if unit.Position.x >= 193 else 193 - unit.Position.x
                            now_dist_y = 0 if unit.Position.y >= 193 else 193 - unit.Position.y
                        else:
                            now_dist_x = 0 if unit.Position.x <= 6 else unit.Position.x - 6
                            now_dist_y = 0 if unit.Position.y <= 6 else unit.Position.y - 6
                        now_dist = now_dist_x + now_dist_y
                        if now_dist < pre_dist and self.main_base[1 - flag].HP > 0:
                            target = self.main_base[1 - flag]
                    if target is not None:
                        target.HP = (target.HP - OriginalSoldierAttribute[unit.Soldier_Name][
                                          SoldierAttr.SOLIDER_ORIGINAL_ATTACK] * tech_factor)
                        self.instruments[flag]['attack'].append((unit_id, target.Unit_ID))

                # 冲锋式兵种的攻击
                else:
                    if not flag:
                        now_dist_x = 0 if unit.Position.x >= 193 else 193 - unit.Position.x
                        now_dist_y = 0 if unit.Position.y >= 193 else 193 - unit.Position.y
                    else:
                        now_dist_x = 0 if unit.Position.x <= 6 else unit.Position.x - 6
                        now_dist_y = 0 if unit.Position.y <= 6 else unit.Position.y - 6
                    now_dist = now_dist_x + now_dist_y
                    if now_dist < pre_dist and self.main_base[1 - flag].HP > 0:
                        self.main_base[1 - flag].HP -= (OriginalSoldierAttribute[unit.Soldier_Name][
                                                            SoldierAttr.SOLIDER_ORIGINAL_ATTACK] * tech_factor)
                        unit.HP = -1
                        self.instruments[flag]['attack'].append((unit_id, self.main_base[1 - flag].Unit_ID))

    def clean_up_phase(self):
        """Remove the destroyed units and towers"""
        for flag in range(2):
            for unit_id in list(self.units[flag].keys()):
                if self.units[flag][unit_id].HP <= 0:
                    self.units[flag].pop(unit_id)
                    self.accumulation[1-flag]['sd_kill'] += 1
            
            for bd_type, bd_list in self.buildings[flag].items():
                k = 0
                while k < len(bd_list):
                    if bd_list[k].HP <= 0:
                        del bd_list[k]
                        self.accumulation[1-flag]['bd_des'] += 1
                    else:
                        k += 1

    def move_phase(self):
        """Move the units according to their behaviour mode"""
        _map = self._map
        for current_flag in range(2):
            # Assume player 0's base is at(0,0) temporarily, which can be changed.
            direction = 1 if current_flag == 0 else -1

            for unit_id, unit in self.units[current_flag].items():
                # Building Musk's skill : AI cannot move in its shot range.
                if unit.Soldier_Name == SoldierName.TURNING_MACHINE or unit.Soldier_Name == SoldierName.ULTRON:
                    can_move = True
                    for enemy_building in self.buildings[1 - current_flag]['defence']:
                        if (enemy_building.BuildingType == BuildingType.Musk and
                            abs(enemy_building.Position.x - unit.Position.x) +
                            abs(enemy_building.Position.y - unit.Position.y) <=
                                    OriginalBuildingAttribute[enemy_building.BuildingType][
                                        BuildingAttribute.ORIGINAL_RANGE]):
                            can_move = False
                            break
                    if not can_move:
                        continue

                if (OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.ACTION_MODE] ==
                        ActionMode.BUILDING_ATTACK):
                    enemy_bds = {'produce':list(range(len(self.buildings[1-current_flag]['produce']))),
                                 'defence':list(range(len(self.buildings[1-current_flag]['defence']))),
                                 'resource':list(range(len(self.buildings[1-current_flag]['resource'])))}
                                    
                    
                    for bd_type, bd_list in enemy_bds.items():
                        k=0
                        while k < len(bd_list):
                            enemy_bd = self.buildings[1 - current_flag][bd_type][ bd_list[k] ]
                            if (
                                (abs(enemy_bd.Position.x - unit.Position.x) +
                                 abs(enemy_bd.Position.y - unit.Position.y)) >
                                (OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.ATTACK_RANGE] +
                                 OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.SPEED])
                                ):
                                del bd_list[k]
                            else:
                                k += 1
                            
                    for i in range(OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.SPEED]):
                        # When Soldier is moving, if there are buildings in Soldier's shot range,
                        # stop to attack the building, else continue moving.
                        can_move = True

                        if current_flag:
                            now_dist_x = 0 if unit.Position.x <= 6 else unit.Position.x - 6
                            now_dist_y = 0 if unit.Position.y <= 6 else unit.Position.y - 6
                        else:
                            now_dist_x = 0 if unit.Position.x >= 193 else 193 - unit.Position.x
                            now_dist_y = 0 if unit.Position.y >= 193 else 193 - unit.Position.y
                        now_dist = now_dist_x + now_dist_y
                        if now_dist <= OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.ATTACK_RANGE]:
                            can_move = False
                        if can_move:
                            for building_type, building_array in enemy_bds.items():
                                for enemy_building_No in building_array:
                                    enemy_building = self.buildings[1 - current_flag][building_type][enemy_building_No]
                                    if (abs(enemy_building.Position.x - unit.Position.x) +
                                            abs(enemy_building.Position.y - unit.Position.y) <=
                                            OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.ATTACK_RANGE]):
                                        can_move = False
                                        break
                                if not can_move:
                                    break

                        if can_move:
                            if _map[unit.Position.x + direction][unit.Position.y] == 1:
                                # position need to be changed.
                                unit.Position = Position(unit.Position.x + direction, unit.Position.y)
                            elif _map[unit.Position.x][unit.Position.y + direction] == 1:
                                unit.Position = Position(unit.Position.x, unit.Position.y + direction)
                        else:
                            break
                    self.instruments[current_flag]['move'].append(
                        (unit_id, unit.Position))

                else:
                    for i in range(OriginalSoldierAttribute[unit.Soldier_Name][SoldierAttr.SPEED]):
                        if _map[unit.Position.x + direction][unit.Position.y] == 1:
                            unit.Position = Position(unit.Position.x + direction, unit.Position.y)
                        elif _map[unit.Position.x][unit.Position.y + direction] == 1:
                            unit.Position = Position(unit.Position.x, unit.Position.y + direction)
                    self.instruments[current_flag]['move'].append(
                        (unit_id, unit.Position))

    def building_phase(self):
        """Deal with the instruments about buildings"""

        # Lack the legality judgement temporarily.

        def construct_phase(self):
            
            first_flag = random.randint(0,1)
            
            for current_flag in [first_flag, 1-first_flag]:
                age_increase_factor = 0.5 * (self.status[current_flag]['tech'] + 2)
                max_bd_num = 40 * age_increase_factor
                bd_num = 0

                for building_type,buildings_in_it in self.buildings[current_flag].items():
                    # print(building_type,buildings_in_it)
                    bd_num += len(buildings_in_it)
                    # print(bd_num)

                for construct_instrument in self.raw_instruments[current_flag]['construct']:
                    if bd_num >= max_bd_num:
                        break
                    building_name = construct_instrument[0]
                    building_pos = Position(*construct_instrument[1])
                    money_cost = (
                        OriginalBuildingAttribute[construct_instrument[0]][BuildingAttribute.ORIGINAL_RESOURCE])
                    building_point_cost = (
                        OriginalBuildingAttribute[construct_instrument[0]][BuildingAttribute.ORIGINAL_BUILDING_POINT])
                    if building_name < 9 and building_name >0:
                        produce_pos = Position(*construct_instrument[2])
                    else:
                        produce_pos = None

                    # Ignore the instruments that spend too much.
                    if (self.status[current_flag]['money'] < money_cost or
                                self.status[current_flag]['building'] < building_point_cost):
                        if print_info:
                            print("建造指令资源或建造点不足")
                        continue
                    # print('money')
                    # print(current_flag,self.status[current_flag]['money'],money_cost)
                    # print("buildingpoint")
                    # print(current_flag,self.status[current_flag]['building'],building_point_cost)

                    building_range = 8  # 建造范围暂设为8
                    can_build = False
                    if (abs(building_pos.x - current_flag * (self._map_size - 1)) <= 10 and
                                abs(building_pos.y - current_flag * (self._map_size - 1)) <= 10):
                        can_build = True
                    for building_list in self.buildings[current_flag].values():
                        if not can_build:
                            for building in building_list:
                                if (abs(building.Position.x - building_pos.x) +
                                        abs(building.Position.y - building_pos.y) <=
                                        building_range):
                                    can_build = True
                                    break

                    for building_list in self.buildings[current_flag].values():
                        if can_build:
                            for building in building_list:
                                if (abs(building.Position.x - building_pos.x) +
                                        abs(building.Position.y - building_pos.y) <= 1):
                                    can_build = False
                                    break
                                    
                    for building_list in self.buildings[1 - current_flag].values():
                        if can_build:
                            for building in building_list:
                                if (abs(building.Position.x - building_pos.x) +
                                        abs(building.Position.y - building_pos.y) <= 1):
                                    can_build = False
                                    break
                    if not can_build:
                        if print_info:
                            print("不在建造范围内或与已有建筑邻近或重叠")
                        continue

                    if (OriginalBuildingAttribute[construct_instrument[0]][BuildingAttribute.BUILDING_TYPE] ==
                            UnitType.PRODUCTION_BUILDING):
                        self.buildings[current_flag]['produce'].append(
                            Building(building_name, building_pos, current_flag, self.total_id, False,
                                     0, produce_pos)
                            )

                    elif (OriginalBuildingAttribute[construct_instrument[0]][BuildingAttribute.BUILDING_TYPE] ==

                            UnitType.DEFENSIVE_BUILDING):
                        self.buildings[current_flag]['defence'].append(
                            Building(building_name, building_pos, current_flag, self.total_id, False,
                                     0, produce_pos)
                            )

                    else:
                        self.buildings[current_flag]['resource'].append(
                            Building(building_name, building_pos, current_flag, self.total_id, False,
                                     0, produce_pos)
                            )

                    bd_num += 1
                    self.total_id += 1
                    self.status[current_flag]['money'] -= money_cost
                    self.status[current_flag]['building'] -= building_point_cost
                    self.instruments[current_flag]['construct'].append(construct_instrument)
                    self.accumulation[current_flag]['bd_cons'] += 1
        construct_phase(self)

        def maintain_phase(self):
            for current_flag in range(2):
                for maintain_instrument in self.raw_instruments[current_flag]['maintain']:
                    maintain_base = False
                    for building_type, building_array in self.buildings[current_flag].items():
                        if maintain_base:
                            break
                        for building in building_array:
                            # Change the status if The building is maintaining.
                            if building.Unit_ID == maintain_instrument:
                                if building.BuildingType == BuildingType.Base:
                                    maintain_base = True
                                    break
                                # Change the status of the true building, not its copy.
                                max_HP = (
                                OriginalBuildingAttribute[building.BuildingType][BuildingAttribute.ORIGINAL_HP] *
                                0.5 * (building.level + 2))
                                lost_percent = (max_HP - building.HP) / max_HP  # The ratio of lost HP to max HP.
                                construct_money = (
                                    OriginalBuildingAttribute[building.BuildingType]
                                                            [BuildingAttribute.ORIGINAL_RESOURCE] *
                                                            0.5 * (building.level + 2))
                                if lost_percent < 0.2:
                                    if (self.status[current_flag]['money'] > lost_percent * construct_money):
                                        building.HP = max_HP
                                        self.status[current_flag]['money'] -= lost_percent * construct_money
                                        self.instruments[current_flag]['maintain'].append(building.Unit_ID)
                                    else:
                                        if print_info:
                                            print("修理指令资源不足")
                                    break
                                else:
                                    if (self.status[current_flag]['money'] > 0.2 * construct_money):
                                        building.HP = building.HP + 0.2 * max_HP
                                        self.status[current_flag]['money'] -= 0.2 * construct_money
                                        self.instruments[current_flag]['maintain'].append(building.Unit_ID)
                                    else:
                                        if print_info:
                                            print("修理指令资源不足")
                                    break
        maintain_phase(self)

        def upgrade_phase(self):
            for current_flag in range(2):
                for upgrade_instrument in self.raw_instruments[current_flag]['upgrade']:
                    have_found = False
                    for building_type, building_array in self.buildings[current_flag].items():
                        for building in building_array:
                            if building.Unit_ID == upgrade_instrument:
                                #building_index = building_array.index(element)
                                max_HP = (
                                    OriginalBuildingAttribute[building.BuildingType][BuildingAttribute.ORIGINAL_HP] *
                                    0.5 * (building.level + 2))
                                hp_persent = building.HP / max_HP
                                # The difference of construct money and max HP between old and upgraded towers.
                                upgrade_diff_money = OriginalBuildingAttribute[building.BuildingType][
                                                         BuildingAttribute.ORIGINAL_RESOURCE] * 0.5
                                upgrade_diff_bdpoint = OriginalBuildingAttribute[building.BuildingType][
                                                        BuildingAttribute.ORIGINAL_BUILDING_POINT] * 0.5
                                upgrade_diff_max_HP = OriginalBuildingAttribute[building.BuildingType][
                                                          BuildingAttribute.ORIGINAL_HP] * 0.5

                                if (self.status[current_flag]['money'] > upgrade_diff_money
                                    and self.status[current_flag]['building'] > upgrade_diff_bdpoint
                                    and self.status[current_flag]['tech'] >= building.level + 1):
                                    building.level += 1
                                    building.HP = (max_HP + upgrade_diff_max_HP) * hp_persent
                                    self.status[current_flag]['money'] -= upgrade_diff_money
                                    self.status[current_flag]['building'] -= upgrade_diff_bdpoint
                                    self.instruments[current_flag]['upgrade'].append(upgrade_instrument)
                                    self.accumulation[current_flag]['bd_up'] += 1
                                else:
                                    if print_info:
                                        print("升级建筑指令科技等级或资源不足")
                                have_found = True
                                break
                        if have_found:
                            break
        upgrade_phase(self)

        def sell_phase(self):
            # age_increase_factor = 0.5 * (self.status[current_flag]['tech'] + 2)
            for current_flag in range(2):
                for sell_instrument in self.raw_instruments[current_flag]['sell']:
                    have_found = False  # Signal if the building to be sold has been found.
                    for building_type, building_array in self.buildings[current_flag].items():
                        for building in building_array:
                            if building.Unit_ID == sell_instrument:
                                max_HP = (
                                    OriginalBuildingAttribute[building.BuildingType][BuildingAttribute.ORIGINAL_HP] *
                                    0.5 * (building.level + 2))
                                return_percent = 0.5 * building.HP / max_HP
                                construct_money = (OriginalBuildingAttribute[building.BuildingType][
                                                       BuildingAttribute.ORIGINAL_RESOURCE] *
                                                   0.5 * (building.level + 2))

                                self.status[current_flag]['money'] += return_percent * construct_money
                                self.buildings[current_flag][building_type].remove(building)
                                have_found = True
                                break
                        if have_found:
                            break
                    self.instruments[current_flag]['sell'].append(sell_instrument)
        sell_phase(self)

    def produce_phase(self):
        """Unit production by producing building"""
        for current_flag in range(2):
            for building in self.buildings[current_flag]['produce']:
                age_increase_factor = 0.5 * (building.level + 2)
                if building.CD_left <= 0:
                    solider_name = OriginalBuildingAttribute[building.BuildingType][BuildingAttribute.TARGET]
                    solider_hp = OriginalSoldierAttribute[solider_name][SoldierAttr.SOLIDER_ORIGINAL_HP] * \
                                 age_increase_factor
                    solider_pos = building.ProducePos
                    solider_flag = current_flag
                    solider_id = self.total_id
                    solider_level = building.level
                    cd = OriginalBuildingAttribute[building.BuildingType][BuildingAttribute.CD]
                    self.units[current_flag][solider_id]=\
                        Soldier(solider_name, solider_hp, solider_pos, solider_flag, solider_id, solider_level)
                    building.CD_left = cd  # 重置CD
                    self.total_id += 1
                    self.instruments[current_flag]['produce'].append(solider_id)
                    self.accumulation[current_flag]['sd_pro'] += 1
                else:
                    building.CD_left = building.CD_left - 1

    def update_age_phase(self):
        """Deal with the update_age instruments"""

        basic_consumption = 2000  # 基础升级科技消耗，未定
        increased_consumption = 1500  # 科技每升一级，下次升级科技资源消耗增量
        for flag in range(2):
            if self.raw_instruments[flag]['update_age']:
                consumption = basic_consumption + increased_consumption * self.status[flag]['tech']
                if self.status[flag]['money'] > consumption and self.status[flag]['tech'] < Age.AI.value:
                    self.status[flag]['money'] -= consumption
                    self.main_base[flag].HP = (
                        self.main_base[flag].HP /
                        (OriginalBuildingAttribute[BuildingType.Base][BuildingAttribute.ORIGINAL_HP]*
                        (self.status[flag]['tech'] + 2) * 0.5) *
                        (OriginalBuildingAttribute[BuildingType.Base][BuildingAttribute.ORIGINAL_HP] *
                        (self.status[flag]['tech'] + 3) * 0.5)
                                    )
                    self.status[flag]['tech'] += 1
                    self.instruments[flag]['update_age'].append(True)
                    self.accumulation[flag]['tech'] += 1
                else:
                    if print_info:
                        print("升级时代资源不足")
                    self.instruments[flag]['update_age'].append(False)

    def resource_phase(self):
        """Produce new resource and refresh building force"""
        for flag in range(2):
            basic_resource = OriginalBuildingAttribute[BuildingType.Programmer][BuildingAttribute.ORIGINAL_ATTACK]
            for building in self.buildings[flag]['resource']:
                resource = basic_resource * 0.5 * (building.level + 2)
                self.status[flag]['money'] += resource
                self.accumulation[flag]['money'] += resource
            self.status[flag]['building'] = 60 + 40 * self.status[flag]['tech']
            self.instruments[flag]['resource'] = True

    def debug_print(self):
        """debug时输出信息"""
        if self.turn_num == 0:
            file = "debug.txt"
            if os.path.exists(file):
                os.remove(file)
        
        line = "回合:" + str(self.turn_num) + '\n'
        with open("debug.txt", "a", encoding="utf8") as out:
            out.write(line)

        line = "\t指令:" + str(self.raw_instruments) + '\n'
        with open("debug.txt", "a", encoding="utf8") as out:
            out.write(line)

        with open("debug.txt", "a", encoding="utf8") as out:
            out.write("\t输出主基地血量\n")
        for flag in range(2):
            line = "\t\tflag:" + str(flag) + " HP:" + str(self.main_base[flag].HP) + '\n'
            with open("debug.txt", "a") as out:
                out.write(line)

        with open("debug.txt", "a", encoding="utf8") as out:
            out.write('\t输出building中的信息\n')
        for flag in range(2):
            line = '\t\tflag:' + str(flag) + '\n'
            with open("debug.txt", "a") as out:
                out.write(line)
            for building_type,buildings_of_type in self.buildings[flag].items():
                for building in buildings_of_type:
                    line = "\t\t\tID:" + str(building.Unit_ID) + " Type:" + str(int(building.BuildingType)) \
                          + " Position:" + str(building.Position.x) + ' ' + str(building.Position.y) \
                          + " Pro_pos:" + str(building.ProducePos.x if building.ProducePos != None else -1) \
                          + ' ' + str(building.ProducePos.y if building.ProducePos != None else -1) \
                          + " HP:" + str(building.HP) + '\n'
                    with open("debug.txt", "a") as out:
                        out.write(line)

        with open("debug.txt", "a", encoding="utf8") as out:
            out.write('\t输出unit中的信息\n')
        for flag in range(2):
            line = '\t\tflag:' + str(flag) + '\n'
            with open("debug.txt", "a") as out:
               out.write(line)
            tech_factor = 0.5 * (self.status[flag]['tech'] + 2)
            for unit_id, unit in self.units[flag].items():
                line = "\t\t\tID:" + str(unit_id) + " Type:" + str(int(unit.Soldier_Name)) \
                      + " Position:" + str(unit.Position.x) + ' ' + str(unit.Position.y) \
                      + " Attack:" + str(OriginalSoldierAttribute[unit.Soldier_Name][
                                SoldierAttr.SOLIDER_ORIGINAL_ATTACK] * tech_factor) \
                      + " HP:" + str(unit.HP) + '\n'
                with open("debug.txt", "a") as out:
                    out.write(line)

    def map_save(self):
        jmap=json.dumps(self._map)
        filename="map_save"+(str)(self.save_num)+".txt"
        with open(filename,'w') as f:
            f.write(jmap)

    def turn_save(self):
        bd_number = [[0 for i in range(17)] for _ in range(2)]
        for flag in range(2):
            for bd_type,bd_list in self.buildings[flag].items():
                for bd in bd_list:
                    bd_number[flag][bd.BuildingType - 1] += 1
        sd_number = [[0 for i in range(8)] for _ in range(2)]
        for flag in range(2):
            for sd_id, sd in self.units[flag].items():
                sd_number[flag][sd.Soldier_Name] += 1
                
        junits = [[] for _ in range(2)]
        jbuildings = [{
            'produce': [],
            'defence': [],
            'resource': []
        } for _ in range(2)]
        jstatus = [{
            'money': 0,
            'tech': 0,
            'building': 0,
        } for _ in range(2)]
        jinstruments = [{
            'attack': [],
            'move': [],
            'construct': [],
            'maintain': [],
            'upgrade': [],
            'sell': [],
            'update_age': [],
            'produce': [],
            'resource': False
        } for _ in range(2)]
        jbase=[{
            'base_HP':0,
            'base_pos':(0,0)
        } for _ in range(2)]
        for i in range (2):
            jbase[i]['base_HP']=self.main_base[i].HP
            jbase[i]['base_pos']=(self.main_base[i].Position.x,self.main_base[i].Position.y)
            for unit_id,unit in self.units[i].items():
                unit_temp={'name':str(unit.Soldier_Name),'hp':unit.HP,'pos':(unit.Position.x,unit.Position.y),'flag':unit.Flag,'id':unit.Unit_ID,'level':unit.level}
                junits[i].append(unit_temp)
            for building in self.buildings[i]['produce']:
                building_temp={'type':str(building.BuildingType),'pos':(building.Position.x,building.Position.y),'hp':building.HP,'flag':building.Flag,'id':building.Unit_ID,
                               'maintain':building.Is_Maintain,'level':building.level,'pro_pos':(building.ProducePos.x,building.ProducePos.y)}
                jbuildings[i]['produce'].append(building_temp)
            for building in self.buildings[i]['defence']:
                building_temp = {'type': str(building.BuildingType), 'pos': (building.Position.x, building.Position.y),
                                 'hp': building.HP, 'flag': building.Flag, 'id': building.Unit_ID,
                                 'maintain': building.Is_Maintain, 'level': building.level,
                                 'pro_pos': ()}
                jbuildings[i]['defence'].append(building_temp)
            for building in self.buildings[i]['resource']:
                building_temp = {'type': str(building.BuildingType), 'pos': (building.Position.x, building.Position.y),
                                 'hp': building.HP, 'flag': building.Flag, 'id': building.Unit_ID,
                                 'maintain': building.Is_Maintain, 'level': building.level,
                                 'pro_pos': ()}
                jbuildings[i]['resource'].append(building_temp)
            jstatus[i]=self.status[i]
            #jinstruments[i]['attack']=self.instruments[i]['attack']
            for id1,id2 in self.instruments[i]['attack']:
                jinstruments[i]['attack'].append({'id0':id1,'id1':id2})
            for id,pos in self.instruments[i]['move']:
                jinstruments[i]['move'].append({'id':id,'pos':(pos.x,pos.y)})
            for building in self.instruments[i]['construct']:
                construct_temp = {'type':str(building[0]),'pos':(building[1][0],building[1][1])}
                if building[0] < 9 and building[0] > 0:
                    produce_pos = (building[2][0],building[2][1])
                    construct_temp['pro_pos']=produce_pos
                jinstruments[i]['construct'].append(construct_temp)
            jinstruments[i]['maintain']=self.instruments[i]['maintain']
            jinstruments[i]['upgrade']=self.instruments[i]['upgrade']
            jinstruments[i]['sell'] = self.instruments[i]['sell']
            jinstruments[i]['produce'] = self.instruments[i]['produce']
            jinstruments[i]['resource']=self.instruments[i]['resource']

        data={'building_number0':bd_number[0],'building_number1':bd_number[1],
              'soldier_number0':sd_number[0],'soldier_number1':sd_number[1],
              'mainbase_0':jbase[0],'mainbase_1':jbase[1],
              'unit_0':junits[0],'unit_1':junits[1],
              'buildings_0':jbuildings[0],'buildings_1':jbuildings[1],
              'status_0':jstatus[0],'status_1':jstatus[1],
              'instruments_0':jinstruments[0],'instruments_1':jinstruments[1]}
        jdata = json.dumps(data)
        filename = "turn_save" + (str)(self.save_num) + ".txt"
        with open(filename, 'a') as f:
            f.write(jdata)
            f.write('\n')

    def draw_judge(self):
        bd_num = [0,0]
        for flag in range(2):
            for building_type,buildings in self.buildings[flag].items():
                bd_num[flag] += len(buildings)

        if self.winner != 1 and self.winner != 0:
            if self.status[0]['tech'] > self.status[1]['tech']:
                self.winner = 0
                return
            elif self.status[0]['tech'] < self.status[1]['tech']:
                self.winner = 1
                return
            if self.main_base[0].HP > self.main_base[1].HP:
                self.winner = 0
                return
            elif self.main_base[0].HP < self.main_base[1].HP:
                self.winner = 1
                return
            if bd_num[0] > bd_num[1]:
                self.winner = 0
                return
            elif bd_num[0] < bd_num[1]:
                self.winner = 1
                return
            if self.status[0]['money'] > self.status[1]['money']:
                self.winner = 0
                return
            elif self.status[0]['money'] < self.status[1]['money']:
                self.winner = 1
                return
    
    def next_tick(self):
        """回合演算与指令合法性判断"""
        # print(self.raw_instruments)


        self.instruments = [{
           'attack': [],
           'move': [],
           'construct': [],
           'maintain': [],
           'upgrade': [],
           'sell': [],
           'update_age': [],
           'produce': [],
           'resource': False
           } for _ in range(2)]
        
        self.attack_phase()
        self.clean_up_phase()
        self.move_phase()
        # print(self.raw_instruments[1])
        # print("传回的指令：")
        # for flag in range(2):
        #     print("flag:",flag)
        #     print('construct:',self.raw_instruments[flag]['construct'])
        #     print('maintain:',self.raw_instruments[flag]['maintain'])
        #     print('upgrade:',self.raw_instruments[flag]['upgrade'])
        #     print('sell:',self.raw_instruments[flag]['sell'])
        #     print('update_age:',self.raw_instruments[flag]['update_age'])
        self.check_legal()
        # print(self.raw_instruments[1])
        # print(self.raw_instruments)
        self.building_phase()
        self.produce_phase()
        self.update_age_phase()
        self.resource_phase()
        # self.update_id()
        self.judge_winnner()
        self.turn_save()
        # for building in self.buildings[0]['produce']:
        #     print(building.BuildingType,building.Unit_ID)
        #     print('****')
        # print('****************************************')

        # print(self.main_base[0].BuildingType,self.main_base[0].Position.x)
        # self.debug_print()
        # print("执行了的指令：")
        # for flag in range(2):
        #     print("flag:",flag)
        #     print('construct:',self.instruments[flag]['construct'])
        #     print('maintain:',self.instruments[flag]['maintain'])
        #     print('upgrade:',self.instruments[flag]['upgrade'])
        #     print('sell:',self.instruments[flag]['sell'])
        #     print('update_age:',self.instruments[flag]['update_age'])
        # self.raw_instruments = [{
        #     'construct': [],  # (BuildingType,(BuildingPos.x,BuildingPos.y),(SoldierPos.x,SoldierPos.y))
        #     'maintain': [],  # id
        #     'upgrade': [],  # id
        #     'sell': [],  # id
        #     'update_age': False,
        #     } for _ in range(2)]
        
        self.turn_num += 1
    def describe(self):
        tech_factor = max(self.accumulation[0]['tech'],self.accumulation[1]['tech']) * 0.5 + 1
        
        if (self.turn_num >= 10000 and self.winner == 2):
            self.description = '同时崩溃局'
            return
        if (self.winner == 2):
            if (self.turn_num < 1000):
                self.description = '同时爆炸'
            else:
                self.description = '龟缩拖平'
        else:
            if abs(self.accumulation[0]['tech'] - self.accumulation[1]['tech']) > 1:
                if self.accumulation[self.winner]['tech'] > self.accumulation[1 - self.winner]['tech']:
                    self.description = '高科技碾压'
                else:
                    if self.turn_num <80:
                        self.description = '低科技速攻'
                    else:
                        self.description = '低科技翻盘'
                return
            if abs(self.accumulation[0]['base_remain_hp'] - self.accumulation[1]['base_remain_hp']) < 2000 * tech_factor:
                if self.turn_num <80:
                    self.description = '光速对拆'
                else:
                    self.description = '均势对攻'
                return
            if abs(self.accumulation[0]['money'] - self.accumulation[1]['money']) > 15000 * tech_factor:
                if self.accumulation[self.winner]['money'] > self.accumulation[1 - self.winner]['money']:
                    self.description = '经济碾压'
                else:
                    self.description = '弱经济强攻'
                return
            if self.accumulation[self.winner]['sd_pro'] > self.accumulation[1 - self.winner]['sd_pro'] *2:
                if self.turn_num > 80:
                    self.description = '大军攻坚'
                else:
                    self.description = '暴兵速推'
                return
            if self.accumulation[self.winner]['sd_pro'] < self.accumulation[1 - self.winner]['sd_pro'] *0.5:
                if self.turn_num > 80:
                    self.description = '防守反击'
                else:
                    self.description = '精兵强攻'
                # if (abs(self.accumulation[0]['tech'] - self.accumulation[1]['tech'])>1)
    def assessment(self):
        for flag in range(2):
            self.accumulation[flag]['base_remain_hp'] = self.main_base[flag].HP
        
        self.describe()
        filename = "assessment" + (str)(self.save_num) + self.description + ".txt"
        with open(filename, 'a') as f:
            f.write("winner: ")
            json.dump(self.winner,f)
            f.write('  '+self.description)
            f.write('\n')
            f.write("turn: ")
            json.dump(self.turn_num,f)
            f.write('\n')
        for flag in range(2):
            accumulation = json.dumps( self.accumulation[flag] )
            with open(filename, 'a') as f:
                f.write(accumulation)
                f.write('\n')
            
        

def main():
    game = GameMain()
    game.next_tick()


if __name__ == "__main__":
    main()
