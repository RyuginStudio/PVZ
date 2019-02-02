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

std::vector<Enemy*> Vec_Enemy;            //��������
std::vector<Plants*> Vec_Plants;          //ֲ������
std::vector<Bullet*> Vec_Bullet;          //�ӵ�����
std::vector<Sun*> Vec_Sun;                //��������



int Controler::SunValue = 150;        //ÿ����������¶ֵ   �л��ؿ�ʱ���

bool Controler::UserCanPlant = false;  //������ֲ=>��


//�С��д�1��ʼ��������������Ҫ��һ����
//���飺�ø������Ƿ���ֲ�����  false��û��ֲ�� 
bool array_PlantOrNot[6][10];



void Controler::rand_change_BG(Sprite* &GameBackGround) //���������������ͼ
{
	srand((unsigned int)time(0));
	switch (random(0, 10))
	{
	case 0:
		GameBackGround = Sprite::create("back_ground/game_back_ground_normal.png");  //���ر���
		break;
	case 1:
		GameBackGround = Sprite::create("back_ground/game_back_ground_wedding.png");  //���ر���
		break;
	case 2:
		GameBackGround = Sprite::create("back_ground/game_back_ground_winter.png");  //���ر���
		break;
	case 3:
		GameBackGround = Sprite::create("back_ground/game_back_ground_ice.png");  //���ر���
		break;
	case 4:
		GameBackGround = Sprite::create("back_ground/game_back_ground_sand.png");  //���ر���
		break;
	case 5:
		GameBackGround = Sprite::create("back_ground/game_back_ground_autumn.png");  //���ر���
		break;
	case 6:
		GameBackGround = Sprite::create("back_ground/game_back_ground_halloween.png");  //���ر���
		break;
	case 7:
		GameBackGround = Sprite::create("back_ground/game_back_ground_night.png");  //���ر���
		break;
	case 8:
		GameBackGround = Sprite::create("back_ground/game_back_ground_birthday.png");  //���ر���
		break;
	case 9:
		GameBackGround = Sprite::create("back_ground/game_back_ground_beach.png");  //���ر���
		break;
	case 10:
		GameBackGround = Sprite::create("back_ground/game_back_ground_plane.png");  //���ر���
		break;
	default:
		break;
	}
}

Controler::Controler() //��ʼ�����������
{	
}

//����ΪUI�ܿأ�
void Controler::drawTestGrid(TestScene & mission) //���Ʋ�������
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


void Controler::createSunFromSky(TestScene &mission)  //�����¼��������ϵ�����
{
	srand((unsigned int)time(0));
	int temp_x = random(70, 900);
	int temp_y = 690;                //��������λ�ã�x,y������

	auto sun = new Sun(true);    //���캯����ʼ��������Ϊ��(true)������յ�����
	
	Vec_Sun.push_back(sun);
	sun->sp_sun_scroll->setPosition(temp_x, temp_y);

	mission.addChild(sun->sp_sun_scroll, 20);
}

void Controler::sunFallDown() //���ϵ���������
{
	for (int i = 0; i < Vec_Sun.size(); i++)
	{
		auto pos = Vec_Sun[i]->sp_sun_scroll->getPosition();

		if (Vec_Sun[i]->sun_from_sky == true)  //�����Ƿ��������
		{
			Vec_Sun[i]->sp_sun_scroll->setPosition(Point(pos.x, --pos.y)); //��׹
		}
	}
}

void Controler::sunDisappear(TestScene & mission) //�����¼�������7����Զ���ʧ
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

