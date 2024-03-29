
# 基本设定

每张地图的一条对角线两端有双方玩家的主基地，地图上会随机生成若干条道路。玩家可以在非道路单元格上建造建筑，建筑类型有：生产型、防御型和资源型，三者分别自动进行单位生产、攻击敌方单位和资源获取操作。同时玩家可以花费一定资源升级时代，每升级一次时代都会解锁更强大的功能。通过合理地建造建筑，击毁敌方主基地或者在达到回合上限时拥有更多战斗力即可取得胜利。


# 地图设定

（1）基本设定：200*200正方形地图，实体与数据两层；1代表道路，0代表空地，2代表基地。玩家只能在空地上进行建造。

（2）主基地：主基地位于主对角线两个端点处，大小为7*7，主基地内不能存在任何单位与建筑，单位对主基地的距离按照顶点计算。

（3）道路：随机产生若干条宽度为1的道路连接双方主基地，所有道路成中心对称，道路之间不存在交叉。地图正中央有设有2*2的一块方形路面以使前后道路连通。

# 回合逻辑顺序

（1）防御塔攻击与单位死亡判定。

（2）单位攻击与防御塔被击毁判定。

（3）单位移动。

（4）指令合法性判断。

（5）建筑建造、修复、升级、出售（这四条有序）。

（6）单位生产。

（7）科技升级。

（8）资源生产。

（9）胜负判定。

# 时代

一共分为6个时代：比特、电路、处理器、算法、网络、AI。

升级时代基础消耗：2000 + 750 * (科技^2)

升级时代可以解锁以下功能：

（1）解锁新的建筑

（2）可建造已解锁的建筑的高级版

（3）可以对已建造在地图上的建筑进行建筑升级操作

（4）获得更高的建造力

# 建筑

（1）建筑占据1个单元格，不可位于道路或主基地内，玩家只能在“建造范围”内建造新建筑。

（2）建造范围：玩家每个已有建筑周围 6 至 10 格内以及主基地边缘4格宽度内（即玩家0横纵坐标<11，玩家1横纵坐标>188，且不在基地范围内）为建造范围，新建筑只能建于建造范围内。在同一回合内先后建造的建筑中，后建造的建筑可位于先建造建筑刚扩展的建造范围内，且不可与先建造的建筑相距5格以内。

（3）建筑的属性：建筑ID、生命值、位置、类型、CD、维修状态、攻击类型、攻击力、资源消耗、射程、AOE（单体伤害为0）、建造力需求。

（4）生产型建筑：可在生产范围内的任意一个“道路”单元格上生产兵种。

（5）防御型建筑：对攻击范围内的敌方兵种进行自动攻击，若无特殊说明，优先攻击最近的单位。

（6）资源型建筑：每回合获取资源值。

（7）初始建筑上限为40，每提升1级科技加20。

（8）双方在同一回合于相同或相邻位置建造，随机选取一方建造成功，另一方建造失败。

# 单位

（1）单位分为实体单位、数据单位两大类。

（2）单位会自动行动，玩家不可操作，行动模式有：推塔、冲锋、抗线。

（3）每种单位均由对应的生产建筑自动生产，不需要消耗资源。

（4）单位属性：ID、位置、生命值、行动模式、速度、攻击力、移动类型、射程。

（5）推塔模式：攻击范围内存在敌方建筑时停止移动并进行攻击直至摧毁目标。

（6）冲锋模式：单位冲向敌方主基地，在到达其边缘时死亡并对主基地造成大量伤害（不会攻击沿途建筑）。

（7）抗线模式：一边移动，同时攻击路过的建筑。

（8）单位没有碰撞体积，一个单元格内理论上可以存在无数个单位。


# 胜利条件

（1）限定回合内，一方摧毁另一方主基地即获胜。

（2）规定回合数内，不满足（1）或者双方主基地同时被摧毁，则按以下顺序判定胜负：

+ a.科技时代高的一方获胜

+ b.主基地剩余血量多的一方获胜

+ c.剩余建筑数量多的一方获胜

+ d.剩余资源总量多的一方获胜

+ e.以上均无法判定则平局

（3）一方AI崩溃，游戏将继续进行至结束，双方先后在游戏未结束之前崩溃，将调用平局判断。


# 主基地

主基地初始血量为10000，每升一级科技，最大血量提升5000，当前血量保持百分比不变。


# 关于建筑建造、升级、维修与出售

