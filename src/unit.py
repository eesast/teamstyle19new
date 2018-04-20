#! /usr/bin/env python3
# -*- coding: utf-8 -*-

from enum import IntEnum

"""
为保证基类调用时的安全性 所有属性都设置为了私有 同时为了方便调用 使用了装饰器来提供返回值
但没有设置 set函数的装饰器，因此属性现在处于能读不能取的状态 在以后确定了哪些变量需要在运行期间重新赋值再加入对应的set的装饰器"""

# ***********************The Define of Global Parameters************************
Inf = 1000


# *****************************Enum Value ant Table*****************************
class Command(IntEnum):
    Construct = 0
    Maintain = 1
    Upgrade = 2
    Sell = 3
    Update_Age = 4


class UnitType(IntEnum):
    Base = 0

    PRODUCTION_BUILDING = 1
    DEFENSIVE_BUILDING = 2
    RESOURCE_BUILDING = 3

    DATA = 4
    SUBSTANCE = 5
    ALL = 6


class Age(IntEnum):
    BIT = 0
    CIRCUIT = 1
    PROCESSOR = 2
    ALGORITHM = 3
    NETWORK = 4
    AI = 5


class BuildingType(IntEnum):
    Base = 0

    Shannon = 1
    Thevenin = 2
    Norton = 3
    Von_Neumann = 4
    Berners_Lee = 5
    Kuen_Kao = 6
    Turing = 7
    Tony_Stark = 8

    Bool = 9
    Ohm = 10
    Mole = 11
    Monte_Carlo = 12
    Larry_Roberts = 13
    Robert_Kahn = 14
    Musk = 15
    Hawkin = 16

    Programmer = 17


class BuildingAttribute(IntEnum):
    BUILDING_TYPE = 0
    ORIGINAL_HP = 1
    ORIGINAL_ATTACK = 2
    ORIGINAL_RANGE = 3
    TARGET = 4
    AGE = 5
    ORIGINAL_RESOURCE = 6
    ORIGINAL_BUILDING_POINT = 7
    AOE = 8
    CD = 9


class SoldierName(IntEnum):
    BIT_STREAM = 0
    VOLTAGE_SOURCE = 1
    CURRENT_SOURCE = 2
    ENIAC = 3
    PACKET = 4
    OPTICAL_FIBER = 5
    TURNING_MACHINE = 6
    ULTRON = 7


class SoldierAttr(IntEnum):
    SOLIDER_TYPE = 0
    ACTION_MODE = 1
    SOLIDER_ORIGINAL_HP = 2
    SOLIDER_ORIGINAL_ATTACK = 3
    ATTACK_RANGE = 4
    SPEED = 5


class ActionMode(IntEnum):
    BUILDING_ATTACK = 0
    BASE_ATTACK = 1
    MOVING_ATTACK = 2


