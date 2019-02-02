#ifndef __SUN_FLOWER_H__
#define __SUN_FLOWER_H__

#include "Plants.h"
#include "cocos2d.h";
#include "TestScene.h"
USING_NS_CC;

class SunFlower : public Plants      //���տ�
{
public:
	SunFlower();
	~SunFlower();

	//============================�¼����
	//��д���෽��
	void plants_attack(TestScene &mission, int hang);
	void plants_shake(TestScene &mission);
	Sprite* plants_ini(int hang, int lie);

	static int energy;                //��ֲֲ����������

	bool beg_sun = true;       //ֲ���ڶ���50֡��ʱ�������ʼ���⣬����һ��50֡��ʱ��ر��������        


	//�������ĺô��ǣ�������ͼƬ��֡����ÿ��ֲ�����Լ��Ķ����켣
	int pic_idx = 0;    //ֲ���ͼƬ����ֵ
	int pic_attack_idx = 0; //��������ֵ
};

#endif // !__SUN_FLOWER_H__