#include "Bullet.h"
#include "Zombie1.h"
#include <vector>


extern std::vector<Bullet*> Vec_Bullet;       //子弹容器
extern std::vector<Enemy*> Vec_Enemy;         //敌人容器

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::bulletInit(int bullet_type, int posBgnX, int posBgnY)
{
	this->disappear = false;           //初始化子弹不处于消失的状态
	this->bullet_type = bullet_type;   //传值给子弹类型属性

	this->Pos_begin_x = posBgnX;       //子弹初始坐标（发射该子弹的植物的坐标）
	this->Pos_begin_y = posBgnY;

	switch (bullet_type)
	{
	case 1: //豌豆弹  效果：中规中矩
	{
		this->demage = 5;
		sp_bullet = Sprite::create("bullet/1.png");
		break;
	}	
	case 2: //冰冻弹  效果：使敌人减速，故伤害值低
	{
		this->demage = 3;
		sp_bullet = Sprite::create("bullet/2.png");
		break;
	}
	case 3: //终极火焰弹
	{
		this->demage = 25;
		break;
	}
	case 4:
	{

		break;
	}
	}
	
}

void Bullet::bulletRemove(TestScene & mission) //回收废弃子弹
{
	for (int idx = 0; idx < Vec_Bullet.size(); idx++)
	{
		if (Vec_Bullet[idx]->disappear == true)
		{
			mission.removeChild(Vec_Bullet[idx]->sp_bullet);   //擦除弹壳图片

            //擦除碰撞到的那个！而非第一个，因为有后面种植的植物产生的子弹先碰撞到僵尸的情况！
			Vec_Bullet.erase(Vec_Bullet.begin() + idx);
			idx--;
		}

	}
}

void Bullet::bullet_bomb_collision() //子弹碰撞检测以及炸裂图片更换
{
	for (Bullet *i : Vec_Bullet)
	{
		for (int j = 0; j < Vec_Enemy.size(); j++)
		{
			if (Vec_Enemy[j]->ash == true | Vec_Enemy[j]->blood <= 0 | Vec_Enemy[j]->sp_enemy->getPosition().x < i->Pos_begin_x) //灰烬状态、坐标小于子弹初始坐标、空血 => 排除掉这个僵尸
				continue;
			if (i->disappear == true)
				break;

			if (i->hang == Vec_Enemy[j]->hang //僵尸与子弹同行 
				&&i->disappear == false //子弹不处于消失状态
				&& i->sp_bullet->getPosition().x >= Vec_Enemy[j]->sp_enemy->getPosition().x //撞上或者穿过
				) //满足以上，则发生碰撞
			{
				Vec_Enemy[j]->blood -= i->demage;  //僵尸伤血

				CCLOG("%d", Vec_Enemy[j]->blood);
				SimpleAudioEngine::getInstance()->playEffect("SE/splat2.mp3"); //打击音效
			
				CCTexture2D* texture = CCTextureCache::sharedTextureCache()->
					addImage("bullet/" + CCString::createWithFormat("%d", i->bullet_type)->_string + "_bomb.png");//匹配相应的子弹碎片

				i->sp_bullet->setTexture(texture);

				i->sp_bullet->stopAllActions();

				i->disappear = true;

				if (i->bullet_type == 2)  //如果是减速弹改变减速移速
				{
					Vec_Enemy[j]->speed = -0.6;
					CCLOG("%s", "slowDown!");
				}
			}
		}
	}
}
