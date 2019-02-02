#include "Zombie1.h"
#include "SunFlower.h"
#include "PeaShooter.h"
#include "SnowPea.h"
#include "NutWall.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

extern std::vector<Plants*> Vec_Plants;    //���տ�����

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

	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���ڳߴ�

	sp_enemy = Sprite::create("zombie1_move/0.png");

	if (sp_enemy == nullptr)
		exit(-1);  //��ָ�룬���ز�����Դ����
	
	/*��������Ϊ��66   �²����߶�Ϊ��18
	���Ӻ�����Ϊ��91  ��������߶�Ϊ��106*/
	sp_enemy->setPosition(visibleSize.width+sp_enemy->getContentSize().width/9, (hang-1)*106+18+80); //�趨��ɫxλ�ã���û����������ʽ
	
	return sp_enemy;
}

void Zombie1::enemy_move_attack()
{
	if (ash == true)  //���״̬Ϊ���ҽ�
		return;
	
	for (int idx = 0; idx < Vec_Plants.size(); idx++)
	{
		if (Vec_Plants[idx]->hang == this->hang               //�趨�����䣬����ڽ�ʬ�����ֲ�����½�ʬ�гɹ���״̬����ס��������
			&& Vec_Plants[idx]->sp_plant->getPosition().x >= this->sp_enemy->getPosition().x - Vec_Plants[idx]->sp_plant->getContentSize().width / 3
			&& Vec_Plants[idx]->sp_plant->getPosition().x <= this->sp_enemy->getPosition().x + Vec_Plants[idx]->sp_plant->getContentSize().width / 3
			&& this->blood > 0 && Vec_Plants[idx]->blood > 0
			&& Vec_Plants[idx]->zombieEat == true) //��֤�ǽ�ʬ�Ե�ֲ��ų�ӣ�ҡ������Ŀ�λ��
		{
			this->attack_or_not = true;

			if (pic_attack_idx == 0)
				SimpleAudioEngine::getInstance()->playEffect("SE/chomp.mp3");//����һ��

			CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("zombie1_attack/" + CCString::createWithFormat("%d", pic_attack_idx)->_string + ".png");
			sp_enemy->setTexture(texture);
			pic_attack_idx++;
			if (pic_attack_idx > 20)
				pic_attack_idx = 0; //���ö���֡��

			Vec_Plants[idx]->blood -= 2; //����ֲ���Ѫ��

			if (Vec_Plants[idx]->blood <= 0 && this->blood > 0) //ֲ������
			{
				this->attack_or_not = false;
			}
		}
	}	

	int lie = ceil((sp_enemy->getPosition().x - 66) / 91);
	//���������ƶ���1.����ʬ����״̬Ϊ��ʱ�ƶ� 2.��ʬ���ڵ��С���û��ֲ��ʱ�ƶ�
	if (this->attack_or_not == false || array_PlantOrNot[hang][lie] == false)
	{
		this->attack_or_not = false; //Ϊ������Ч�����󲥷�

		if (pic_idx > 21)
			pic_idx = 0;   //����

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("res/zombie1_move/" + CCString::createWithFormat("%d", pic_idx)->_string + ".png");
		sp_enemy->setTexture(texture);

		pic_idx += 1;

		auto acMoveLeft = MoveBy::create(0.1f, Vec2(speed, 0));
		sp_enemy->runAction(acMoveLeft);
	}

}
