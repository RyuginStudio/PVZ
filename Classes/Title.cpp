#include "Title.h"
#include "SimpleAudioEngine.h"
#include "TestScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Sprite *sp_title;
Sprite *sp_version;

Title::Title()
{
}


Title::~Title()
{
}


void Title::GameBgCallBack(Ref * callback) //ѡ��ʼ��Ϸ�Ļص�����
{
	Director::getInstance()->replaceScene(CCTransitionFadeTR::create(2.5f, TestScene::createScene()));
	SimpleAudioEngine::getInstance()->playEffect("SE/confirm.mp3");
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Title::update_per_0_1(float dt)  //�趨0.1s��ʱ��
{
	static int idx = 0;  

	idx >= 22 ? idx = 0 : ++idx;  //��һ��ѭ����1��ʼ��Ϊtitle�����ͼƬ����ֵΪ��0

	CCTexture2D *texture = TextureCache::sharedTextureCache()
		->addImage("Title/" + CCString::createWithFormat("%d", idx)->_string + ".png");

	sp_title->setTexture(texture);
}


Scene* Title::createScene()
{
	auto scene = Scene::create();

	auto layer = Title::create();

	scene->addChild(layer);

	return scene;
}

bool Title::init()
{
	srand((unsigned int)time(0));

	if (!Layer::init())
	{
		return false;
	}

	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/title.mp3", true);

	sp_title = Sprite::create("Title/0.png");
	sp_title->setPosition(Point(480, 319));	
	this->addChild(sp_title);

	sp_version = Sprite::create("Title/version.png");	
	sp_version->setPosition(Point(455, 323));
	this->addChild(sp_version);

	auto gameBegin = MenuItemImage::create("Title/playButton.png", "Title/pressDown.png", this, menu_selector(Title::GameBgCallBack));
	auto menu = Menu::create(gameBegin, NULL);
	menu->setPosition(Point(480, 205));
	this->addChild(menu);
	
	this->schedule(schedule_selector(Title::update_per_0_1), 0.1f);  //�༭ʱ��Ҫע����仰������vs2017�Զ���ȫ����ʧЧ

	return true;
}