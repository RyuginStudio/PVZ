#include "Sun.h"


void Sun::Sun_Scroll(TestScene &mission)  //阳光滚动帧动画
{
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("SunScroll/"+CCString::createWithFormat("%d", sun_scroll_idx)->_string+".png");
	sp_sun_scroll->setTexture(texture);
	

	if(this->sun_from_sky == false)
	sp_sun_scroll->setPosition(Point(position.x + 10, position.y - 20));

	if (sun_scroll_idx == 21)
		sun_scroll_idx = 0;

	sun_scroll_idx++;

	this->timmer_sun_disappear++;   //控制阳光在七秒后自动消失
}

Sun::Sun(Point pos, TestScene &mission, bool sun_from_sky)  //重载构造函数，阳光产生在植物所在的坐标
{
	this->sun_from_sky = sun_from_sky;
	sp_sun_scroll = Sprite::create("SunScroll/0.png");
	this->position = pos;
	mission.addChild(sp_sun_scroll, 20);
}

Sun::Sun(bool sun_from_sky)
{
	this->sun_from_sky = sun_from_sky;
	sp_sun_scroll = Sprite::create("SunScroll/0.png");
}


Sun::~Sun()
{
}