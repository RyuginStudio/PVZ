#include <vector>
#include "TestScene.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "Controler.h"
#include "Zombie1.h"
#include "Enemy.h"
#include "SunFlower.h"
#include "PeaShooter.h"
#include "SnowPea.h"
#include "NutWall.h"
#include "CherryBomb.h"
#include "Plants.h"
#include "Bullet.h"
#include "Sun.h"

USING_NS_CC;

using namespace std;
using namespace CocosDenshion;
using namespace cocostudio::timeline;

extern std::vector<Enemy*> Vec_Enemy;         //敌人容器
extern std::vector<Plants*> Vec_Plants;       //植物容器
extern std::vector<Bullet*> Vec_Bullet;       //子弹容器
extern std::vector<Sun*> Vec_Sun;             //阳光容器

Sprite *GameBackGround;  //游戏背景界面

//行、列从1开始计数，所以数组要大一个数
//数组：该格子上是否有植物存在  false：没有植物 
extern bool array_PlantOrNot[6][10];


//设置当前在选择栏选中的植物
int PlantChoice = 0; //0=>空 

 
//初始加载多少种植物（绘制选择框）
int PlantKinds = 7;



Scene* TestScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TestScene::create();

	scene->addChild(layer);

	return scene;
}

bool TestScene::init()
{
	srand((unsigned int)time(0));

	/*int ZombieGroup[4][5] = { { 1 },
	                          { 1,1 },
							  { 1,1,1 },
							  { 1,1,1,1,1 } };  //僵尸数组，4波僵尸  => 把此数组传给Controler中的静态成员函数


	Controler::addZombie(*this, &ZombieGroup[0][0], &ZombieGroup[3][4]); */

	auto sp_temp1 = Sprite::create("zombie1_move/4.png");
	auto sp_temp2 = Sprite::create("zombie1_move/7.png");
	auto sp_temp3 = Sprite::create("zombie1_move/2.png");
	auto sp_temp4 = Sprite::create("zombie1_move/20.png");
	auto sp_temp5 = Sprite::create("zombie1_move/16.png");

	sp_temp1->setScale(.75f, .75f);
	sp_temp1->setPosition(1000, 450);
	addChild(sp_temp1, 5);

	sp_temp2->setScale(.75f, .75f);
	sp_temp2->setPosition(1111, 350);
	addChild(sp_temp2, 5);

	sp_temp3->setScale(.75f, .75f);
	sp_temp3->setPosition(1200, 390);
	addChild(sp_temp3, 5);

	sp_temp4->setScale(.75f, .75f);
	sp_temp4->setPosition(980, 320);
	addChild(sp_temp4, 5);

	sp_temp5->setScale(.75f, .75f);
	sp_temp5->setPosition(1100, 270);
	addChild(sp_temp5, 5);

	Size winSize = Director::getInstance()->getWinSize(); //获取当前窗口尺寸

	//Controler::drawTestGrid(*this); //绘制测试网格

	if (!Layer::init())
	{
		return false;
	}

	//加载触控模块
	setTouchEnabled(true);
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	Controler::rand_change_BG(GameBackGround);  //利用随机数更换地图
	
	GameBackGround->setScale(.75f, .75f);
	GameBackGround->setPosition(Point(570, 320));

	
	this->addChild(GameBackGround);

	this->scheduleOnce(schedule_selector(TestScene::update_2_5), 2.5f);       //地图显示2.5秒后开始滚屏
	
	return true;
}

void TestScene::update(float dt) //帧定时器，每帧刷新
{ 
	Controler::sunDisappear(*this);    //阳光在未拾起的七秒后消失
	Controler::plant_disappear(*this); //植物死亡后（空血）清场
	Bullet::bullet_bomb_collision();   //子弹碰撞检测以及炸裂图片更换
	Controler::drawPlantMask(*this);   //绘制植物蒙版（能量不够会使植物变灰）
	Controler::drawSunValue(this);     //绘制当前关卡的雨露值，放入帧定时器中，每帧回调
	Controler::sunFallDown();          //来自天上的阳光受重力下落

	Controler::eat_brain(*this);       //吃掉大脑游戏结束
}

