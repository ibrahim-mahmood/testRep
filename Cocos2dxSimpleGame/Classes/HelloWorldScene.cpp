#include "HelloWorldScene.h"


using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(!CCLayerColor::initWithColor( ccc4(255,255,255,255) ) );

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);


		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *player = CCSprite::spriteWithFile("Player.png", 
			CCRectMake(0, 0, 27, 40) );
		player->setPosition( ccp(player->getContentSize().width/2, winSize.height/2) );
		this->addChild(player);

		bRet = true;
	} while (0);
	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
	return bRet;
}

void HelloWorld::addTarget()
{
	CCSprite *target = CCSprite::spriteWithFile("Target.png", 
		CCRectMake(0,0,27,40) );

	// Determine where to spawn the target along the Y axis
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = target->getContentSize().height/2;
	int maxY = winSize.height
		-  target->getContentSize().height/2;
	int rangeY = maxY - minY;
	// srand( TimGetTicks() );
	int actualY = ( rand() % rangeY ) + minY;

	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated
	target->setPosition( 
		ccp(winSize.width + (target->getContentSize().width/2), 
		actualY) );
	this->addChild(target);

	// Determine speed of the target
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration )
		+ minDuration;

	// Create the actions
	CCFiniteTimeAction* actionMove = 
		CCMoveTo::actionWithDuration( (float)actualDuration, ccp(0 - target->getContentSize().width/2, actualY) );
	CCFiniteTimeAction* actionMoveDone = 
		CCCallFuncN::actionWithTarget( this, 
		callfuncN_selector(HelloWorld::spriteMoveFinished));
	target->runAction( CCSequence::actions(actionMove, 
		actionMoveDone, NULL) );
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
}


// cpp with cocos2d-x
void HelloWorld::gameLogic(CCTime dt)
{
    this->addTarget();
	
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

