//向日葵

#include "SunFlower.h"
#include "Sun.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

extern std::vector<Bullet*> Vec_Bullet;       //子弹容器
extern std::vector<Sun*> Vec_Sun;             //阳光容器


int SunFlower::energy = 50; //初始化种植植物所需的能量


SunFlower::SunFlower()
{
}


SunFlower::~SunFlower()
{
}

Sprite *SunFlower::plants_ini(int hang, int lie)
{
	this->type = 0;           //植物种类
	this->hang = hang;        //植物的行
	this->lie = lie;          //植物的列 
	this->blood = 100;        //植物的血量 

	this->pic_idx = 0;
	this->pic_attack_idx = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取窗口尺寸
	this->sp_plant = Sprite::create("SunFlower/0.png");

	if (sp_plant == nullptr)
		exit(-1);  //空指针，加载不到资源报错！

	return sp_plant;
}


void SunFlower::plants_shake(TestScene &mission)
{
	if (pic_attack_idx == 50 && blood > 0 && beg_sun == true || pic_attack_idx == 300 && blood > 0)          //在植物处于50与300时，都会产生阳光
	{
		//产生阳光
		plants_attack(mission, hang);
		beg_sun = false; //关闭初始产生阳光的机制
	}

	if (pic_idx > 17)
		pic_idx = 0;   //重置
	if (pic_attack_idx > 300)
		pic_attack_idx = 0; //重置

	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("SunFlower/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
	sp_plant->setTexture(texture);

	pic_idx += 1;
	pic_attack_idx += 1;
}

void SunFlower::plants_attack(TestScene &mission, int hang)  //产生阳光
{
	auto sun = new Sun(sp_plant->getPosition(), mission, false);
	sun->sun_from_sky = false;
	Vec_Sun.push_back(sun);  //将阳光放入容器
}