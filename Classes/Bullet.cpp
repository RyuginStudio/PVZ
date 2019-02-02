#include "Bullet.h"
#include "Zombie1.h"
#include <vector>


extern std::vector<Bullet*> Vec_Bullet;       //�ӵ�����
extern std::vector<Enemy*> Vec_Enemy;         //��������

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::bulletInit(int bullet_type, int posBgnX, int posBgnY)
{
	this->disappear = false;           //��ʼ���ӵ���������ʧ��״̬
	this->bullet_type = bullet_type;   //��ֵ���ӵ���������

	this->Pos_begin_x = posBgnX;       //�ӵ���ʼ���꣨������ӵ���ֲ������꣩
	this->Pos_begin_y = posBgnY;

	switch (bullet_type)
	{
	case 1: //�㶹��  Ч�����й��о�
	{
		this->demage = 5;
		sp_bullet = Sprite::create("bullet/1.png");
		break;
	}	
	case 2: //������  Ч����ʹ���˼��٣����˺�ֵ��
	{
		this->demage = 3;
		sp_bullet = Sprite::create("bullet/2.png");
		break;
	}
	case 3: //�ռ����浯
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

void Bullet::bulletRemove(TestScene & mission) //���շ����ӵ�
{
	for (int idx = 0; idx < Vec_Bullet.size(); idx++)
	{
		if (Vec_Bullet[idx]->disappear == true)
		{
			mission.removeChild(Vec_Bullet[idx]->sp_bullet);   //��������ͼƬ

            //������ײ�����Ǹ������ǵ�һ������Ϊ�к�����ֲ��ֲ��������ӵ�����ײ����ʬ�������
			Vec_Bullet.erase(Vec_Bullet.begin() + idx);
			idx--;
		}

	}
}

void Bullet::bullet_bomb_collision() //�ӵ���ײ����Լ�ը��ͼƬ����
{
	for (Bullet *i : Vec_Bullet)
	{
		for (int j = 0; j < Vec_Enemy.size(); j++)
		{
			if (Vec_Enemy[j]->ash == true | Vec_Enemy[j]->blood <= 0 | Vec_Enemy[j]->sp_enemy->getPosition().x < i->Pos_begin_x) //�ҽ�״̬������С���ӵ���ʼ���ꡢ��Ѫ => �ų��������ʬ
				continue;
			if (i->disappear == true)
				break;

			if (i->hang == Vec_Enemy[j]->hang //��ʬ���ӵ�ͬ�� 
				&&i->disappear == false //�ӵ���������ʧ״̬
				&& i->sp_bullet->getPosition().x >= Vec_Enemy[j]->sp_enemy->getPosition().x //ײ�ϻ��ߴ���
				) //�������ϣ�������ײ
			{
				Vec_Enemy[j]->blood -= i->demage;  //��ʬ��Ѫ

				CCLOG("%d", Vec_Enemy[j]->blood);
				SimpleAudioEngine::getInstance()->playEffect("SE/splat2.mp3"); //�����Ч
			
				CCTexture2D* texture = CCTextureCache::sharedTextureCache()->
					addImage("bullet/" + CCString::createWithFormat("%d", i->bullet_type)->_string + "_bomb.png");//ƥ����Ӧ���ӵ���Ƭ

				i->sp_bullet->setTexture(texture);

				i->sp_bullet->stopAllActions();

				i->disappear = true;

				if (i->bullet_type == 2)  //����Ǽ��ٵ��ı��������
				{
					Vec_Enemy[j]->speed = -0.6;
					CCLOG("%s", "slowDown!");
				}
			}
		}
	}
}
