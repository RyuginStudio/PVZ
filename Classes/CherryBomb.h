#ifndef __CHERRY_BOMB_H__
#define __CHERRY_BOMB_H__

#include <cocos2d.h>
#include "Plants.h"
#include "TestScene.h"

USING_NS_CC;

class CherryBomb : public Plants
{
public:
	CherryBomb();
	~CherryBomb();

//======================后加入的

//重写父类方法
	
	void plants_attack(TestScene &mission, int hang);
	void plants_shake(TestScene &mission);
	Sprite* plants_ini(int hang, int lie);


	static int energy;           //种植植物所需能量 => 150

	Sprite* sp_bomb;           //精灵“啵”图片

    //这样做的好处是，不共享图片的帧数，每个植物有自己的动画轨迹
	int pic_idx = 0;    //植物的图片索引值 => C++ 11类内初始化

};

#endif // !__CHERRY_BOMB_H__