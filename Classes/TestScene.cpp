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

extern std::vector<Enemy*> Vec_Enemy;         //��������
extern std::vector<Plants*> Vec_Plants;       //ֲ������
extern std::vector<Bullet*> Vec_Bullet;       //�ӵ�����
extern std::vector<Sun*> Vec_Sun;             //��������

Sprite *GameBackGround;  //��Ϸ��������

//�С��д�1��ʼ��������������Ҫ��һ����
//���飺�ø������Ƿ���ֲ�����  false��û��ֲ�� 
extern bool array_PlantOrNot[6][10];


//���õ�ǰ��ѡ����ѡ�е�ֲ��
int PlantChoice = 0; //0=>�� 

 
//��ʼ���ض�����ֲ�����ѡ���
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
							  { 1,1,1,1,1 } };  //��ʬ���飬4����ʬ  => �Ѵ����鴫��Controler�еľ�̬��Ա����


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

	Size winSize = Director::getInstance()->getWinSize(); //��ȡ��ǰ���ڳߴ�

	//Controler::drawTestGrid(*this); //���Ʋ�������

	if (!Layer::init())
	{
		return false;
	}

	//���ش���ģ��
	setTouchEnabled(true);
	//����Ϊ���㴥��
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	Controler::rand_change_BG(GameBackGround);  //���������������ͼ
	
	GameBackGround->setScale(.75f, .75f);
	GameBackGround->setPosition(Point(570, 320));

	
	this->addChild(GameBackGround);

	this->scheduleOnce(schedule_selector(TestScene::update_2_5), 2.5f);       //��ͼ��ʾ2.5���ʼ����
	
	return true;
}

void TestScene::update(float dt) //֡��ʱ����ÿ֡ˢ��
{ 
	Controler::sunDisappear(*this);    //������δʰ����������ʧ
	Controler::plant_disappear(*this); //ֲ�������󣨿�Ѫ���峡
	Bullet::bullet_bomb_collision();   //�ӵ���ײ����Լ�ը��ͼƬ����
	Controler::drawPlantMask(*this);   //����ֲ���ɰ棨����������ʹֲ���ң�
	Controler::drawSunValue(this);     //���Ƶ�ǰ�ؿ�����¶ֵ������֡��ʱ���У�ÿ֡�ص�
	Controler::sunFallDown();          //�������ϵ���������������

	Controler::eat_brain(*this);       //�Ե�������Ϸ����
}

void TestScene::update_winScroll(float dt)  //����0.1s��ʱ�����ڻ������
{
	auto winSize = Director::getInstance()->getWinSize();

	//��Ҫ���������жϣ����򵥸�ִ�е�ʱ�������˶�ʱ����ˢ��ʱ�䣬�ᵼ�¶�ʱ�������࿪
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
	
		auto act_scale = ScaleTo::create(2.f, 1.0f, 1.0f);  //�Ա���ͼƬ����x,y������춯��(��,x,y)
		auto act_moveSP = MoveTo::create(2.f, Point(570, 350));

		auto act_spawn = Spawn::create(act_scale, act_moveSP, NULL); //Sequence��϶�������������ͬʱִ��
		GameBackGround->runAction(act_spawn); //ִ����϶���

		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Grasswalk_low_quality.mp3", true);   //BGM
		
	    //CCLOG("background's position x,y is: %d %d", int(GameBackGround->getPosition().x), int(GameBackGround->getPosition().y));
		
		this->unschedule(schedule_selector(TestScene::update_winScroll));  //�رն�ʱ��
		this->scheduleUpdate();//����֡��ʱ��
		this->schedule(schedule_selector(TestScene::update_0_1),0.1f);       //����0.1s��ʱ��
		this->schedule(schedule_selector(TestScene::update_0_1_5), 0.15f);   //����0.15S��ʱ��
		this->schedule(schedule_selector(TestScene::update_1_5), 1.5f);      //����1.5S��ʱ��
		this->schedule(schedule_selector(TestScene::update_4), 4.f);         //����4.s��ʱ��
		this->schedule(schedule_selector(TestScene::update_6), 6.f);         //����6.S��ʱ��

		Controler::UserCanPlant = true;  //������ֲ
		Controler::drawPlantIconTable(PlantKinds, *this, winSize);   //����ֲ��ͼ����
	}
}