（1）所有新建的建筑均为0级建筑，拥有表格中的基础属性，消耗基础资源和建造力。

（2）可以对消耗资源以及建造力对建筑进行升级操作。

（3）进行科技升级后，已造的建筑并不会升级，需要单独进行建筑升级操作。

（4）建筑升级采用以下规则：

    a.消耗基础资源一半的资源与建造点，提升基础属性一半的属性。

	b.保持建筑生命值百分比不变。

	c.建筑升级并不会改变建筑种类。例如，在科技1级时，升级一个0级bool，它会变成一个1级布尔，而不是变成一个欧姆。

	d.建筑等级无法超过当前科技等级，每回合每建筑只能升一级。

（5）建筑维修按照建筑已损失的血量百分比补齐差价，不消耗建造力，每个建筑每回合最多维修20%的血量。

（6）建筑出售按剩余生命值比例返还最高50%的建造与升级消耗。

# 关于建造力

（1）建造力是一个只与科技水平相关的值，初始为60，每提升一级科技增加40。

（2）建造建筑需要花费建造力，建造力不足时无法进行建造。

（3）建造力每回合自动补充至满值，不会溢出，也不可囤积。

# 所有建筑与单位的详细设定

	1.科技因数 = 1+建筑等级*0.5
	2.所有给出基础值的实际数值为基础值*科技因数，即bit级别的数值为基础值，此后每级增加50%;
	3.关于AOE：AOE为2表示可以攻击某一格和其相邻格内所有单位，即与该格距离小于2，而非小于等于2，以此类推
	4.数据类单位只会被数据攻击打到，实体单位同理

|资源建筑|基础生命值|基础资源采集值|基础资源|基础建造力|
|-------|---------|------------|-------|--------|
|码农|100|10|100|10|

|生产建筑|基础生命值|单位|生产范围|生产CD|解锁时代|基础资源|基础建造力|
|-------|---------|--|--------|-------|-------|---------|------|
|香农|120|比特流|10|2|比特|150|15|
|戴维南|160|电压源|12|6|电路|160|16|
|诺顿|150|电流源|8|4|电路|160|16|
|冯诺依曼|200|ENIAC|15|15|处理器|200|20|
|伯纳斯李|150|数据包|10|3|网络|250|25|
|高锟|160|光纤|12|6|网络|400|40|
|图灵|300|图灵机|15|8|AI|600|60|
|托尼斯塔克|220|奥创|8|12|AI|600|60|

|单位|类型|行动模式|基础生命值|基础攻击力|攻击范围|移动速度|
|----|---|-------|---------|---------|-------|------|
|比特流|数据|推塔|16|10|12|12|
|电压源|实体|推塔|60|18|20|8|
|电流源|实体|冲锋|40|160|3|15|
|ENIAC|实体|抗线|400|12|5|4|
|数据包|数据|冲锋|50|300|3|16|
|光纤|实体|推塔|30|20|32|12|
|图灵机|数据|抗线|300|8|6|6|
|奥创|实体|推塔|200|500|20|8|

|防御建筑|基础生命值|基础攻击力|攻击CD|射程|攻击目标|AOE|解锁时代|基础资源|基础建造力|特效|
|-------|---------|---------|---|------|----|-------|-------|---------|---|----|
|布尔|220|16|1|32|数据|0|比特|150|15|布尔代数：有一半的几率攻击无效|
|欧姆|320|20|3|30|实体|6|电路|200|20|欧姆定律：同时击中电压源和电流源时对所有击中单位造成4倍伤害|
|摩尔|250|4|1|36|实体|0|处理器|225|22|摩尔定律：优先攻击上回合目标且对一个目标连续攻击时每次伤害*2|
|蒙特卡罗|350|25|2|50|实体|0|算法|200|20|蒙特卡罗方法：对单位造成的伤害会乘以一个0~2之间的随机数|
|拉里罗伯茨|220|6|1|40|全部|8|网络|250|25|阿帕网：优先攻击数据包且对数据包造成的伤害*3|
|罗伯特卡恩|520|5|1|35|数据|0|网络|450|45|TCP\IP协议：攻击任何目标均附加其最大生命值百分之10（*科技因数）的伤害|
|马斯克|750|0|1|15|全部|0|AI|500|50|AI末日论：使其攻击范围内的AI兵种无法移动与攻击|
|霍金|360|∞|7~2|20|全部|2|AI|500|50|黑洞：消灭1格和邻格内所有单位，等级越高cd越短|