void TestScene::update_winScroll(float dt)  //加载0.1s定时器用于画面滚动
{
	auto winSize = Director::getInstance()->getWinSize();

	//需要条件进行判断，否则单个执行的时长超过了定时器的刷新时间，会导致定时器函数多开
	static bool move_left = true;
	static bool move_right = true;
	static bool scale_move = true;  
	
	Layer *parent = (Layer *)getParent();
	static int temp_x = parent->getPosition().x;
	//CCLOG("layer's x is: %d", temp_x);
	static int temp_y = parent->getPosition().y;

	if(temp_x <= 255 && move_left == true)
		parent->setPosition(Point(++temp_x, temp_y));

	else if(temp_x > -436 && move_right == true)
	{
		move_left = false;
		parent->setPosition(Point(--temp_x, temp_y));
	}
	else if(temp_x != 0)
	{		
		move_right = false;
		if (temp_x != 0)
		parent->setPosition(Point(++temp_x, temp_y));
	}
	else if(scale_move == true)
	{
		scale_move = false;

		parent->setPosition(Point(0, 0));
		//CCLOG("background's position y is: %d", int(GameBackGround->getPosition().y));
	
		auto act_scale = ScaleTo::create(2.f, 1.0f, 1.0f);  //对背景图片进行x,y轴的拉伸动作(秒,x,y)
		auto act_moveSP = MoveTo::create(2.f, Point(570, 350));

		auto act_spawn = Spawn::create(act_scale, act_moveSP, NULL); //Sequence组合动作，两个动作同时执行
		GameBackGround->runAction(act_spawn); //执行组合动作

		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Grasswalk_low_quality.mp3", true);   //BGM
		
	    //CCLOG("background's position x,y is: %d %d", int(GameBackGround->getPosition().x), int(GameBackGround->getPosition().y));
		
		this->unschedule(schedule_selector(TestScene::update_winScroll));  //关闭定时器
		this->scheduleUpdate();//加载帧定时器
		this->schedule(schedule_selector(TestScene::update_0_1),0.1f);       //加载0.1s定时器
		this->schedule(schedule_selector(TestScene::update_0_1_5), 0.15f);   //加载0.15S定时器
		this->schedule(schedule_selector(TestScene::update_1_5), 1.5f);      //加载1.5S定时器
		this->schedule(schedule_selector(TestScene::update_4), 4.f);         //加载4.s定时器
		this->schedule(schedule_selector(TestScene::update_6), 6.f);         //加载6.S定时器

		Controler::UserCanPlant = true;  //允许种植
		Controler::drawPlantIconTable(PlantKinds, *this, winSize);   //绘制植物图标栏
	}
}

void TestScene::update_0_1(float dt) //秒定时器
{
	Controler::plants_shake_controler(*this);  //植物摇摆总控

	for (int i = 0; i < Vec_Enemy.size(); i++)
	{
		if(Vec_Enemy[i]->blood > 0)
			Vec_Enemy[i]->enemy_move_attack();//僵尸移动|攻击
	}
	
}

void TestScene::update_0_1_5(float dt) //0.15s定时器
{
	Bullet::bulletRemove(*this);//回收子弹壳
	Controler::zombie_die_animation(); //僵尸死亡动画总控
}

void TestScene::update_1_5(float dt)//1.5s定时器
{
	Controler::zombie_disappear(*this); //僵尸1死亡后清场
}

void TestScene::update_2_5(float dt) //游戏开始2.5秒后执行画面滚动
{  
	this->schedule(schedule_selector(TestScene::update_winScroll), 0.01f); //加载0.1s定时器用于画面滚动
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/ChooseYourSeeds.mp3");          //4秒后播放BGM
}

void TestScene::update_4(float dt)  //4秒定时器 用于产生天上的阳光
{
	Controler::createSunFromSky(*this);
	Controler::addZombieTest(*this);
}

void TestScene::update_6(float dt)//6s定时器
{
	Controler::zombieRecoverSpeed(); //恢复被冰减速僵尸的速度
}

void TestScene::update_once(float dt) //删除“樱桃炸弹的啵图”
{
	if(this->getChildByName("CherryBomb"))
		removeChildByName("CherryBomb");

	if (this->getChildByName("CherryBomb"))
		removeChildByName("CherryBomb");

	if (this->getChildByName("CherryBomb"))
		removeChildByName("CherryBomb");
}

