//�����㶹����


#include "SnowPea.h"
#include "Bullet.h"
#include "Zombie1.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

extern std::vector<Bullet*> Vec_Bullet;       //�ӵ�����
extern std::vector<Enemy*> Vec_Enemy;         //��������

int SnowPea::energy = 175;         //��ʼ����ֲ����ֲ�����������


SnowPea::SnowPea()
{
}


SnowPea::~SnowPea()
{
}

Sprite * SnowPea::plants_ini(int hang, int lie)
{
	this->blood = 100;            //ֲ��������Ѫ��
	this->type = 2;               //ֲ������
	this->hang = hang;            //ֲ�����
	this->lie = lie;              //ֲ�����

	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���ڳߴ�
	this->sp_plant = Sprite::create("SnowPea/0.png");

	if (sp_plant == nullptr)
		exit(-1);  //��ָ�룬���ز�����Դ������

	return sp_plant;
}


void SnowPea::plants_shake(TestScene &mission)
{
	for (int i = 0; i < Vec_Enemy.size(); i++) {
		if (this->hang == Vec_Enemy[i]->hang                        //ֲ�﹥������ȱһ���ɣ�1.��ʬ��ֲ��ͬ�� 
			&& this->sp_plant->getPosition().x <= Vec_Enemy[i]->sp_enemy->getPosition().x //2.ֲ���ڽ�ʬ���
			&& pic_idx == 2)                                                   //3.ֲ���˶���ͼƬ2
		{
			this->plants_attack(mission, hang); //ֲ�﹥��
		}
	}

	if (pic_idx > 14)
		pic_idx = 0;   //����

	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("SnowPea/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
	sp_plant->setTexture(texture);

	pic_idx += 1;
}

void SnowPea::plants_attack(TestScene &mission, int hang)  //ֲ�﹥��
{

	SimpleAudioEngine::getInstance()->playEffect("SE/throw.mp3");//������Ч

	Vec_Bullet.push_back(new Bullet);       //�ӵ�����
	Vec_Bullet[Vec_Bullet.size() - 1]->bulletInit(this->type, sp_plant->getPosition().x, sp_plant->getPosition().y); //���ؼ����㶹����ͼ
	Vec_Bullet[Vec_Bullet.size() - 1]->sp_bullet->setPosition(sp_plant->getPosition().x + 15, sp_plant->getPosition().y + 15);//�趨�ӵ�������
	Vec_Bullet[Vec_Bullet.size() - 1]->hang = hang;


	mission.addChild(Vec_Bullet[Vec_Bullet.size() - 1]->sp_bullet, 100);

	auto acBulMovRight = MoveBy::create(2.2f, Point(900, 0));

	Vec_Bullet[Vec_Bullet.size() - 1]->sp_bullet->runAction(acBulMovRight); //�����ӵ����˶�

}