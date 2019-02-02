#ifndef __SUN_FLOWER_H__
#define __SUN_FLOWER_H__

#include "Plants.h"
#include "cocos2d.h";
#include "TestScene.h"
USING_NS_CC;

class SunFlower : public Plants      //向日葵
{
public:
	SunFlower();
	~SunFlower();

	//============================新加入的
	//重写父类方法
	void plants_attack(TestScene &mission, int hang);
	void plants_shake(TestScene &mission);
	Sprite* plants_ini(int hang, int lie);

	static int energy;                //种植植物所需能量

	bool beg_sun = true;       //植物在动画50帧的时候产生初始阳光，在下一个50帧的时候关闭这个技能        


	//这样做的好处是，不共享图片的帧数，每个植物有自己的动画轨迹
	int pic_idx = 0;    //植物的图片索引值
	int pic_attack_idx = 0; //攻击索引值
};

#endif // !__SUN_FLOWER_H__