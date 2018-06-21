#include "LayerPopup.h"
#include "LayerGame.h"
#include "LayerStart.h"

bool LayerPopup::init()
{
	if (!CCLayer::init()){ return false; }	

	m_TouchStretch = 2;
	//���ô�������
	this->setTouchEnabled(true);

	m_Dict = CCDictionary::createWithContentsOfFile(zh_CN_XML);		
	return true;
}

void LayerPopup::registerWithTouchDispatcher()
{
	//kCCMenuHandlerPriority=-128�������ֵ����Ϊ-128�Ķ��������Ա��±ߵĲ�����ȼ���
	//����ccTouchBegan�ķ���ֵΪtrue��˵�������Ĳ㽫���ܲ������������Ϣ�ˣ�ֻ��������ϱߵ�
	//�˵������ȼ�������Ҫ���������ϱߵĲ˵��ǿ��Խ��յ�������Ϣ��
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
		kCCMenuHandlerPriority * m_TouchStretch, true);
}

bool LayerPopup::ccTouchBegan(CCTouch * touch, CCEvent * pevent)
{
	return true;
}

/************************************************************************/
/* ������Ϸ�Ի���                                                        */
/************************************************************************/
bool LayerBack::init()
{
	if (!LayerPopup::init()){ return false; }

	CCSprite *bgSprite1 = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(0, 256, 256, 64));
	bgSprite1->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 116));
	this->addChild(bgSprite1);

	//���������ı���ͼƬ������������λ��Ϊ������Ļ���е�	
	CCSprite *bgSprite2 = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(0, 0, 512, 256));
	bgSprite2->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bgSprite2);
	bgSprite = bgSprite2;

	//��ӷ�����Ϸ�˵���ť
	CCMenuItemLabel *backItem = Common::itemLabel(m_Dict, zh_BACKGAME, ccp(winSize.width / 2, winSize.height / 2 + 120));
	backItem->setTarget(this, menu_selector(LayerBack::backCallBack));
	CCMenu *menu = CCMenu::create(backItem, NULL);
	menu->setTouchPriority(kCCMenuHandlerPriority * m_TouchStretch - 1);
	menu->setPosition(CCPointZero);
	this->addChild(menu);	

	return true;
}

void LayerBack::backCallBack(CCObject *sender)
{
	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[0], false);
	}
}

/************************************************************************/
/* ���ý���                                                              */
/************************************************************************/
bool LayerSettings::init()
{
	if (!LayerBack::init()){ return false; }

	//��ӷ��ز˵���ť
	CCSprite *backMenuSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(0, 318, 80, 100));
	CCMenuItemSprite *backMenuItem = CCMenuItemSprite::create(backMenuSprite, backMenuSprite, this, menu_selector(LayerSettings::backMenuCallBack));
	backMenuItem->setPosition(ccp(255, 120));

	//��ӹرմ�music�˵���ť
	CCSprite *openmusicSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(128, 320, 80, 90));
	CCSprite *closemusicSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(0, 422, 80, 90));
	CCMenuItemSprite *openMusicItem = CCMenuItemSprite::create(openmusicSprite, openmusicSprite);
	CCMenuItemSprite *closeMusicItem = CCMenuItemSprite::create(closemusicSprite, closemusicSprite);
	CCMenuItemToggle * musicItem = CCMenuItemToggle::createWithTarget(this, menu_selector(LayerSettings::musicCallBack), openMusicItem, closeMusicItem, NULL);
	musicItem->setPosition(ccp(400, 120));

	//��ӹرմ�sound�˵���ť
	CCSprite *opensoundSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(255, 320, 80, 94));
	CCSprite *closesoundSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(128, 422, 80, 90));
	CCMenuItemSprite *openSoundItem = CCMenuItemSprite::create(opensoundSprite, opensoundSprite);
	CCMenuItemSprite *closeSoundItem = CCMenuItemSprite::create(closesoundSprite, closesoundSprite);
	CCMenuItemToggle * soundItem = CCMenuItemToggle::createWithTarget(this, menu_selector(LayerSettings::soundCallBack), openSoundItem, closeSoundItem, NULL);	
	soundItem->setPosition(ccp(115, 120));

	CCMenu *menu = CCMenu::create(backMenuItem, musicItem, soundItem, NULL);
	menu->setPosition(CCPointZero);
	menu->setTouchPriority(kCCMenuHandlerPriority * m_TouchStretch - 1);
	bgSprite->addChild(menu);

	if (!Common::isPlayEffect)
	{
		soundItem->setSelectedIndex(1);
	}
	if (!Common::isPlayMusic)
	{
		musicItem->setSelectedIndex(1);
	}

	return true;
}

