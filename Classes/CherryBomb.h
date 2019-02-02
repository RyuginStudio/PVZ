#ifndef __CHERRY_BOMB_H__
#define __CHERRY_BOMB_H__

#include <cocos2d.h>
#include "Plants.h"
#include "TestScene.h"

USING_NS_CC;

class CherryBomb : public Plants
{
public:
	CherryBomb();
	~CherryBomb();

//======================������

//��д���෽��
	
	void plants_attack(TestScene &mission, int hang);
	void plants_shake(TestScene &mission);
	Sprite* plants_ini(int hang, int lie);


	static int energy;           //��ֲֲ���������� => 150

	Sprite* sp_bomb;           //���顰࣡�ͼƬ

    //�������ĺô��ǣ�������ͼƬ��֡����ÿ��ֲ�����Լ��Ķ����켣
	int pic_idx = 0;    //ֲ���ͼƬ����ֵ => C++ 11���ڳ�ʼ��

};

#endif // !__CHERRY_BOMB_H__