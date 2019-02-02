//坚果墙


#include "NutWall.h"
#include "Zombie1.h"

//敌人容器
extern std::vector<Enemy*> Vec_Enemy;      //敌人容器


int NutWall::energy = 50;   //初始化种植该植物所需的能量



NutWall::NutWall()
{
}


NutWall::~NutWall()
{
}

void NutWall::plants_shake(TestScene & mission)
{
	if (pic_idx > 12)
		pic_idx = 0;   //重置

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

void NutWall::plants_attack(TestScene & mission, int hang)  //在特定的模式中坚果墙会有攻击的情况（滚动撵僵尸游戏mode）
{
	//待完成
}

Sprite * NutWall::plants_ini(int hang, int lie)
{
	this->blood = 1000;           //植物自身的血量
	this->type = 3;               //植物种类
	this->hang = hang;            //植物的行
	this->lie = lie;              //植物的列

	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取窗口尺寸
	this->sp_plant = Sprite::create("NutWall/health_0.png");

	if (sp_plant == nullptr)
		exit(-1);  //空指针，加载不到资源报错！

	return sp_plant;
}