void LayerSettings::backCallBack(CCObject *sender)
{
	LayerBack::backCallBack(sender);
	LayerBase1 *lb = (LayerBase1*)this->getParent();	
	lb->subPopup();
	this->removeFromParent();//�Ƴ��Ի���		
}

void LayerSettings::backMenuCallBack(CCObject *sender)
{
	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[0], false);
	}
	LayerGame *lg = dynamic_cast<LayerGame*>(this->getParent());
	//���������Ϸ�У��򷵻ص����˵���
	if (lg)
	{		
		lg->saveData(false);		
		//�ص���ʼ��Ϸ
		CCDirector::sharedDirector()->replaceScene(Common::scene(LayerStart::create()));
	}
	else
	{
		SimpleAudioEngine::end();//�ͷ�������Դ
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
		CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
#endif
	}
}

void LayerSettings::musicCallBack(CCObject *sender)
{
	unsigned int index = ((CCMenuItemToggle*)sender)->getSelectedIndex();
	//CCLog("musicCallBack,%d", index);		
	if (index == 0)//������
	{
		Common::isPlayMusic = true;
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();				
	}
	else if (index == 1)//�ر�����
	{
		Common::isPlayMusic = false;
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayMusic", Common::isPlayMusic);
}

void LayerSettings::soundCallBack(CCObject *sender)
{
	unsigned int index = ((CCMenuItemToggle*)sender)->getSelectedIndex();
	//CCLog("soundCallBack,%d", index);		
	if (index == 0)//����Ч
	{		
		Common::isPlayEffect = true;		
	}
	else if (index == 1)//�ر���Ч
	{
		Common::isPlayEffect = false;
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}
	CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayEffect", Common::isPlayEffect);
}

/************************************************************************/
/* �̵����                                                              */
/************************************************************************/
bool LayerShop::init()
{
	if (!LayerBack::init()){ return false; }

	//��ӹ���Ģ���˵���ť
	CCSprite *mushroomSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("shopMain.png"), CCRectMake(765, 50, 80, 80));
	CCMenuItemSprite *mushroomItem = CCMenuItemSprite::create(mushroomSprite, mushroomSprite, this, menu_selector(LayerShop::addMushroom));
	mushroomItem->setPosition(ccp(115, 125));
	//mushroomItem->setTarget(this, menu_selector(LayerShop::backCallBack));	

	//��ӹ��������˵���ť
	CCSprite *lifeSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("shopMain.png"), CCRectMake(900, 50, 80, 80));
	CCMenuItemSprite *lifeItem = CCMenuItemSprite::create(lifeSprite, lifeSprite, this, menu_selector(LayerShop::addLife));;
	lifeItem->setPosition(ccp(250, 125));
	//lifeItem->setTarget(this, menu_selector(LayerShop::backCallBack));

	CCMenu *menu = CCMenu::create(mushroomItem, lifeItem, NULL);
	menu->setPosition(CCPointZero);
	menu->setTouchPriority(kCCMenuHandlerPriority * m_TouchStretch - 1);
	bgSprite->addChild(menu);

	/*****************************����Ģ�����������Լ�ͼƬ********************************************************/
	CCLabelBMFont *buyMushroomLabel = Common::fontLabel(m_Dict, zh_BUYMUSHROOM, ccp(113, 145), 0.75f);
	bgSprite->addChild(buyMushroomLabel);
	CCSprite *coin1Sprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(450, 450, 25, 25));
	coin1Sprite->setPosition(ccp(80, 77));
	bgSprite->addChild(coin1Sprite);
	bgSprite->addChild(Common::fontLabel("150", ccp(120, 77)));
	/******************************�����������������Լ�ͼƬ*********************************************************/
	CCLabelBMFont *buyLifeLabel = Common::fontLabel(m_Dict, zh_BUYLIFE, ccp(255, 145));
	bgSprite->addChild(buyLifeLabel);
	CCSprite *coin2Sprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("menu.png"), CCRectMake(450, 450, 25, 25));
	coin2Sprite->setPosition(ccp(222, 77));
	bgSprite->addChild(coin2Sprite);
	bgSprite->addChild(Common::fontLabel("300", ccp(265, 77)));
	/*******************************ͳ��������������******************************************************************/
	m_GrowCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("growcount");
	m_Life = CCUserDefault::sharedUserDefault()->getIntegerForKey("life");
	m_Coin = CCUserDefault::sharedUserDefault()->getIntegerForKey("currentcoin");
	m_TempCoin = m_Coin;

	CCLabelBMFont *coinLabel = Common::fontLabel(m_Dict, zh_COINTEXT, ccp(120, 200), 0.6f);
	CCLabelBMFont *lifeLabel = Common::fontLabel(m_Dict, zh_LIFETEXT, ccp(270, 200), 0.6f);
	CCLabelBMFont *growLabel = Common::fontLabel(m_Dict, zh_GROWTEXT, ccp(380, 200), 0.6f);
	bgSprite->addChild(coinLabel);
	bgSprite->addChild(lifeLabel);	
	bgSprite->addChild(growLabel);

	m_CoinLabel = Common::fontLabel(Common::format(m_Coin), ccp(150, 200), 0.6f);
	m_CoinLabel->setAnchorPoint(ccp(0, 0.5f));	
	m_LifeLabel = Common::fontLabel(Common::format(m_Life), ccp(305, 200), 0.6f);
	m_LifeLabel->setAnchorPoint(ccp(0, 0.5f));	
	m_GrowLabel = Common::fontLabel(Common::format(m_GrowCount), ccp(415, 200), 0.6f);
	m_GrowLabel->setAnchorPoint(ccp(0, 0.5f));
	bgSprite->addChild(m_CoinLabel);
	bgSprite->addChild(m_LifeLabel);
	bgSprite->addChild(m_GrowLabel);
	
	/******************************��ʾ����**************************************************************************/
	CCLabelBMFont *hintLabel = Common::fontLabel(m_Dict, zh_SHOPHINT, ccp(bgSprite->getContentSize().width / 2, 45));
	bgSprite->addChild(hintLabel);

	this->scheduleUpdate();
	//���ô�������
	//this->setTouchEnabled(true);

	return true;
}

