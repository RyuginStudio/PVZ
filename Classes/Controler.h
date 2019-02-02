#ifndef __CONTROLER_H__
#define __CONTROLER_H__

#include "cocos2d.h"
#include "TestScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Controler
{
public:

	static void rand_change_BG(Sprite* &GameBackGround); //利用随机数更换地图

	static int SunValue;         //阳光值 

	static bool UserCanPlant;    //玩家是否可以种植植物
	
	Controler();  //初始化控制器相关

	static void drawTestGrid(TestScene &mission);   //绘制测试网格

	static void addZombieTest(TestScene &mission);

	static void createSunFromSky(TestScene &mission);    //公共事件阳光掉落

	static void sunFallDown(); //天上的阳光下落

	static void sunDisappear(TestScene &mission); //公共事件阳光在7秒后自动消失

	//具体植物的摇摆函数会在一定的帧数下调用自身的攻击函数
	static void plants_shake_controler(TestScene &mission);   //植物摇摆总控
	
	static void plant_disappear(TestScene &mission);   //植物死亡后（空血）清场总控

	static void zombieRecoverSpeed();    //恢复被冰减速僵尸的速度

	static void zombie_die_animation();   //僵尸死亡动画总控

	static void zombie_disappear(TestScene &mission);   //僵尸死亡后清场总控

	static void drawPlantIconTable(int count, TestScene &mission, Size winSize);  //绘制植物图标栏用于点选，从而种植植物 => 以及label能量消耗说明
	static void drawSunValue(TestScene *const &mission); //绘制当前关卡的雨露值，放入帧定时器中，没帧回调

	static void drawPlantMask(TestScene &mission);   //绘制植物蒙版（能量不够会使植物变灰）

	static void drawPlantSelectSquare(TestScene &mission, int PlantChoice);    //根据选择的植物，来绘制选择框，让玩家直观地看到选择的是什么植物

	//static void addZombie(TestScene &mission, int *beg, int *end);   //根据每个场景中的僵尸刷新数组，在mission场景中刷新僵尸

	static void eat_brain(TestScene &mission);   //吃掉大脑游戏结束
};

#endif // !__CONTROLER_H__