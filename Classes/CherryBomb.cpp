#include "CherryBomb.h"
#include "Zombie1.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

extern std::vector<Enemy*> Vec_Enemy;        //��������


int CherryBomb::energy = 150;          //��ֲ��������150


CherryBomb::CherryBomb()
{
}

CherryBomb::~CherryBomb()
{
}

void CherryBomb::plants_attack(TestScene & mission, int hang)
{	
	SimpleAudioEngine::getInstance()->playEffect("SE/cherrybomb.mp3");
	
	sp_bomb = Sprite::create("CherryBomb/CherryBomb.png"); //"�"����ͼƬ
	sp_bomb->setName("CherryBomb");
	mission.addChild(sp_bomb, 3);
	sp_bomb->setPosition(this->sp_plant->getPosition());
	

	for (int i = 0; i < Vec_Enemy.size(); i++) //����3*3�����ڵĽ�ʬ
	{
		if (abs(Vec_Enemy[i]->hang - this->hang) < 2 
			&& abs(Vec_Enemy[i]->sp_enemy->getPosition().x - sp_plant->getPosition().x) < 139 
			&& Vec_Enemy[i]->blood > 0) //��Ѫ��Ϊ0 => �Ѿ������������䶯���Ľ�ʬ�����в���
		{
			Texture2D *texture = TextureCache::sharedTextureCache()->addImage("ZombieAshes/zombie1Ash.png");
			Vec_Enemy[i]->sp_enemy->setTexture(texture);
			Vec_Enemy[i]->ash = true;  //��ʬתΪ�ҽ�״̬
		}
	}

	this->blood = 0;  //֡��ʱ���еĺ������Զ�����bloodΪ0��ֲ��

	mission.scheduleOnce(schedule_selector(TestScene::update_once), .8f);  //.8f��ɾ����࣡�ͼ
}


void CherryBomb::plants_shake(TestScene & mission) //����CCTEXTURE2d����ͼƬ
{
	pic_idx += 1;

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("CherryBomb/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
	sp_plant->setTexture(texture);

	if (pic_idx == 6)
	{
		this->plants_attack(mission, hang);
	}
}


Sprite * CherryBomb::plants_ini(int hang, int lie)  //ֲ���ʼ��
{
	this->hang = hang;            //ֲ�����
	this->lie = lie;              //ֲ�����
	this->blood = 100;            //ֲ��Ѫ��

	this->zombieEat = false;      //��ʬ����ӣ��ը��

	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���ڳߴ�
	this->sp_plant = Sprite::create("CherryBomb/0.png");

	if (sp_plant == nullptr)
		exit(-1);  //��ָ�룬���ز�����Դ����

	return sp_plant;
}