OriginalBuildingAttribute = {

    BuildingType.Base: {BuildingAttribute.BUILDING_TYPE: UnitType.Base,
                        BuildingAttribute.ORIGINAL_HP: 10000,
                        BuildingAttribute.ORIGINAL_ATTACK: 0,
                        BuildingAttribute.ORIGINAL_RANGE: 0,
                        BuildingAttribute.TARGET: None,
                        BuildingAttribute.AGE: Age.BIT,
                        BuildingAttribute.ORIGINAL_RESOURCE: 0,
                        BuildingAttribute.ORIGINAL_BUILDING_POINT: None,
                        BuildingAttribute.AOE: None,
                        BuildingAttribute.CD: None}
,  # need to complete
    BuildingType.Shannon: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                           BuildingAttribute.ORIGINAL_HP: 120,
                           BuildingAttribute.ORIGINAL_ATTACK: None,
                           BuildingAttribute.ORIGINAL_RANGE: 8,
                           BuildingAttribute.TARGET: SoldierName.BIT_STREAM,
                           BuildingAttribute.AGE: Age.BIT,
                           BuildingAttribute.ORIGINAL_RESOURCE: 150,
                           BuildingAttribute.ORIGINAL_BUILDING_POINT: 15,
                           BuildingAttribute.AOE: None,
                           BuildingAttribute.CD: 2},
    BuildingType.Thevenin: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                            BuildingAttribute.ORIGINAL_HP: 160,
                            BuildingAttribute.ORIGINAL_ATTACK: None,
                            BuildingAttribute.ORIGINAL_RANGE: 5,
                            BuildingAttribute.TARGET: SoldierName.VOLTAGE_SOURCE,
                            BuildingAttribute.AGE: Age.CIRCUIT,
                            BuildingAttribute.ORIGINAL_RESOURCE: 160,
                            BuildingAttribute.ORIGINAL_BUILDING_POINT: 16,
                            BuildingAttribute.AOE: None,
                            BuildingAttribute.CD: 6},
    BuildingType.Norton: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                          BuildingAttribute.ORIGINAL_HP: 150,
                          BuildingAttribute.ORIGINAL_ATTACK: None,
                          BuildingAttribute.ORIGINAL_RANGE: 5,
                          BuildingAttribute.TARGET: SoldierName.CURRENT_SOURCE,
                          BuildingAttribute.AGE: Age.CIRCUIT,
                          BuildingAttribute.ORIGINAL_RESOURCE: 160,
                          BuildingAttribute.ORIGINAL_BUILDING_POINT: 16,
                          BuildingAttribute.AOE: None,
                          BuildingAttribute.CD: 4},
    BuildingType.Von_Neumann: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                               BuildingAttribute.ORIGINAL_HP: 200,
                               BuildingAttribute.ORIGINAL_ATTACK: None,
                               BuildingAttribute.ORIGINAL_RANGE: 12,
                               BuildingAttribute.TARGET: SoldierName.ENIAC,
                               BuildingAttribute.AGE: Age.PROCESSOR,
                               BuildingAttribute.ORIGINAL_RESOURCE: 200,
                               BuildingAttribute.ORIGINAL_BUILDING_POINT: 20,
                               BuildingAttribute.AOE: None,
                               BuildingAttribute.CD: 15},
    BuildingType.Berners_Lee: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                               BuildingAttribute.ORIGINAL_HP: 150,
                               BuildingAttribute.ORIGINAL_ATTACK: None,
                               BuildingAttribute.ORIGINAL_RANGE: 10,
                               BuildingAttribute.TARGET: SoldierName.PACKET,
                               BuildingAttribute.AGE: Age.NETWORK,
                               BuildingAttribute.ORIGINAL_RESOURCE: 250,
                               BuildingAttribute.ORIGINAL_BUILDING_POINT: 25,
                               BuildingAttribute.AOE: None,
                               BuildingAttribute.CD: 3},
    BuildingType.Kuen_Kao: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                            BuildingAttribute.ORIGINAL_HP: 160,
                            BuildingAttribute.ORIGINAL_ATTACK: None,
                            BuildingAttribute.ORIGINAL_RANGE: 12,
                            BuildingAttribute.TARGET: SoldierName.OPTICAL_FIBER,
                            BuildingAttribute.AGE: Age.NETWORK,
                            BuildingAttribute.ORIGINAL_RESOURCE: 400,
                            BuildingAttribute.ORIGINAL_BUILDING_POINT: 40,
                            BuildingAttribute.AOE: None,
                            BuildingAttribute.CD: 6},
    BuildingType.Turing: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                          BuildingAttribute.ORIGINAL_HP: 250,
                          BuildingAttribute.ORIGINAL_ATTACK: None,
                          BuildingAttribute.ORIGINAL_RANGE: 10,
                          BuildingAttribute.TARGET: SoldierName.TURNING_MACHINE,
                          BuildingAttribute.AGE: Age.AI,
                          BuildingAttribute.ORIGINAL_RESOURCE: 600,
                          BuildingAttribute.ORIGINAL_BUILDING_POINT: 60,
                          BuildingAttribute.AOE: None,
                          BuildingAttribute.CD: 20},
    BuildingType.Tony_Stark: {BuildingAttribute.BUILDING_TYPE: UnitType.PRODUCTION_BUILDING,
                              BuildingAttribute.ORIGINAL_HP: 220,
                              BuildingAttribute.ORIGINAL_ATTACK: None,
                              BuildingAttribute.ORIGINAL_RANGE: 8,
                              BuildingAttribute.TARGET: SoldierName.ULTRON,
                              BuildingAttribute.AGE: Age.AI,
                              BuildingAttribute.ORIGINAL_RESOURCE: 600,
                              BuildingAttribute.ORIGINAL_BUILDING_POINT: 60,
                              BuildingAttribute.AOE: None,
                              BuildingAttribute.CD: 20},

    BuildingType.Bool: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                        BuildingAttribute.ORIGINAL_HP: 220,
                        BuildingAttribute.ORIGINAL_ATTACK: 16,
                        BuildingAttribute.ORIGINAL_RANGE: 32,
                        BuildingAttribute.TARGET: UnitType.DATA,
                        BuildingAttribute.AGE: Age.BIT,
                        BuildingAttribute.ORIGINAL_RESOURCE: 150,
                        BuildingAttribute.ORIGINAL_BUILDING_POINT: 15,
                        BuildingAttribute.AOE: 0,
                        BuildingAttribute.CD: 1},
    BuildingType.Ohm: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                       BuildingAttribute.ORIGINAL_HP: 320,
                       BuildingAttribute.ORIGINAL_ATTACK: 20,
                       BuildingAttribute.ORIGINAL_RANGE: 30,
                       BuildingAttribute.TARGET: UnitType.SUBSTANCE,
                       BuildingAttribute.AGE: Age.CIRCUIT,
                       BuildingAttribute.ORIGINAL_RESOURCE: 200,
                       BuildingAttribute.ORIGINAL_BUILDING_POINT: 20,
                       BuildingAttribute.AOE: 6,
                       BuildingAttribute.CD: 3},
    BuildingType.Mole: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                        BuildingAttribute.ORIGINAL_HP: 250,
                        BuildingAttribute.ORIGINAL_ATTACK: 4,
                        BuildingAttribute.ORIGINAL_RANGE: 36,
                        BuildingAttribute.TARGET: UnitType.DATA,
                        BuildingAttribute.AGE: Age.PROCESSOR,
                        BuildingAttribute.ORIGINAL_RESOURCE: 225,
                        BuildingAttribute.ORIGINAL_BUILDING_POINT: 22,
                        BuildingAttribute.AOE: 0,
                        BuildingAttribute.CD: 1},
    BuildingType.Monte_Carlo: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                               BuildingAttribute.ORIGINAL_HP: 350,
                               BuildingAttribute.ORIGINAL_ATTACK: 25,
                               BuildingAttribute.ORIGINAL_RANGE: 50,
                               BuildingAttribute.TARGET: UnitType.SUBSTANCE,
                               BuildingAttribute.AGE: Age.ALGORITHM,
                               BuildingAttribute.ORIGINAL_RESOURCE: 200,
                               BuildingAttribute.ORIGINAL_BUILDING_POINT: 20,
                               BuildingAttribute.AOE: 0,
                               BuildingAttribute.CD: 2},
    BuildingType.Larry_Roberts: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                                 BuildingAttribute.ORIGINAL_HP: 220,
                                 BuildingAttribute.ORIGINAL_ATTACK: 6,
                                 BuildingAttribute.ORIGINAL_RANGE: 40,
                                 BuildingAttribute.TARGET: UnitType.ALL,
                                 BuildingAttribute.AGE: Age.NETWORK,
                                 BuildingAttribute.ORIGINAL_RESOURCE: 250,
                                 BuildingAttribute.ORIGINAL_BUILDING_POINT: 25,
                                 BuildingAttribute.AOE: 8,
                                 BuildingAttribute.CD: 1},
    BuildingType.Robert_Kahn: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                               BuildingAttribute.ORIGINAL_HP: 520,
                               BuildingAttribute.ORIGINAL_ATTACK: 5,
                               BuildingAttribute.ORIGINAL_RANGE: 35,
                               BuildingAttribute.TARGET: UnitType.DATA,
                               BuildingAttribute.AGE: Age.NETWORK,
                               BuildingAttribute.ORIGINAL_RESOURCE: 450,
                               BuildingAttribute.ORIGINAL_BUILDING_POINT: 45,
                               BuildingAttribute.AOE: 0,
                               BuildingAttribute.CD: 1},
    BuildingType.Musk: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                        BuildingAttribute.ORIGINAL_HP: 1000,
                        BuildingAttribute.ORIGINAL_ATTACK: 0,
                        BuildingAttribute.ORIGINAL_RANGE: 24,
                        BuildingAttribute.TARGET: UnitType.ALL,
                        BuildingAttribute.AGE: Age.AI,
                        BuildingAttribute.ORIGINAL_RESOURCE: 500,
                        BuildingAttribute.ORIGINAL_BUILDING_POINT: 50,
                        BuildingAttribute.AOE: 0,
                        BuildingAttribute.CD: 1},
    BuildingType.Hawkin: {BuildingAttribute.BUILDING_TYPE: UnitType.DEFENSIVE_BUILDING,
                          BuildingAttribute.ORIGINAL_HP: 360,
                          BuildingAttribute.ORIGINAL_ATTACK: Inf,
                          BuildingAttribute.ORIGINAL_RANGE: 20,
                          BuildingAttribute.TARGET: UnitType.ALL,
                          BuildingAttribute.AGE: Age.AI,
                          BuildingAttribute.ORIGINAL_RESOURCE: 500,
                          BuildingAttribute.ORIGINAL_BUILDING_POINT: 50,
                          BuildingAttribute.AOE: 1,
                          BuildingAttribute.CD: 6},

    BuildingType.Programmer: {BuildingAttribute.BUILDING_TYPE: UnitType.RESOURCE_BUILDING,
                              BuildingAttribute.ORIGINAL_HP: 100,
                              BuildingAttribute.ORIGINAL_ATTACK: 10,
                              BuildingAttribute.ORIGINAL_RANGE: 0,
                              BuildingAttribute.TARGET: UnitType.ALL,
                              BuildingAttribute.AGE: Age.BIT,
                              BuildingAttribute.ORIGINAL_RESOURCE: 100,
                              BuildingAttribute.ORIGINAL_BUILDING_POINT: 10,
                              BuildingAttribute.AOE: 0,
                              BuildingAttribute.CD: 1},
    # use attack stand for the ability of resource building to get resource
}

