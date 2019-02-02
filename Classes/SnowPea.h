#ifndef __SNOW_PEA_H__
#define __SNOW_PEA_H__

#include "Plants.h"
#include "cocos2d.h";
#include "TestScene.h"

USING_NS_CC;

class SnowPea : public Plants
{
public:
	SnowPea();
	~SnowPea();
	//============================�¼����
	//��д���෽��
	void plants_attack(TestScene &mission, int hang);
	void plants_shake(TestScene &mission);
	Sprite* plants_ini(int hang, int lie);


	static int energy;                //��ֲֲ�����������

						 //�������ĺô��ǣ�������ͼƬ��֡����ÿ��ֲ�����Լ��Ķ����켣
	int pic_idx = 0;    //ֲ���ͼƬ����ֵ

};

#endif // !__SNOW_PEA_H__


