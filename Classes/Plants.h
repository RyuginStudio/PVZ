#ifndef __PLANTS_H__
#define __PLANTS_H__
#include "cocos2d.h"
#include "TestScene.h"

USING_NS_CC;

class Plants :public Node
{
public:
	Plants();
	~Plants();

	static int energy;          //种植植物所需的能量
	int type;                   //植物种类
	int blood = 1;              //血量
	int hang;                   //植物所在的行
	int lie;                    //植物所在的列
	bool zombieEat = true;      //有的植物是僵尸不吃的（樱桃炸弹、辣椒）

	Sprite* sp_plant;           //精灵图片


//========================新添加的父类函数

	virtual Sprite* plants_ini(int hang, int lie);               //初始化植物(虚函数)
	virtual void plants_shake(TestScene &mission);               //植物摇摆(虚函数)
	virtual void plants_attack();                                //植物攻击僵尸(虚函数)

};
#endif // !__PLANTS_H__