OriginalSoldierAttribute = {
    SoldierName.BIT_STREAM: {SoldierAttr.SOLIDER_TYPE: UnitType.DATA,
                             SoldierAttr.ACTION_MODE: ActionMode.BUILDING_ATTACK,
                             SoldierAttr.SOLIDER_ORIGINAL_HP: 16,
                             SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 10,
                             SoldierAttr.ATTACK_RANGE: 16,
                             SoldierAttr.SPEED: 12},
    SoldierName.VOLTAGE_SOURCE: {SoldierAttr.SOLIDER_TYPE: UnitType.SUBSTANCE,
                                 SoldierAttr.ACTION_MODE: ActionMode.BUILDING_ATTACK,
                                 SoldierAttr.SOLIDER_ORIGINAL_HP: 60,
                                 SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 18,
                                 SoldierAttr.ATTACK_RANGE: 24,
                                 SoldierAttr.SPEED: 8},
    SoldierName.CURRENT_SOURCE: {SoldierAttr.SOLIDER_TYPE: UnitType.SUBSTANCE,
                                 SoldierAttr.ACTION_MODE: ActionMode.BASE_ATTACK,
                                 SoldierAttr.SOLIDER_ORIGINAL_HP: 40,
                                 SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 160,
                                 SoldierAttr.ATTACK_RANGE: 3,
                                 SoldierAttr.SPEED: 15},
    SoldierName.ENIAC: {SoldierAttr.SOLIDER_TYPE: UnitType.SUBSTANCE,
                        SoldierAttr.ACTION_MODE: ActionMode.MOVING_ATTACK,
                        SoldierAttr.SOLIDER_ORIGINAL_HP: 550,
                        SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 12,
                        SoldierAttr.ATTACK_RANGE: 10,
                        SoldierAttr.SPEED: 4},
    SoldierName.PACKET: {SoldierAttr.SOLIDER_TYPE: UnitType.DATA,
                         SoldierAttr.ACTION_MODE: ActionMode.BASE_ATTACK,
                         SoldierAttr.SOLIDER_ORIGINAL_HP: 50,
                         SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 300,
                         SoldierAttr.ATTACK_RANGE: 3,
                         SoldierAttr.SPEED: 16},
    SoldierName.OPTICAL_FIBER: {SoldierAttr.SOLIDER_TYPE: UnitType.SUBSTANCE,
                                SoldierAttr.ACTION_MODE: ActionMode.BUILDING_ATTACK,
                                SoldierAttr.SOLIDER_ORIGINAL_HP: 40,
                                SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 25,
                                SoldierAttr.ATTACK_RANGE: 40,
                                SoldierAttr.SPEED: 12},
    SoldierName.TURNING_MACHINE: {SoldierAttr.SOLIDER_TYPE: UnitType.DATA,
                                  SoldierAttr.ACTION_MODE: ActionMode.MOVING_ATTACK,
                                  SoldierAttr.SOLIDER_ORIGINAL_HP: 850,
                                  SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 8,
                                  SoldierAttr.ATTACK_RANGE: 12,
                                  SoldierAttr.SPEED: 3},
    SoldierName.ULTRON: {SoldierAttr.SOLIDER_TYPE: UnitType.SUBSTANCE,
                         SoldierAttr.ACTION_MODE: ActionMode.BUILDING_ATTACK,
                         SoldierAttr.SOLIDER_ORIGINAL_HP: 200,
                         SoldierAttr.SOLIDER_ORIGINAL_ATTACK: 500,
                         SoldierAttr.ATTACK_RANGE: 20,
                         SoldierAttr.SPEED: 8},
}