void TestScene::update_0_1(float dt) //�붨ʱ��
{
	Controler::plants_shake_controler(*this);  //ֲ��ҡ���ܿ�

	for (int i = 0; i < Vec_Enemy.size(); i++)
	{
		if(Vec_Enemy[i]->blood > 0)
			Vec_Enemy[i]->enemy_move_attack();//��ʬ�ƶ�|����
	}
	
}

void TestScene::update_0_1_5(float dt) //0.15s��ʱ��
{
	Bullet::bulletRemove(*this);//�����ӵ���
	Controler::zombie_die_animation(); //��ʬ���������ܿ�
}

void TestScene::update_1_5(float dt)//1.5s��ʱ��
{
	Controler::zombie_disappear(*this); //��ʬ1�������峡
}

void TestScene::update_2_5(float dt) //��Ϸ��ʼ2.5���ִ�л������
{  
	this->schedule(schedule_selector(TestScene::update_winScroll), 0.01f); //����0.1s��ʱ�����ڻ������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/ChooseYourSeeds.mp3");          //4��󲥷�BGM
}

void TestScene::update_4(float dt)  //4�붨ʱ�� ���ڲ������ϵ�����
{
	Controler::createSunFromSky(*this);
	Controler::addZombieTest(*this);
}

void TestScene::update_6(float dt)//6s��ʱ��
{
	Controler::zombieRecoverSpeed(); //�ָ��������ٽ�ʬ���ٶ�
}

void TestScene::update_once(float dt) //ɾ����ӣ��ը�����ͼ��
{
	if(this->getChildByName("CherryBomb"))
		removeChildByName("CherryBomb");

	if (this->getChildByName("CherryBomb"))
		removeChildByName("CherryBomb");

	if (this->getChildByName("CherryBomb"))
		removeChildByName("CherryBomb");
}

bool TestScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event) //��������
{
	double Pos_x = touch->getLocation().x;
	double Pos_y = touch->getLocation().y;
	CCLOG("x:%lf    y:%lf", Pos_x, Pos_y); //���������굥����x��y����
	
	for (int i = 0; i < Vec_Sun.size(); ++i)  //�������е����� => ��ȡ����
	{	
		if (Vec_Sun[i]->sp_sun_scroll->getBoundingBox().containsPoint(touch->getLocation()) && Controler::UserCanPlant == true) //�жϴ������Ƿ���Ŀ��ķ�Χ��
		{
			Controler::SunValue += 25;
			SimpleAudioEngine::getInstance()->playEffect("SE/points.mp3");
			this->removeChild(Vec_Sun[i]->sp_sun_scroll); //ɾ������
			Vec_Sun.erase(Vec_Sun.begin() + i);
			--i;
			return true;   //1.��ֹһ�´����յ���������(�˴��൱��break)���ǹ��ܸ����� => 2.��ֹ�������ͬʱ��ѡֲ��
		}
	}


	/*��������Ϊ��66   �²����߶�Ϊ��18
	���Ӻ�����Ϊ��91  ��������߶�Ϊ��106*/
	int Grid_x = ceil((Pos_x - 66) / 91); 
	int Grid_y = ceil((Pos_y - 18) / 106);//ceil() ����ȡ��
	int x = ceil(Grid_x), y = ceil(Grid_y);
	CCLOG("you set the position is in (%d, %d)", Grid_x, Grid_y);

	if (Grid_y == 6 && Controler::UserCanPlant == true && Grid_x <= PlantKinds)  //��괦��ֲ��ѡ����
	{
		switch (Grid_x)
		{
		case 2: //(6,2)���տ�
		{
			if (PlantChoice != 2 && Controler::SunValue >= SunFlower::energy) //֮ǰѡ��Ĳ���2��������ֵ���ã����л�ѡ��
			{
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 2;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //����ѡ�е�ֲ�����ѡ���
			}
			else if(PlantChoice == 2)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//ѡ��գ��Ż�ֲ��
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
			}
			break;
		}			
		case 3: //(6,3)�㶹����
		{
			if (PlantChoice != 3 && Controler::SunValue >= PeaShooter::energy)
			{
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 3;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //����ѡ�е�ֲ�����ѡ���
			}
			else if(PlantChoice == 3)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//ѡ��գ��Ż�ֲ��
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
			}
			break;
		}			
		case 4: //(6,4)��������
		{
			if (PlantChoice != 4 && Controler::SunValue >= SnowPea::energy)  
			{
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 4;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //����ѡ�е�ֲ�����ѡ���
			}
			else if(PlantChoice == 4)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//ѡ��գ��Ż�ֲ��
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
			}
			break;
		}
		case 5: //(6,5)���ǽ
		{
			if (PlantChoice != 5 && Controler::SunValue >= NutWall::energy)
			{
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 5;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //����ѡ�е�ֲ�����ѡ���
			}
			else if(PlantChoice == 5)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//ѡ��գ��Ż�ֲ��
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
			}
			break;
		}
		case 6: //(6,6)ӣ��ը��
		{
			if (PlantChoice != 6 && Controler::SunValue >= CherryBomb::energy)
			{
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
				SimpleAudioEngine::getInstance()->playEffect("SE/getSeed.mp3");
				PlantChoice = 6;
				Controler::drawPlantSelectSquare(*this, PlantChoice);  //����ѡ�е�ֲ�����ѡ���
			}
			else if (PlantChoice == 6)
			{
				SimpleAudioEngine::getInstance()->playEffect("SE/touchTabel.mp3");
				PlantChoice = 1;//ѡ��գ��Ż�ֲ��
				Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
			}
			break;
		}
		case 7: //(6,7)������
		{
			
			break;
		}
		}			
	}
	
	if (Grid_x > 0 && Grid_x < 10 && Grid_y > 0 && Grid_y < 6 && array_PlantOrNot[Grid_y][Grid_x] == false && Controler::UserCanPlant == true) //�������û���ֲ
	{
		addNewSpriteAtPosition(Point((Grid_x - 1) * 91 + 114, (Grid_y - 1) * 106 + 74), Grid_y, Grid_x);  //ֻ��Ϊ���Ӿ��϶���
		Controler::drawPlantSelectSquare(*this, 1);  //ɾ����
	}
	return false;
}

