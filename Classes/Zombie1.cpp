#include "Zombie1.h"
#include "SunFlower.h"
#include "PeaShooter.h"
#include "SnowPea.h"
#include "NutWall.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

extern std::vector<Plants*> Vec_Plants;    //向日葵容器

extern bool array_PlantOrNot[6][10];


Zombie1::Zombie1()
{
	this->blood = 100;
}

Zombie1::~Zombie1()
{
}


Sprite * Zombie1::enemy_ini(int hang)
{
	this->hang = hang;

	this->attack_or_not = false;

	this->speed = -1.2;

	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取窗口尺寸

	sp_enemy = Sprite::create("zombie1_move/0.png");

	if (sp_enemy == nullptr)
		exit(-1);  //空指针，加载不到资源报错！
	
	/*左侧距离宽度为：66   下侧距离高度为：18
	格子横向宽度为：91  格子纵向高度为：106*/
	sp_enemy->setPosition(visibleSize.width+sp_enemy->getContentSize().width/9, (hang-1)*106+18+80); //设定角色x位置，最好换成随机数形式
	
	return sp_enemy;
}

void Zombie1::enemy_move_attack()
{
	if (ash == true)  //如果状态为：灰烬
		return;
	
	for (int idx = 0; idx < Vec_Plants.size(); idx++)
	{
		if (Vec_Plants[idx]->hang == this->hang               //设定好区间，解决在僵尸身后种植，导致僵尸切成攻击状态（卡住）的问题
			&& Vec_Plants[idx]->sp_plant->getPosition().x >= this->sp_enemy->getPosition().x - Vec_Plants[idx]->sp_plant->getContentSize().width / 3
			&& Vec_Plants[idx]->sp_plant->getPosition().x <= this->sp_enemy->getPosition().x + Vec_Plants[idx]->sp_plant->getContentSize().width / 3
			&& this->blood > 0 && Vec_Plants[idx]->blood > 0
			&& Vec_Plants[idx]->zombieEat == true) //保证是僵尸吃的植物（排除樱桃、辣椒的卡位）
		{
			this->attack_or_not = true;

			if (pic_attack_idx == 0)
				SimpleAudioEngine::getInstance()->playEffect("SE/chomp.mp3");//播放一次

			CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("zombie1_attack/" + CCString::createWithFormat("%d", pic_attack_idx)->_string + ".png");
			sp_enemy->setTexture(texture);
			pic_attack_idx++;
			if (pic_attack_idx > 20)
				pic_attack_idx = 0; //重置动作帧数

			Vec_Plants[idx]->blood -= 2; //减少植物的血量

			if (Vec_Plants[idx]->blood <= 0 && this->blood > 0) //植物死掉
			{
				this->attack_or_not = false;
			}
		}
	}	

	int lie = ceil((sp_enemy->getPosition().x - 66) / 91);
	//不攻击就移动：1.本僵尸攻击状态为否时移动 2.僵尸所在的行、列没有植物时移动
	if (this->attack_or_not == false || array_PlantOrNot[hang][lie] == false)
	{
		this->attack_or_not = false; //为了让音效不错误播放

		if (pic_idx > 21)
			pic_idx = 0;   //重置

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("res/zombie1_move/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
		sp_enemy->setTexture(texture);

		pic_idx += 1;

		auto acMoveLeft = MoveBy::create(0.1f, Vec2(speed, 0));
		sp_enemy->runAction(acMoveLeft);
	}

}
