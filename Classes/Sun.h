#ifndef __SUN_H__
#define __SUN_H__

#include "cocos2d.h"
#include "TestScene.h"

USING_NS_CC;

class Sun
{
public:

	Point position;           //���������λ��

	int sun_scroll_idx = 0;   //֡������֡��

	int timmer_sun_disappear = 0;  //������ʧ��ʱ��

	Sprite *sp_sun_scroll;    //������������ʼͼƬ

	bool sun_from_sky;     //�������Ƿ�Ϊ���е����

	void Sun_Scroll(TestScene &mission);  //�������֡����

	Sun(Point pos, TestScene &mission, bool sun_from_sky);    //���ع��캯�������������ֲ�����ڵ�����

	Sun(bool sun_from_sky);
	~Sun();
};


#endif // !__SUN_H__
