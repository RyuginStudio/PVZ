#include "CherryBomb.h"
#include "Zombie1.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

extern std::vector<Enemy*> Vec_Enemy;        //敌人容器


int CherryBomb::energy = 150;          //种植所需能量150


CherryBomb::CherryBomb()
{
}

CherryBomb::~CherryBomb()
{
}

void CherryBomb::plants_attack(TestScene & mission, int hang)
{	
	SimpleAudioEngine::getInstance()->playEffect("SE/cherrybomb.mp3");
	
	sp_bomb = Sprite::create("CherryBomb/CherryBomb.png"); //"啵"精灵图片
	sp_bomb->setName("CherryBomb");
	mission.addChild(sp_bomb, 3);
	sp_bomb->setPosition(this->sp_plant->getPosition());
	

	for (int i = 0; i < Vec_Enemy.size(); i++) //消灭3*3网格内的僵尸
	{
		if (abs(Vec_Enemy[i]->hang - this->hang) < 2 
			&& abs(Vec_Enemy[i]->sp_enemy->getPosition().x - sp_plant->getPosition().x) < 139 
			&& Vec_Enemy[i]->blood > 0) //对血量为0 => 已经进行死亡跌落动画的僵尸不进行操作
		{
			Texture2D *texture = TextureCache::sharedTextureCache()->addImage("ZombieAshes/zombie1Ash.png");
			Vec_Enemy[i]->sp_enemy->setTexture(texture);
			Vec_Enemy[i]->ash = true;  //僵尸转为灰烬状态
		}
	}

	this->blood = 0;  //帧定时器中的函数会自动消除blood为0的植物

	mission.scheduleOnce(schedule_selector(TestScene::update_once), .8f);  //.8f后删除“啵”图
}


void CherryBomb::plants_shake(TestScene & mission) //利用CCTEXTURE2d更改图片
{
	pic_idx += 1;

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("CherryBomb/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
	sp_plant->setTexture(texture);

	if (pic_idx == 6)
	{
		this->plants_attack(mission, hang);
	}
}


Sprite * CherryBomb::plants_ini(int hang, int lie)  //植物初始化
{
	this->hang = hang;            //植物的行
	this->lie = lie;              //植物的列
	this->blood = 100;            //植物血量

	this->zombieEat = false;      //僵尸不吃樱桃炸弹

	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取窗口尺寸
	this->sp_plant = Sprite::create("CherryBomb/0.png");

	if (sp_plant == nullptr)
		exit(-1);  //空指针，加载不到资源报错！

	return sp_plant;
}