void LayerShop::addMushroom(CCObject*)
{
	m_TempCoin -= 150;
	if (m_TempCoin <= 0)
	{
		m_TempCoin = m_Coin;
		return;
	}

	m_GrowCount++;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("growcount", m_GrowCount);
	
	m_GrowLabel->setString(Common::format(m_GrowCount));

	LayerGame *lg = dynamic_cast<LayerGame*>(this->getParent());
	if (lg)
	{
		lg->setGrowCount(m_GrowCount);
		lg->setCoin(m_TempCoin);
	}

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[0], false);
	}
}

void LayerShop::addLife(CCObject*)
{
	m_TempCoin -= 300;
	if (m_TempCoin <= 0)
	{
		m_TempCoin = m_Coin;
		return;
	}
	m_Life++;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("life", m_Life);
	
	m_LifeLabel->setString(Common::format(m_Life));

	LayerGame *lg = dynamic_cast<LayerGame*>(this->getParent());
	if (lg)
	{
		lg->setLife(m_Life);
		lg->setCoin(m_TempCoin);
	}

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[0], false);
	}
}

void LayerShop::update(float)
{	
	if (m_TempCoin < m_Coin)
	{
		m_Coin -= 5;
		if (m_TempCoin > m_Coin)
			m_Coin = m_TempCoin;		
		m_CoinLabel->setString(Common::format(m_Coin));
	}
}

void LayerShop::backCallBack(CCObject *sender)
{
	LayerBack::backCallBack(sender);
	LayerBase1 *lb = (LayerBase1*)this->getParent();
	if (m_Life == 0)
	{
		LayerGame *lg = dynamic_cast<LayerGame*>(lb);
		if (lg)
		{
			lb->overDialog(false);
		}		
	}	
	lb->subPopup();
	//CCLog("%p", lg);
	this->removeFromParent();
}


