#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__
#include "cocos2d.h"

class TestScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene);
	
//========================================�󲹳��
	void update(float delta); //֡��ʱ��
	void update_winScroll(float dt);    //0.1s��ʱ�����ڻ������
	void update_0_1(float dt);
	void update_0_1_5(float dt);
	void update_1_5(float dt);
	void update_2_5(float dt);
	void update_4(float dt);
	void update_6(float dt);
	void update_5(float dt);
	void update_once(float dt); //ɾ����ӣ��ը�����ͼ��

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event); //��������
	void addNewSpriteAtPosition(cocos2d::Point p, int hang, int lie); //ͨ�������������øú�����Ӿ���
};
#endif // !__GAME_TITLE_SCENE_H__