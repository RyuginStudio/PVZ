#ifndef __ZOMBIE1_H__
#define __ZOMBIE1_H__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class Zombie1 :public Enemy      //������Ҳ����˵һ�н�ʬ�ĸ���
{
public:
	Zombie1();
	~Zombie1();
//=============================������ӵ�

	Sprite* enemy_ini(int hang);      //��ʼ������
	void enemy_move_attack();         //�����ƶ��򹥻�

};
#endif // !__ZOMBIE1_H__