void Controler::drawPlantIconTable(int count, TestScene & mission, Size winSize)  //����ֲ��ͼ�������ڵ�ѡ���Ӷ���ֲֲ��(һ��Ҫ�޸ģ���label��Ϊ���Ա)
{
	for (int idx = 0; idx < count; idx++)  //ͼ�κͿ�
	{
		//����Ϊlabel����������˵����

		if (idx == 0) {//��һ��label���Ƶ�ֵӦ�õ��ڵ�ǰ������ֵ
			
		}
		else if (idx == 1) {
			auto label = Label::create(CCString::createWithFormat("%d", SunFlower::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //��ɫ���  ���һ��������͸����
			label->setPosition(Point(winSize.width / 4.7, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 2) {
			auto label = Label::create(CCString::createWithFormat("%d", PeaShooter::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //��ɫ���  ���һ��������͸����
			label->setPosition(Point(winSize.width / 3.25, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 3) {
			auto label = Label::create(CCString::createWithFormat("%d", SnowPea::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //��ɫ���  ���һ��������͸����
			label->setPosition(Point(winSize.width / 2.5, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 4) {
			auto label = Label::create(CCString::createWithFormat("%d", NutWall::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //��ɫ���  ���һ��������͸����
			label->setPosition(Point(477, 572));
			mission.addChild(label, 12);
		}
		else if (idx == 5) {
			auto label = Label::create(CCString::createWithFormat("%d", CherryBomb::energy)->_string, "NewSuperMarioFontU.ttf", 20);
			label->enableOutline(Color4B(0, 0, 0, 255), 2);  //��ɫ���  ���һ��������͸����
			label->setPosition(Point(567, 572));
			mission.addChild(label, 12);
		}

		//����Ϊ������ͼ��
		auto sp_PlantIconTable = Sprite::create("UI/PlantIconTable.png");
		auto sp_Plant = Sprite::create("PlantItemIcon/" + CCString::createWithFormat("%d", idx)->_string + ".png");

		sp_PlantIconTable->setPosition(//����λ��
			Point(20 + (idx + 1)*sp_PlantIconTable->getContentSize().width,
				winSize.height - sp_PlantIconTable->getContentSize().height / 2 - 5));

		sp_Plant->setPosition(//������ͼ��λ��
			Point(20 + (idx + 1)*sp_PlantIconTable->getContentSize().width,
				winSize.height - sp_PlantIconTable->getContentSize().height / 2 + 2));

		mission.addChild(sp_PlantIconTable, 10);
		mission.addChild(sp_Plant, 11);
	}
}

void Controler::drawSunValue(TestScene *const &mission)//���Ƶ�ǰ�ؿ�����¶ֵ������֡��ʱ���У�ÿ֡�ص�
{	
	mission->removeChildByTag(223);
	auto label = Label::create(CCString::createWithFormat("%d", Controler::SunValue)->_string, "NewSuperMarioFontU.ttf", 20);
	label->setTag(223);
	label->enableOutline(Color4B(0, 0, 0, 255), 2);  //��ɫ���  ���һ��������͸����
	label->setPosition(Point(113, 572));
	mission->addChild(label, 12);
}

void Controler::drawPlantMask(TestScene & mission)  //����ֲ���ɰ棨����������ʹֲ���ң�
{
	if (SunValue < SunFlower::energy && !mission.getChildByTag(10))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //ֲ�ﲻ��ѡ�еĻ�ɫ�ɰ�
		sp_GrayMask->setPosition(Point(201, 595));
		sp_GrayMask->setTag(10);
		mission.addChild(sp_GrayMask, 14);
	}
	else if(SunValue >= SunFlower::energy){
		mission.removeChildByTag(10);
	}

	if (SunValue < PeaShooter::energy && !mission.getChildByTag(11))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //ֲ�ﲻ��ѡ�еĻ�ɫ�ɰ�
		sp_GrayMask->setPosition(Point(293, 595));
		sp_GrayMask->setTag(11);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= PeaShooter::energy) {
		mission.removeChildByTag(11);
	}

	if (SunValue < SnowPea::energy && !mission.getChildByTag(12))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //ֲ�ﲻ��ѡ�еĻ�ɫ�ɰ�
		sp_GrayMask->setPosition(Point(384, 595));
		sp_GrayMask->setTag(12);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= SnowPea::energy) {
		mission.removeChildByTag(12);
	}

	if (SunValue < NutWall::energy && !mission.getChildByTag(13))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //ֲ�ﲻ��ѡ�еĻ�ɫ�ɰ�
		sp_GrayMask->setPosition(Point(475, 595));
		sp_GrayMask->setTag(13);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= NutWall::energy) {
		mission.removeChildByTag(13);
	}

	if (SunValue < CherryBomb::energy && !mission.getChildByTag(14))
	{
		auto *sp_GrayMask = Sprite::create("UI/GrayMask.png");  //ֲ�ﲻ��ѡ�еĻ�ɫ�ɰ�
		sp_GrayMask->setPosition(Point(566, 595));
		sp_GrayMask->setTag(14);
		mission.addChild(sp_GrayMask, 14);
	}
	else if (SunValue >= CherryBomb::energy) {
		mission.removeChildByTag(14);
	}
	    
}

void Controler::drawPlantSelectSquare(TestScene & mission, int PlantChoice)  //����ѡ���ֲ�������ѡ��������ֱ�۵ؿ���ѡ�����ʲôֲ��
{
	auto sp_Selected = Sprite::create("UI/PlantSelected.png");  //ѡ�п�
	sp_Selected->setTag(5);

	switch (PlantChoice)
	{
	case 1://ɾ��ѡ����
		CCLOG("Delete selected!");
		mission.removeChildByTag(5);
		break;
	case 2:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected,13); //����
		sp_Selected->setPosition(Point(203, 595));
		break;
	case 3:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //����
		sp_Selected->setPosition(Point(294, 595));
		break;
	case 4:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //����
		sp_Selected->setPosition(Point(385, 595));
		break;
	case 5:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //����
		sp_Selected->setPosition(Point(476, 595));
		break;
	case 6:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //����
		sp_Selected->setPosition(Point(567, 595));
		break;
	case 7:
		CCLOG("DRAW SELECTED!");
		mission.addChild(sp_Selected, 13); //����
		sp_Selected->setPosition(Point(658, 595));
		break;
	}
}

/*void Controler::addZombie(TestScene & mission, int *beg, int *end)  //����ÿ�������еĽ�ʬˢ�����飬��mission������ˢ�½�ʬ
{
	while (beg != end)
	{
		switch (*beg)
		{
		case 0:
			break;
		case 1: //��ͨ��ʬ
			Vec_Enemy.push_back(new Zombie1);
			mission.addChild(Vec_Enemy[Vec_Enemy.size() - 1]->enemy_ini(random(1, 5)), 1);
			break;
		case 2: //���ӽ�ʬ
			break;
		case 3: //��ȫñ��ʬ
			break;
		case 4: //�����Ž�ʬ
			break;
		default:
			break;
		}
		beg++;
	}
}
*/


//����Ϊֲ���ܿأ�

void Controler::plants_shake_controler(TestScene & mission) //ֲ��ҡ���ܿ� �� �������֡����
{
	for (int idx = 0; idx < Vec_Plants.size(); idx++)  //����ʱ��̬ iָ��plants��ͬ�����࣬���ǵ�shake�Ƕ�̬��
	{
		Vec_Plants[idx]->plants_shake(mission);//ֲ��ҡ��
	} 
	//������for rangeѭ��

	for (Sun *i : Vec_Sun)  //�������
	{
		i->Sun_Scroll(mission);
	}
}

void Controler::plant_disappear(TestScene & mission) //ֲ�������󣨿�Ѫ���峡�ܿ�
{
	for (int i = 0; i < Vec_Plants.size(); i++)  //���Ѫ��Ϊ0��ֲ��
	{
		if (Vec_Plants[i]->blood <= 0)
		{
			array_PlantOrNot[Vec_Plants[i]->hang][Vec_Plants[i]->lie] = false; //����ʬ�Ե�����ӿճ�������������ֲ
			mission.removeChild(Vec_Plants[i]->sp_plant);
			Vec_Plants.erase(Vec_Plants.begin() + i);
			i--;
		}
	}
}


//����Ϊ��ʬ�ܿأ�
void Controler::zombieRecoverSpeed()  //�ָ��������ٽ�ʬ���ٶ�
{
	for (int idx = 0; idx < Vec_Enemy.size(); idx++)
	{
		if (Vec_Enemy[idx]->speed == -0.6)
		{
			Vec_Enemy[idx]->speed = -1.2;  //�ٶȻָ�
			CCLOG("%s", "SpeedRecory!");
		}

	}
}

void Controler::zombie_die_animation() //��ʬ���������ܿ�
{
	for (int i = 0; i < Vec_Enemy.size(); i++)
	{
		if (Vec_Enemy[i]->blood <= 0 && Vec_Enemy[i]->pic_die_idx <= 9)
		{
			if (Vec_Enemy[i]->pic_die_idx == 0)
				SimpleAudioEngine::getInstance()->playEffect("SE/zombie_falling_1.mp3"); //��ʬ������Ч

			Vec_Enemy[i]->sp_enemy->stopAllActions();
			CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("zombie1_down/" + CCString::createWithFormat("%d", Vec_Enemy[i]->pic_die_idx)->_string + ".png");
			Vec_Enemy[i]->sp_enemy->setTexture(texture);
			Vec_Enemy[i]->pic_die_idx++;
		}

		if (Vec_Enemy[i]->pic_die_idx > 9)//��ʬִ�����ж����������ʧ
		{
			Vec_Enemy[i]->disappear = true;
		}
	}
}

void Controler::zombie_disappear(TestScene &mission) //��ʬ�������峡�ܿ�
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


//����Ϊ��Ϸ�ܿأ�
void Controler::eat_brain(TestScene & mission) //�Ե�������Ϸ����
{
	Size winSize = Director::getInstance()->getWinSize();
	for (int i = 0; i < Vec_Enemy.size(); i++)
	{
		static bool Shout_one_time = true; //��ֻ֤����һ�κ��е���Ч
		static bool disPlay_one_time = true; //��ֻ֤��ʾһ�γ�����ͼƬ

		if (Vec_Enemy[i]->sp_enemy->getPosition().x <= -60 && Shout_one_time == true)
		{
			UserCanPlant = false; //�ջ��û���ֲֲ���Ȩ��
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //ͣ��BGM
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
		if (Vec_Enemy[i]->sp_enemy->getPosition().x <= -170) //Ϊeat_brainԤ���㹻��ʱ��
		{
			exit(0);
		}
	}
}