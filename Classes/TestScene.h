#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__
#include "cocos2d.h"

class TestScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene);
	
//========================================后补充的
	void update(float delta); //帧定时器
	void update_winScroll(float dt);    //0.1s定时器用于画面滚动
	void update_0_1(float dt);
	void update_0_1_5(float dt);
	void update_1_5(float dt);
	void update_2_5(float dt);
	void update_4(float dt);
	void update_6(float dt);
	void update_5(float dt);
	void update_once(float dt); //删除“樱桃炸弹的啵图”

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event); //触摸函数
	void addNewSpriteAtPosition(cocos2d::Point p, int hang, int lie); //通过触摸函数调用该函数添加精灵
};
#endif // !__GAME_TITLE_SCENE_H__