# ******************************************************************************

# *********************************Basic Class**********************************
class Resource(object):
    def __init__(self, building_point_1, building_point_2, resource_1, resource_2):
        self.__building_point_1 = building_point_1
        self.__building_point_2 = building_point_2
        self.__resource_1 = resource_1
        self.__resource_2 = resource_2

    @property
    def building_point_1(self):
        return self.__building_point_1

    @property
    def building_point_2(self):
        return self.__building_point_2

    @property
    def resource_1(self):
        return self.__resource_1

    @property
    def resource_2(self):
        return self.__resource_2


class Position(object):
    def __init__(self, x, y):
        self.__x = x
        self.__y = y

    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y


class Building(object):
    def __init__(self, building_type, pos, flag, unit_id, maintain, time, produce_pos):
        self.__BuildingType = building_type
        self.__HP = OriginalBuildingAttribute[building_type][BuildingAttribute.ORIGINAL_HP] * (1 + time / 2)
        self.__Position = pos
        self.__Flag = flag
        self.__Unit_ID = unit_id
        self.__Is_Maintain = maintain
        self.level = time
        self.__CD_left = 0
        self.__Produce_Position = produce_pos
        # 以下为仅用于BuildingType为Mole的成员
        self.last_target_id = -1
        self.mult_factor = 1

    @property
    def ProducePos(self):
        return self.__Produce_Position

    @ProducePos.setter
    def ProducePos(self,produce_pos):
        self.__Produce_Position = produce_pos

    @property
    def HP(self):
        return self.__HP

    @HP.setter
    def HP(self, hp):
        # some condition
        self.__HP = hp

    @property
    def BuildingType(self):
        return self.__BuildingType

    @property
    def Position(self):
        return self.__Position

    @property
    def Flag(self):
        return self.__Flag

    @property
    def Unit_ID(self):
        return self.__Unit_ID

    @property
    def Is_Maintain(self):
        return self.__Is_Maintain

    @property
    def CD_left(self):
        if self.__BuildingType == BuildingType.Programmer:
            raise AttributeError("Programmer Building has no attribute of CD_left")
        else:
            return self.__CD_left

    @CD_left.setter
    def CD_left(self, cd_left):
        self.__CD_left = cd_left


class Soldier(object):
    def __init__(self, solider_name, hp, pos, flag, unit_id, level):
        self.__Soldier_Name = solider_name
        self.__HP = hp
        self.__Position = pos
        self.__Flag = flag
        self.__Unit_ID = unit_id
        self.level = level

    @property
    def HP(self):
        return self.__HP

    @HP.setter
    def HP(self, hp):
        # some condition
        self.__HP = hp

    @property
    def Soldier_Name(self):
        return self.__Soldier_Name

    @property
    def Position(self):
        return self.__Position

    @Position.setter
    def Position(self, Position1):
        self.__Position = Position1

    @property
    def Flag(self):
        return self.__Flag

    @property
    def Unit_ID(self):
        return self.__Unit_ID

# ******************************************************************************
