#ifndef __ZOMBIE1_H__
#define __ZOMBIE1_H__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class Zombie1 :public Enemy      //敌人类也就是说一切僵尸的父类
{
public:
	Zombie1();
	~Zombie1();
//=============================后来添加的

	Sprite* enemy_ini(int hang);      //初始化敌人
	void enemy_move_attack();         //敌人移动或攻击

};
#endif // !__ZOMBIE1_H__