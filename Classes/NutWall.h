#ifndef __NUT_WALL_H__
#define __NUT_WALL_H__

#include "Plants.h"
#include "cocos2d.h";
#include "TestScene.h"
USING_NS_CC;

class NutWall :public Plants   //���ǽ
{
public:
	NutWall();
	~NutWall();

	//============================�¼����
	//��д���෽��
	void plants_shake(TestScene &mission);
	void plants_attack(TestScene &mission, int hang);
	Sprite* plants_ini(int hang, int lie);


	static int energy;          //��ֲֲ�����������

						 //�������ĺô��ǣ�������ͼƬ��֡����ÿ��ֲ�����Լ��Ķ����켣
	int pic_idx = 0;    //ֲ���ͼƬ����ֵ

};
#endif // !__NUT_WALL_H__