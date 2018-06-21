#include "AppDelegate.h"
#include "LayerStart.h"
#include "Common.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);	
	//pEGLView->setDesignResolutionSize(1024, 512, kResolutionExactFit);
	pEGLView->setDesignResolutionSize(800, 480, kResolutionExactFit);

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	CCScene *pScene = Common::scene(LayerStartLoading::create());

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
	CCObject *obj = CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0);
	LayerBase1 *base = dynamic_cast<LayerBase1*>(obj);
	if (base)
	{
		base->keyBackClicked();
	}
	else
	{
		CCDirector::sharedDirector()->stopAnimation();
		if (Common::isPlayMusic)		
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();		
		if (Common::isPlayEffect)		
			SimpleAudioEngine::sharedEngine()->pauseAllEffects();		
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
	CCObject *obj = CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0);
	LayerBase1 *base = dynamic_cast<LayerBase1*>(obj);
	if (base)
	{
		//base->keyBackClicked();
	}
	else
	{
		CCDirector::sharedDirector()->stopAnimation();
		if (Common::isPlayMusic)
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		if (Common::isPlayEffect)
			SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}
}
