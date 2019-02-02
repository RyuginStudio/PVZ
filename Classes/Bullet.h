#ifndef __BULLET_H__
#define __BULLET_H__

#include <cocos2d.h>
#include "TestScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Bullet : public Node
{
public:
	Bullet();
	~Bullet();

	int Pos_begin_x;  //子弹初始坐标（用于碰撞检测，不攻击身后的僵尸）
	int Pos_begin_y;


//后来新加入的
	int bullet_type;  //子弹种类，根据植物的种类相匹配
	bool disappear = false;
	int hang;
	int demage;       //子弹的伤害值

	Sprite *sp_bullet;
	

	void bulletInit(int bullet_type, int posBgnX, int posBgnY);  //子弹初始化

	static void bulletRemove(TestScene &mission);   //回收废弃子弹
	
	static void bullet_bomb_collision();   //子弹碰撞检测以及炸裂图片更换(僵尸减速以及僵尸碰撞后伤血)

};


#endif // !__BULLET_H__