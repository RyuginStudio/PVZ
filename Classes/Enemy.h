#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h" 
USING_NS_CC;

class Enemy :public Node      //������Ҳ����˵һ�н�ʬ�ĸ���
{
public:
	Enemy();
	~Enemy();
//========================����ӵĸ��ຯ��

	virtual Sprite* enemy_ini(int hang);      //��ʼ������
	virtual void enemy_move_attack();         //�����ƶ��򹥻�

	Sprite* sp_enemy;//����ͼƬ

	int type;           //��ʬ����
	int demage;         //��ʬ�˺�
	int blood;          //��ʬѪ��
	double speed;       //��ʬ����

	bool ash = false;   //��ʬ�Ƿ�Ϊ�ҽ�״̬
	bool attack_or_not; //��ʬ�Ĺ���״̬

	int hang;           //��ʬ��������


	//�������ĺô��ǣ�������ͼƬ��֡����ÿ����ʬ���Լ��Ķ����켣
	int pic_idx = 0;          //��ʬ����ͼƬ����ֵ
	int pic_attack_idx = 0;   //��ʬ����ͼƬ����ֵ
	int pic_die_idx = 0;      //��ʬ����ͼƬ����ֵ

	bool disappear = false;   //��ʬִ���궯��������ʧ

};
#endif // !__ENEMY_H__