void TestScene::addNewSpriteAtPosition(cocos2d::Point p, int hang, int lie)  //��ֲֲ��
{

	switch (PlantChoice)
	{
	case 1: //ʲô��ûѡ��
	{
		break;
	}
	case 2: //ѡ�����տ�
	{
		Vec_Plants.push_back(new SunFlower);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//��ֲ��Ч
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(p);
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= SunFlower::energy; //��ֲ����¶ֵ����
		PlantChoice = 1; //���ѡ�е�ֲ��
		break;
	}
	case 3: //ѡ����ͨ�㶹����
	{
		Vec_Plants.push_back(new PeaShooter);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//��ֲ��Ч
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(p);
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= PeaShooter::energy; //��ֲ����¶ֵ����
		PlantChoice = 1; //���ѡ�е�ֲ��
		break;
	}
	case 4: //ѡ�м����㶹����
	{
		Vec_Plants.push_back(new SnowPea);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//��ֲ��Ч
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(p);
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= SnowPea::energy; //��ֲ����¶ֵ����
		PlantChoice = 1; //���ѡ�е�ֲ��
		break;
	}
	case 5: //ѡ�м��ǽ
	{
		Vec_Plants.push_back(new NutWall);
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//��ֲ��Ч
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie));
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(Point(p.x, p.y+7));
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= NutWall::energy; //��ֲ����¶ֵ����
		PlantChoice = 1; //���ѡ�е�ֲ��
		break;
	}
	case 6: //ѡ��ӣ��ը��
	{
		Vec_Plants.push_back(new CherryBomb());
		SimpleAudioEngine::getInstance()->playEffect("SE/plant.mp3");//��ֲ��Ч
		this->addChild(Vec_Plants[Vec_Plants.size() - 1]->plants_ini(hang, lie),2);
		Vec_Plants[Vec_Plants.size() - 1]->sp_plant->setPosition(Point(p.x, p.y + 7)); //����ͼƬλ��
		array_PlantOrNot[hang][lie] = true;
		Controler::SunValue -= CherryBomb::energy; //��ֲ����¶ֵ����
		PlantChoice = 1; //���ѡ�е�ֲ��
		break;
	}
	}
}