bool TestScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event) //触摸函数
{
	double Pos_x = touch->getLocation().x;
	double Pos_y = touch->getLocation().y;
	CCLOG("x:%lf    y:%lf", Pos_x, Pos_y); //调试输出鼠标单击的x，y坐标
	
	for (int i = 0; i < Vec_Sun.size(); ++i)  //遍历所有的阳光 => 收取阳光
	{	
		if (Vec_Sun[i]->sp_sun_scroll->getBoundingBox().containsPoint(touch->getLocation()) && Controler::UserCanPlant == true) //判断触摸点是否在目标的范围内
		{
			Controler::SunValue += 25;
			SimpleAudioEngine::getInstance()->playEffect("SE/points.mp3");
			this->removeChild(Vec_Sun[i]->sp_sun_scroll); //删除阳光
			Vec_Sun.erase(Vec_Sun.begin() + i);
			--i;
			return true;   //1.防止一下触摸收掉两个阳光(此处相当于break)但是功能更完善 => 2.防止收阳光的同时点选植物
		}
	}


	/*左侧距离宽度为：66   下侧距离高度为：18
	格子横向宽度为：91  格子纵向高度为：106*/
	int Grid_x = ceil((Pos_x - 66) / 91); 
	int Grid_y = ceil((Pos_y - 18) / 106);//ceil() 向上取整
	int x = ceil(Grid_x), y = ceil(Grid_y);
	CCLOG("you set the position is in (%d, %d)", Grid_x, Grid_y);

	if (Grid_y == 6 && Controler::UserCanPlant == true && Grid_x <= PlantKinds)  //鼠标处于植物选择行
	{
		switch (Grid_x)
		{
		case 2: //(6,2)向日葵
		{
			if (PlantChoice != 2 && Controler::SunValue >= SunFlower::energy) //之前选择的不是2，且能量值够用，就切换选择
			{
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 2;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //根据选中的植物绘制选择框
			}
			else if(PlantChoice == 2)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//选择空，放回植物
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
			}
			break;
		}			
		case 3: //(6,3)豌豆射手
		{
			if (PlantChoice != 3 && Controler::SunValue >= PeaShooter::energy)
			{
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 3;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //根据选中的植物绘制选择框
			}
			else if(PlantChoice == 3)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//选择空，放回植物
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
			}
			break;
		}			
		case 4: //(6,4)寒冰射手
		{
			if (PlantChoice != 4 && Controler::SunValue >= SnowPea::energy)  
			{
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 4;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //根据选中的植物绘制选择框
			}
			else if(PlantChoice == 4)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//选择空，放回植物
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
			}
			break;
		}
		case 5: //(6,5)坚果墙
		{
			if (PlantChoice != 5 && Controler::SunValue >= NutWall::energy)
			{
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 5;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //根据选中的植物绘制选择框
			}
			else if(PlantChoice == 5)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//选择空，放回植物
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
			}
			break;
		}
		case 6: //(6,6)樱桃炸弹
		{
			if (PlantChoice != 6 && Controler::SunValue >= CherryBomb::energy)
			{
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 6;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //根据选中的植物绘制选择框
			}
			else if (PlantChoice == 6)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//选择空，放回植物
				Controler::drawPlantSelectSquare(*this, 1);  //删除框
			}
			break;
		}
		case 7: //(6,7)土豆雷
		{
			
			break;
		}
		}			
	}
	
	if (Grid_x > 0 && Grid_x < 10 && Grid_y > 0 && Grid_y < 6 && array_PlantOrNot[Grid_y][Grid_x] == false && Controler::UserCanPlant == true) //且允许用户种植
	{
		addNewSpriteAtPosition(Point((Grid_x - 1) * 91 + 114, (Grid_y - 1) * 106 + 74), Grid_y, Grid_x);  //只是为了视觉上对齐
		Controler::drawPlantSelectSquare(*this, 1);  //删除框
	}
	return false;
}

void TestScene::addNewSpriteAtPosition(cocos2d::Point p, int hang, int lie)  //种植植物
{

	switch (PlantChoice)
	{
	case 1: //什么都没选中
	{
		break;
	}
	case 2: //选中向日葵
	{
		Vec_Plants.push_back(new SunFlower);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//种植音效
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(p);
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= SunFlower::energy; //种植后雨露值减少
		PlantChoice = 1; //清空选中的植物
		break;
	}
	case 3: //选中普通豌豆射手
	{
		Vec_Plants.push_back(new PeaShooter);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//种植音效
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(p);
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= PeaShooter::energy; //种植后雨露值减少
		PlantChoice = 1; //清空选中的植物
		break;
	}
	case 4: //选中减速豌豆射手
	{
		Vec_Plants.push_back(new SnowPea);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//种植音效
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(p);
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= SnowPea::energy; //种植后雨露值减少
		PlantChoice = 1; //清空选中的植物
		break;
	}
	case 5: //选中坚果墙
	{
		Vec_Plants.push_back(new NutWall);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//种植音效
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(Point(p.x, p.y+7));
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= NutWall::energy; //种植后雨露值减少
		PlantChoice = 1; //清空选中的植物
		break;
	}
	case 6: //选中樱桃炸弹
	{
		Vec_Plants.push_back(new CherryBomb());
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//种植音效
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie),2);
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(Point(p.x, p.y + 7)); //修正图片位置
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= CherryBomb::energy; //种植后雨露值减少
		PlantChoice = 1; //清空选中的植物
		break;
	}
	}
}