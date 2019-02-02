#ifndef __PEA_SHOOTER_H__
#define __PEA_SHOOTER_H__

#include "Plants.h"
#include "cocos2d.h";
#include "TestScene.h"
USING_NS_CC;

class PeaShooter :public Plants   //普通豌豆射手
{
public:
	PeaShooter();
	~PeaShooter();

//============================新加入的
   //重写父类方法
	void plants_attack(TestScene &mission, int hang);
	void plants_shake(TestScene &mission);
	Sprite* plants_ini(int hang, int lie);
	

	static int energy;                //种植植物所需能量

	//这样做的好处是，不共享图片的帧数，每个植物有自己的动画轨迹
	int pic_idx = 0;    //植物的图片索引值

};
#endif // ! __PEA_SHOOTER_H__