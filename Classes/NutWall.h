#ifndef __NUT_WALL_H__
#define __NUT_WALL_H__

#include "Plants.h"
#include "cocos2d.h";
#include "TestScene.h"
USING_NS_CC;

class NutWall :public Plants   //坚果墙
{
public:
	NutWall();
	~NutWall();

	//============================新加入的
	//重写父类方法
	void plants_shake(TestScene &mission);
	void plants_attack(TestScene &mission, int hang);
	Sprite* plants_ini(int hang, int lie);


	static int energy;          //种植植物所需的能量

						 //这样做的好处是，不共享图片的帧数，每个植物有自己的动画轨迹
	int pic_idx = 0;    //植物的图片索引值

};
#endif // !__NUT_WALL_H__