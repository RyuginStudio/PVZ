#ifndef __TITLE_H__
#define __TITLE_H__
#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	Title();
	~Title();

//��������ݣ�
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Title);

	void GameBgCallBack(Ref *callback); //ѡ��ʼ��Ϸ�Ļص�����

	void update_per_0_1(float dt);  //�趨0.1s��ʱ��

};

#endif // !__TITLE_H__

