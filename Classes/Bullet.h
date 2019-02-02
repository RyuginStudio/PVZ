#ifndef __BULLET_H__
#define __BULLET_H__

#include <cocos2d.h>
#include "TestScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Bullet : public Node
{
public:
	Bullet();
	~Bullet();

	int Pos_begin_x;  //�ӵ���ʼ���꣨������ײ��⣬���������Ľ�ʬ��
	int Pos_begin_y;


//�����¼����
	int bullet_type;  //�ӵ����࣬����ֲ���������ƥ��
	bool disappear = false;
	int hang;
	int demage;       //�ӵ����˺�ֵ

	Sprite *sp_bullet;
	

	void bulletInit(int bullet_type, int posBgnX, int posBgnY);  //�ӵ���ʼ��

	static void bulletRemove(TestScene &mission);   //���շ����ӵ�
	
	static void bullet_bomb_collision();   //�ӵ���ײ����Լ�ը��ͼƬ����(��ʬ�����Լ���ʬ��ײ����Ѫ)

};


#endif // !__BULLET_H__