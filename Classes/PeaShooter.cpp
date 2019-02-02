//普通豌豆射手

#include "PeaShooter.h"
#include "Bullet.h"
#include "Zombie1.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

extern std::vector<Bullet*> Vec_Bullet;       //子弹容器
extern std::vector<Enemy*> Vec_Enemy;      //敌人容器


int PeaShooter::energy = 100;  //初始化种植该植物所需的能量


PeaShooter::PeaShooter()
{
}


PeaShooter::~PeaShooter()
{
}


Sprite *PeaShooter::plants_ini(int hang, int lie)
{
	this->blood = 100;            //植物自身的血量
	this->type = 1;               //植物种类
	this->hang = hang;            //植物的行
	this->lie = lie;              //植物的列

	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取窗口尺寸
	this->sp_plant = Sprite::create("PeaShooter/0.png");

	if (sp_plant == nullptr)
		exit(-1);  //空指针，加载不到资源报错！

	return sp_plant;
}


void PeaShooter::plants_shake(TestScene &mission)
{
	for (int i = 0; i < Vec_Enemy.size(); i++) {
		if (this->hang == Vec_Enemy[i]->hang                        //植物攻击条件缺一不可：1.僵尸与植物同行 
			&& this->sp_plant->getPosition().x <= Vec_Enemy[i]->sp_enemy->getPosition().x //2.植物在僵尸左边
			&& pic_idx == 3)                                                   //3.植物运动到图片2
		{
			this->plants_attack(mission, hang); //植物攻击
		}
	}
		
	if (pic_idx > 12)
		pic_idx = 0;   //重置

	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("PeaShooter/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
	sp_plant->setTexture(texture);

	pic_idx += 1;

}

void PeaShooter::plants_attack(TestScene &mission, int hang)  //植物攻击
{

	SimpleAudioEngine::getInstance()->playEffect("SE/throw.mp3");//发射音效

	Vec_Bullet.push_back(new Bullet);       //子弹容器
	Vec_Bullet[Vec_Bullet.size() - 1]->bulletInit(this->type, sp_plant->getPosition().x, sp_plant->getPosition().y); //加载普通豌豆弹贴图
	Vec_Bullet[Vec_Bullet.size() - 1]->sp_bullet->setPosition(sp_plant->getPosition().x+15, sp_plant->getPosition().y+15);//设定子弹的坐标
	Vec_Bullet[Vec_Bullet.size() - 1]->hang = hang;


	mission.addChild(Vec_Bullet[Vec_Bullet.size() - 1]->sp_bullet, 100);

	auto acBulMovRight = MoveBy::create(2.2f,Point(900,0));

	Vec_Bullet[Vec_Bullet.size() - 1]->sp_bullet->runAction(acBulMovRight); //加载子弹的运动
	
}