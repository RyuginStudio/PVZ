#ifndef __SUN_H__
#define __SUN_H__

#include "cocos2d.h"
#include "TestScene.h"

USING_NS_CC;

class Sun
{
public:

	Point position;           //阳光产生的位置

	int sun_scroll_idx = 0;   //帧动画的帧数

	int timmer_sun_disappear = 0;  //阳光消失定时器

	Sprite *sp_sun_scroll;    //阳光滚动精灵初始图片

	bool sun_from_sky;     //此阳光是否为空中掉落的

	void Sun_Scroll(TestScene &mission);  //阳光滚动帧动画

	Sun(Point pos, TestScene &mission, bool sun_from_sky);    //重载构造函数，阳光产生在植物所在的坐标

	Sun(bool sun_from_sky);
	~Sun();
};


#endif // !__SUN_H__