/************************************************************************/
/* ��Ϸ�����Ի���                                                        */
/************************************************************************/
LayerOver* LayerOver::create(bool isEsc)
{
	LayerOver *pRet = new LayerOver;
	if (pRet && pRet->init(isEsc))
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}

bool LayerOver::init(bool isEsc)
{
	if (!LayerPopup::init()){ return false; }

	CCSprite *bgSprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("shopMain.png"), CCRectMake(640, 200, 260, 260));
	bgSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	bgSprite->setScaleX(1.5f);
	bgSprite->setScaleY(1.2f);	
	this->addChild(bgSprite);
	this->setPositionY(winSize.height - 100);

	m_IsEsc = isEsc;
	m_TouchStretch = 3;

	CCMenuItemLabel *buttonItem1;
	CCMenuItemLabel *buttonItem2;
	if (m_IsEsc)
	{
		CCLabelBMFont *hintLabel = Common::fontLabel(m_Dict, zh_QUITGAMETEXT, ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(hintLabel);
		//��ӷ�����Ϸ�˵���ť
		buttonItem1 = Common::itemLabel(m_Dict, zh_CONFIRM, ccp(winSize.width / 2 - 70,
												winSize.height / 2 - bgSprite->getContentSize().height / 2 + 10));
		buttonItem2 = Common::itemLabel(m_Dict, zh_CANCEL, ccp(winSize.width / 2 + 70,
												winSize.height / 2 - bgSprite->getContentSize().height / 2 + 10));
	}
	else
	{
		CCLabelBMFont *hintLabel = Common::fontLabel(m_Dict, zh_GAMEOVER1TEXT, ccp(winSize.width / 2, winSize.height / 2));
		CCLabelBMFont *hintLabel2 = Common::fontLabel(m_Dict, zh_GAMEOVER2TEXT, ccp(winSize.width / 2, winSize.height / 2 - hintLabel->getContentSize().height));
		this->addChild(hintLabel);
		this->addChild(hintLabel2);
		//��ӷ�����Ϸ�˵���ť
		buttonItem1 = Common::itemLabel(m_Dict, zh_SHOPBUYLIFE, ccp(winSize.width / 2 - 70,
												winSize.height / 2 - bgSprite->getContentSize().height / 2 + 10));
		buttonItem2 = Common::itemLabel(m_Dict, zh_MAINMENU, ccp(winSize.width / 2 + 70,
												winSize.height / 2 - bgSprite->getContentSize().height / 2 + 10));		
	}		

	buttonItem1->setTarget(this, menu_selector(LayerOver::button1CallBack));
	buttonItem2->setTarget(this, menu_selector(LayerOver::button2CallBack));
	CCMenu *menu = CCMenu::create(buttonItem1, buttonItem2, NULL);
	menu->setTouchPriority(kCCMenuHandlerPriority * m_TouchStretch - 1);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	if (Common::isPlayMusic)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	return true;
}

//over�Ի���ĵ�һ����ť
void LayerOver::button1CallBack(CCObject*)
{	
	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[0], false);
	}
	if (m_IsEsc)
	{
		LayerGame *lg = dynamic_cast<LayerGame*>(this->getParent());
		if (lg)
		{
			lg->saveData(false);
		}
		SimpleAudioEngine::end();//�ͷ�������Դ
		//�˳���Ϸ
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
		CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
#endif
	}
	else
	{
		//�����̵�
		LayerBase1 *lb = (LayerBase1*)this->getParent();
		lb->addChild(LayerShop::create());
		lb->addPopup();

		lb->subPopup();		
		this->removeFromParent();		
	}
}

//over�Ի���ĵڶ�����ť
void LayerOver::button2CallBack(CCObject*)
{
	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[0], false);
	}
	if (m_IsEsc)
	{		
		LayerBase1 *lb = (LayerBase1*)this->getParent();
		lb->subPopup();		
		//ȡ���ص���Ϸ
		this->removeFromParent();	
		if (Common::isPlayMusic)
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
	}
	else
	{
		if (Common::isPlayEffect)
		{
			SimpleAudioEngine::sharedEngine()->playEffect(effectNames[0], false);
		}
		//�ص���ʼ��Ϸ
		CCDirector::sharedDirector()->replaceScene(Common::scene(LayerStart::create()));
	}
}