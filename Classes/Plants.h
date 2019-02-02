#ifndef __PLANTS_H__
#define __PLANTS_H__
#include "cocos2d.h"
#include "TestScene.h"

USING_NS_CC;

class Plants :public Node
{
public:
	Plants();
	~Plants();

	static int energy;          //��ֲֲ�����������
	int type;                   //ֲ������
	int blood = 1;              //Ѫ��
	int hang;                   //ֲ�����ڵ���
	int lie;                    //ֲ�����ڵ���
	bool zombieEat = true;      //�е�ֲ���ǽ�ʬ���Եģ�ӣ��ը����������

	Sprite* sp_plant;           //����ͼƬ


//========================����ӵĸ��ຯ��

	virtual Sprite* plants_ini(int hang, int lie);               //��ʼ��ֲ��(�麯��)
	virtual void plants_shake(TestScene &mission);               //ֲ��ҡ��(�麯��)
	virtual void plants_attack();                                //ֲ�﹥����ʬ(�麯��)

};
#endif // !__PLANTS_H__