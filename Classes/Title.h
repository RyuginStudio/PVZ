#ifndef __TITLE_H__
#define __TITLE_H__
#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	Title();
	~Title();

//后添加内容：
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Title);

	void GameBgCallBack(Ref *callback); //选择开始游戏的回调函数

	void update_per_0_1(float dt);  //设定0.1s定时器

};

#endif // !__TITLE_H__

