#include <iostream>
#include "Title.h"
#include "Controler.h"
#include "Enemy.h"
#include "Zombie1.h"
#include "Plants.h"
#include "SunFlower.h"
#include "PeaShooter.h"
#include "SnowPea.h"
#include "NutWall.h"
#include "Bullet.h"
#include "CherryBomb.h"
#include "Sun.h"

using namespace std;

std::vector<Enemy*> Vec_Enemy;            //敌人容器
std::vector<Plants*> Vec_Plants;          //植物容器
std::vector<Bullet*> Vec_Bullet;          //子弹容器
std::vector<Sun*> Vec_Sun;                //阳光容器



int Controler::SunValue = 150;        //每个场景的雨露值   切换关卡时清空

bool Controler::UserCanPlant = false;  //允许种植=>否


//行、列从1开始计数，所以数组要大一个数
//数组：该格子上是否有植物存在  false：没有植物 
bool array_PlantOrNot[6][10];



void Controler::rand_change_BG(Sprite* &GameBackGround) //利用随机数更换地图
{
	srand((unsigned int)time(0));
	switch (random(0, 10))
	{
	case 0:
		GameBackGround = Sprite::create("back_ground/game_back_ground_normal.png");  //加载背景
		break;
	case 1:
		GameBackGround = Sprite::create("back_ground/game_back_ground_wedding.png");  //加载背景
		break;
	case 2:
		GameBackGround = Sprite::create("back_ground/game_back_ground_winter.png");  //加载背景
		break;
	case 3:
		GameBackGround = Sprite::create("back_ground/game_back_ground_ice.png");  //加载背景
		break;
	case 4:
		GameBackGround = Sprite::create("back_ground/game_back_ground_sand.png");  //加载背景
		break;
	case 5:
		GameBackGround = Sprite::create("back_ground/game_back_ground_autumn.png");  //加载背景
		break;
	case 6:
		GameBackGround = Sprite::create("back_ground/game_back_ground_halloween.png");  //加载背景
		break;
	case 7:
		GameBackGround = Sprite::create("back_ground/game_back_ground_night.png");  //加载背景
		break;
	case 8:
		GameBackGround = Sprite::create("back_ground/game_back_ground_birthday.png");  //加载背景
		break;
	case 9:
		GameBackGround = Sprite::create("back_ground/game_back_ground_beach.png");  //加载背景
		break;
	case 10:
		GameBackGround = Sprite::create("back_ground/game_back_ground_plane.png");  //加载背景
		break;
	default:
		break;
	}
}

Controler::Controler() //初始化控制器相关
{	
}

//以下为UI总控：
void Controler::drawTestGrid(TestScene & mission) //绘制测试网格
{
	auto sp_grid = Sprite::create("point_test/grid.png");
	sp_grid->setPosition(Point(480, 285));
	mission.addChild(sp_grid, 20);
}

void Controler::addZombieTest(TestScene &mission)
{
	Vec_Enemy.push_back(new Zombie1);
	mission.addChild(Vec_Enemy[Vec_Enemy.size() - 1]->enemy_ini(random(1, 5)), 1);
}


void Controler::createSunFromSky(TestScene &mission)  //公共事件产生天上的阳光
{
	srand((unsigned int)time(0));
	int temp_x = random(70, 900);
	int temp_y = 690;                //阳光从随机位置（x,y）掉落

	auto sun = new Sun(true);    //构造函数初始化的阳光为：(true)来自天空的阳光
	
	Vec_Sun.push_back(sun);
	sun->sp_sun_scroll->setPosition(temp_x, temp_y);

	mission.addChild(sun->sp_sun_scroll, 20);
}

void Controler::sunFallDown() //天上的阳光下落
{
	for (int i = 0; i < Vec_Sun.size(); i++)
	{
		auto pos = Vec_Sun[i]->sp_sun_scroll->getPosition();

		if (Vec_Sun[i]->sun_from_sky == true)  //阳光是否来自天空
		{
			Vec_Sun[i]->sp_sun_scroll->setPosition(Point(pos.x, --pos.y)); //下坠
		}
	}
}

void Controler::sunDisappear(TestScene & mission) //公共事件阳光在7秒后自动消失
{
	for (int i = 0; i < Vec_Sun.size(); i++)
	{
		if (Vec_Sun[i]->timmer_sun_disappear == 80)
		{
			mission.removeChild(Vec_Sun[i]->sp_sun_scroll);
			Vec_Sun.erase(Vec_Sun.begin() + i);
			i--;
		}
	}
}

