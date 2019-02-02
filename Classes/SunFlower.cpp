//���տ�

#include "SunFlower.h"
#include "Sun.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

extern std::vector<Bullet*> Vec_Bullet;       //�ӵ�����
extern std::vector<Sun*> Vec_Sun;             //��������


int SunFlower::energy = 50; //��ʼ����ֲֲ�����������


SunFlower::SunFlower()
{
}


SunFlower::~SunFlower()
{
}

Sprite *SunFlower::plants_ini(int hang, int lie)
{
	this->type = 0;           //ֲ������
	this->hang = hang;        //ֲ�����
	this->lie = lie;          //ֲ����� 
	this->blood = 100;        //ֲ���Ѫ�� 

	this->pic_idx = 0;
	this->pic_attack_idx = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���ڳߴ�
	this->sp_plant = Sprite::create("SunFlower/0.png");

	if (sp_plant == nullptr)
		exit(-1);  //��ָ�룬���ز�����Դ����

	return sp_plant;
}


void SunFlower::plants_shake(TestScene &mission)
{
	if (pic_attack_idx == 50 && blood > 0 && beg_sun == true || pic_attack_idx == 300 && blood > 0)          //��ֲ�ﴦ��50��300ʱ�������������
	{
		//��������
		plants_attack(mission, hang);
		beg_sun = false; //�رճ�ʼ��������Ļ���
	}

	if (pic_idx > 17)
		pic_idx = 0;   //����
	if (pic_attack_idx > 300)
		pic_attack_idx = 0; //����

	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("SunFlower/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
	sp_plant->setTexture(texture);

	pic_idx += 1;
	pic_attack_idx += 1;
}

void SunFlower::plants_attack(TestScene &mission, int hang)  //��������
{
	auto sun = new Sun(sp_plant->getPosition(), mission, false);
	sun->sun_from_sky = false;
	Vec_Sun.push_back(sun);  //�������������
}