//���ǽ


#include "NutWall.h"
#include "Zombie1.h"

//��������
extern std::vector<Enemy*> Vec_Enemy;      //��������


int NutWall::energy = 50;   //��ʼ����ֲ��ֲ�����������



NutWall::NutWall()
{
}


NutWall::~NutWall()
{
}

void NutWall::plants_shake(TestScene & mission)
{
	if (pic_idx > 12)
		pic_idx = 0;   //����

	if (this->blood >= 800)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("NutWall/health_" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
		sp_plant->setTexture(texture);
	}
	else if (this->blood > 500)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("NutWall/hurt_" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
		sp_plant->setTexture(texture);
	}
	else
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("NutWall/dying_" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
		sp_plant->setTexture(texture);
	}

	pic_idx += 1;
}

void NutWall::plants_attack(TestScene & mission, int hang)  //���ض���ģʽ�м��ǽ���й���������������콩ʬ��Ϸmode��
{
	//�����
}

Sprite * NutWall::plants_ini(int hang, int lie)
{
	this->blood = 1000;           //ֲ�������Ѫ��
	this->type = 3;               //ֲ������
	this->hang = hang;            //ֲ�����
	this->lie = lie;              //ֲ�����

	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���ڳߴ�
	this->sp_plant = Sprite::create("NutWall/health_0.png");

	if (sp_plant == nullptr)
		exit(-1);  //��ָ�룬���ز�����Դ����

	return sp_plant;
}