void Controler::drawPlantIconTable(int count, TestScene & mission, Size winSize)  //绘制植物图标栏用于点选，从而种植植物(一定要修改！把label作为类成员)
{
	for (int idx = 0; idx < count; idx++)  //图形和块
	{
		//以下为label（消耗能量说明）

		if (idx == 0) {//第一个label绘制的值应该等于当前的阳光值
			
		}
		else if (idx == 1) {
			auto label = Label::create(CCString::createWithFormat("%d", SunFlower::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //黑色描边  最后一个参数是透明度
			label->setPosition(Point(winSize.width / 4.7, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 2) {
			auto label = Label::create(CCString::createWithFormat("%d", PeaShooter::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //黑色描边  最后一个参数是透明度
			label->setPosition(Point(winSize.width / 3.25, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 3) {
			auto label = Label::create(CCString::createWithFormat("%d", SnowPea::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //黑色描边  最后一个参数是透明度
			label->setPosition(Point(winSize.width / 2.5, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 4) {
			auto label = Label::create(CCString::createWithFormat("%d", NutWall::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //黑色描边  最后一个参数是透明度
			label->setPosition(Point(477, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 5) {
			auto label = Label::create(CCString::createWithFormat("%d", CherryBomb::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //黑色描边  最后一个参数是透明度
			label->setPosition(Point(567, 572));
			mission.addChild(label, 12);
		}

		//以下为容器和图标
		auto sp_PlantIconTable = Sprite::create("UI/PlantIconTable.png");
		auto sp_Plant = Sprite::create("PlantItemIcon/" + CCString::createWithFormat("%d", idx)->_string + ".png");

		sp_PlantIconTable->setPosition(//容器位置
			Point(20 + (idx + 1)*sp_PlantIconTable->getContentSize().width,
				winSize.height - sp_PlantIconTable->getContentSize().height / 2 - 5));

		sp_Plant->setPosition(//容器中图标位置
			Point(20 + (idx + 1)*sp_PlantIconTable->getContentSize().width,
				winSize.height - sp_PlantIconTable->getContentSize().height / 2 + 2));

		mission.addChild(sp_PlantIconTable, 10);
		mission.addChild(sp_Plant, 11);
	}
}

void Controler::drawSunValue(TestScene *const &mission)//绘制当前关卡的雨露值，放入帧定时器中，每帧回调
{	
	mission->removeChildByTag(223);
	auto label = Label::create(CCString::createWithFormat("%d", Controler::SunValue)->_string, "NewSuperMarioFontU.ttf", 20);
	label->setTag(223);
	label->enableOutline(Color4B(0, 0, 0, 255), 2);  //黑色描边  最后一个参数是透明度
	label->setPosition(Point(113, 572));
	mission->addChild(label, 12);
}

void Controler::drawPlantMask(TestScene & mission)  //绘制植物蒙版（能量不够会使植物变灰）
{
	if (SunValue < SunFlower::energy && !mission.getChildByTag(10))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //植物不可选中的灰色蒙版
		sp_GrayMask->setPosition(Point(201, 595));
		sp_GrayMask->setTag(10);
		mission.addChild(sp_GrayMask, 14);
	}
	else if(SunValue >= SunFlower::energy){
		mission.removeChildByTag(10);
	}

	if (SunValue < PeaShooter::energy && !mission.getChildByTag(11))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //植物不可选中的灰色蒙版
		sp_GrayMask->setPosition(Point(293, 595));
		sp_GrayMask->setTag(11);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= PeaShooter::energy) {
		mission.removeChildByTag(11);
	}

	if (SunValue < SnowPea::energy && !mission.getChildByTag(12))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //植物不可选中的灰色蒙版
		sp_GrayMask->setPosition(Point(384, 595));
		sp_GrayMask->setTag(12);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= SnowPea::energy) {
		mission.removeChildByTag(12);
	}

	if (SunValue < NutWall::energy && !mission.getChildByTag(13))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //植物不可选中的灰色蒙版
		sp_GrayMask->setPosition(Point(475, 595));
		sp_GrayMask->setTag(13);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= NutWall::energy) {
		mission.removeChildByTag(13);
	}

	if (SunValue < CherryBomb::energy && !mission.getChildByTag(14))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //植物不可选中的灰色蒙版
		sp_GrayMask->setPosition(Point(566, 595));
		sp_GrayMask->setTag(14);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= CherryBomb::energy) {
		mission.removeChildByTag(14);
	}
	    
}

void Controler::drawPlantSelectSquare(TestScene & mission, int PlantChoice)  //根据选择的植物，来绘制选择框，让玩家直观地看到选择的是什么植物
{
	auto sp_Selected = Sprite::create("UI/PlantSelected.png");  //选中框
	sp_Selected->setTag(5);

	switch (PlantChoice)
	{
	case 1://删除选框精灵
		CCLOG("Delete selected!");
		mission.removeChildByTag(5);
		break;
	case 2:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected,13); //绘制
		sp_Selected->setPosition(Point(203, 595));
		break;
	case 3:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //绘制
		sp_Selected->setPosition(Point(294, 595));
		break;
	case 4:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //绘制
		sp_Selected->setPosition(Point(385, 595));
		break;
	case 5:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //绘制
		sp_Selected->setPosition(Point(476, 595));
		break;
	case 6:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //绘制
		sp_Selected->setPosition(Point(567, 595));
		break;
	case 7:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //绘制
		sp_Selected->setPosition(Point(658, 595));
		break;
	}
}

/*void Controler::addZombie(TestScene & mission, int *beg, int *end)  //根据每个场景中的僵尸刷新数组，在mission场景中刷新僵尸
{
	while (beg != end)
	{
		switch (*beg)
		{
		case 0:
			break;
		case 1: //普通僵尸
			Vec_Enemy.push_back(new Zombie1);
			mission.addChild(Vec_Enemy[Vec_Enemy.size() - 1]->enemy_ini(random(1, 5)), 1);
			break;
		case 2: //旗子僵尸
			break;
		case 3: //安全帽僵尸
			break;
		case 4: //防盗门僵尸
			break;
		default:
			break;
		}
		beg++;
	}
}
*/


//以下为植物总控：

void Controler::plants_shake_controler(TestScene & mission) //植物摇摆总控 与 阳光滚动帧动画
{
	for (int idx = 0; idx < Vec_Plants.size(); idx++)  //运行时多态 i指向plants不同的子类，他们的shake是多态的
	{
		Vec_Plants[idx]->plants_shake(mission);//植物摇摆
	} 
	//不能用for range循环

	for (Sun *i : Vec_Sun)  //阳光滚动
	{
		i->Sun_Scroll(mission);
	}
}

void Controler::plant_disappear(TestScene & mission) //植物死亡后（空血）清场总控
{
	for (int i = 0; i < Vec_Plants.size(); i++)  //清空血量为0的植物
	{
		if (Vec_Plants[i]->blood <= 0)
		{
			array_PlantOrNot[Vec_Plants[i]->hang][Vec_Plants[i]->lie] = false; //被僵尸吃掉后格子空出来，可以再种植
			mission.removeChild(Vec_Plants[i]->sp_plant);
			Vec_Plants.erase(Vec_Plants.begin() + i);
			i--;
		}
	}
}


//以下为僵尸总控：
void Controler::zombieRecoverSpeed()  //恢复被冰减速僵尸的速度
{
	for (int idx = 0; idx < Vec_Enemy.size(); idx++)
	{
		if (Vec_Enemy[idx]->speed == -0.6)
		{
			Vec_Enemy[idx]->speed = -1.2;  //速度恢复
			CCLOG("%s", "SpeedRecory!");
		}

	}
}

void Controler::zombie_die_animation() //僵尸死亡动画总控
{
	for (int i = 0; i < Vec_Enemy.size(); i++)
	{
		if (Vec_Enemy[i]->blood <= 0 && Vec_Enemy[i]->pic_die_idx <= 9)
		{
			if (Vec_Enemy[i]->pic_die_idx == 0)
				SimpleAudioEngine::getInstance()->playEffect("SE/zombie_falling_1.mp3"); //僵尸到底音效

			Vec_Enemy[i]->sp_enemy->stopAllActions();
			CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("zombie1_down/" + CCString::createWithFormat("%d", Vec_Enemy[i]->pic_die_idx)->_string + ".png");
			Vec_Enemy[i]->sp_enemy->setTexture(texture);
			Vec_Enemy[i]->pic_die_idx++;
		}

		if (Vec_Enemy[i]->pic_die_idx > 9)//僵尸执行所有动画后可以消失
		{
			Vec_Enemy[i]->disappear = true;
		}
	}
}

void Controler::zombie_disappear(TestScene &mission) //僵尸死亡后清场总控
{
	for (int i = 0; i < Vec_Enemy.size(); i++)
	{
		if (Vec_Enemy[i]->disappear == true || Vec_Enemy[i]->ash == true)
		{
			mission.removeChild(Vec_Enemy[i]->sp_enemy);
			Vec_Enemy.erase(Vec_Enemy.begin() + i);
			i--;
		}
	}
}


//以下为游戏总控：
void Controler::eat_brain(TestScene & mission) //吃掉大脑游戏结束
{
	Size winSize = Director::getInstance()->getWinSize();
	for (int i = 0; i < Vec_Enemy.size(); i++)
	{
		static bool Shout_one_time = true; //保证只播放一次喊叫的音效
		static bool disPlay_one_time = true; //保证只显示一次吃脑子图片

		if (Vec_Enemy[i]->sp_enemy->getPosition().x <= -60 && Shout_one_time == true)
		{
			UserCanPlant = false; //收回用户种植植物的权限
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停播BGM
			SimpleAudioEngine::getInstance()->playEffect("SE/scream.mp3");

			Shout_one_time = false;
		}
		if (Vec_Enemy[i]->sp_enemy->getPosition().x <= -100 && disPlay_one_time == true)
		{
			auto sp_eat_brain = Sprite::create("UI/eat_brain.png");
			sp_eat_brain->setPosition(Point(winSize.width / 2, winSize.height / 2));
			mission.addChild(sp_eat_brain, 200);
			disPlay_one_time = false;
		}
		if (Vec_Enemy[i]->sp_enemy->getPosition().x <= -170) //为eat_brain预留足够的时间
		{
			exit(0);
		}
	}
}