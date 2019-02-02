#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h" 
USING_NS_CC;

class Enemy :public Node      //敌人类也就是说一切僵尸的父类
{
public:
	Enemy();
	~Enemy();
//========================新添加的父类函数

	virtual Sprite* enemy_ini(int hang);      //初始化敌人
	virtual void enemy_move_attack();         //敌人移动或攻击

	Sprite* sp_enemy;//精灵图片

	int type;           //僵尸种类
	int demage;         //僵尸伤害
	int blood;          //僵尸血量
	double speed;       //僵尸移速

	bool ash = false;   //僵尸是否为灰烬状态
	bool attack_or_not; //僵尸的攻击状态

	int hang;           //僵尸所处的行


	//这样做的好处是，不共享图片的帧数，每个僵尸有自己的动画轨迹
	int pic_idx = 0;          //僵尸行走图片索引值
	int pic_attack_idx = 0;   //僵尸攻击图片索引值
	int pic_die_idx = 0;      //僵尸死亡图片索引值

	bool disappear = false;   //僵尸执行完动画可以消失

};
#endif // !__ENEMY_H__