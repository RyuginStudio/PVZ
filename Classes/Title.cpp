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


void Title::GameBgCallBack(Ref * callback) //选择开始游戏的回调函数
{
	Director::getInstance()->replaceScene(CCTransitionFadeTR::create(2.5f, TestScene::createScene()));
	SimpleAudioEngine::getInstance()->playEffect("SE/confirm.mp3");
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Title::update_per_0_1(float dt)  //设定0.1s定时器
{
	static int idx = 0;  

	idx >= 22 ? idx = 0 : ++idx;  //第一次循环从1开始因为title本身的图片索引值为：0

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
	
	this->schedule(schedule_selector(Title::update_per_0_1), 0.1f);  //编辑时需要注释这句话否则导致vs2017自动补全功能失效

	return true;
}