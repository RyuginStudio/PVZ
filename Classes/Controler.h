#ifndef __CONTROLER_H__
#define __CONTROLER_H__

#include "cocos2d.h"
#include "TestScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Controler
{
public:

	static void rand_change_BG(Sprite* &GameBackGround); //���������������ͼ

	static int SunValue;         //����ֵ 

	static bool UserCanPlant;    //����Ƿ������ֲֲ��
	
	Controler();  //��ʼ�����������

	static void drawTestGrid(TestScene &mission);   //���Ʋ�������

	static void addZombieTest(TestScene &mission);

	static void createSunFromSky(TestScene &mission);    //�����¼��������

	static void sunFallDown(); //���ϵ���������

	static void sunDisappear(TestScene &mission); //�����¼�������7����Զ���ʧ

	//����ֲ���ҡ�ں�������һ����֡���µ�������Ĺ�������
	static void plants_shake_controler(TestScene &mission);   //ֲ��ҡ���ܿ�
	
	static void plant_disappear(TestScene &mission);   //ֲ�������󣨿�Ѫ���峡�ܿ�

	static void zombieRecoverSpeed();    //�ָ��������ٽ�ʬ���ٶ�

	static void zombie_die_animation();   //��ʬ���������ܿ�

	static void zombie_disappear(TestScene &mission);   //��ʬ�������峡�ܿ�

	static void drawPlantIconTable(int count, TestScene &mission, Size winSize);  //����ֲ��ͼ�������ڵ�ѡ���Ӷ���ֲֲ�� => �Լ�label��������˵��
	static void drawSunValue(TestScene *const &mission); //���Ƶ�ǰ�ؿ�����¶ֵ������֡��ʱ���У�û֡�ص�

	static void drawPlantMask(TestScene &mission);   //����ֲ���ɰ棨����������ʹֲ���ң�

	static void drawPlantSelectSquare(TestScene &mission, int PlantChoice);    //����ѡ���ֲ�������ѡ��������ֱ�۵ؿ���ѡ�����ʲôֲ��

	//static void addZombie(TestScene &mission, int *beg, int *end);   //����ÿ�������еĽ�ʬˢ�����飬��mission������ˢ�½�ʬ

	static void eat_brain(TestScene &mission);   //�Ե�������Ϸ����
};

#endif // !__CONTROLER_H__