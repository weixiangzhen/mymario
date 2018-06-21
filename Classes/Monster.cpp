#include "Monster.h"

CCArray *Monster::m_MAwardDatas = NULL;

//ͼƬԤ����
void Monster::preload()
{
	CCTexture2D *pObjectTexture = CCTextureCache::sharedTextureCache()->addImage("tiledmap/object.png");
	
	{//���ש��
		CCArray *arr = CCArray::create();

		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 32, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(32, 32, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 32, 32, 32));
		arr->addObject(frame);

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.5f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "BrickCoin");
	}

	{//��ʯש��
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 96, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "BrickRock");
	}

	{//�����Ч
		CCArray *arr = CCArray::create();

		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(96, 32, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 32, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(160, 32, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 32, 32, 32));
		arr->addObject(frame);

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.02f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "BrickMakeCoin1");
	}

	{//��Ҷ�����Ч2
		CCArray *arr = CCArray::create();

		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(96, 128, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 128, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(160, 128, 32, 32));
		arr->addObject(frame);

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.02f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "BrickMakeCoin2");
	}

	{//����Ҷ���
		CCArray *arr = CCArray::create();

		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 128, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(32, 128, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 128, 32, 32));
		arr->addObject(frame);

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.5f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "PropCoin");
	}

	{//ʳ��
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(224, 0, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "FoodMushroom");

		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(96, 96, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "FoodFlower");

		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(224, 32, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "DarkFoodMushroom");
	}

	{//��ͨ�Ĺ���
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 160, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MonsterSmall");
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(32, 160, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MonsterSmallDead");

		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 160, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MonsterSmallBlack");
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(96, 160, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MonsterSmallBlackDead");
	}

	{//�ڹ�߷ɱ��߶���
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 320, 64, 64));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 320, 64, 64));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "TortoiseFlyWalk");
		//�ڹ����߶���
		arr = CCArray::create();
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 320, 64, 64));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 320, 64, 64));
		arr->addObject(frame);
		animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "TortoiseWalk");

		//���
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 160, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "TortoiseHull");

		//�ڹ���ʱ��Ķ���
		arr = CCArray::create();
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(160, 160, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 160, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(224, 160, 32, 32));
		arr->addObject(frame);
		animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "TortoiseCrazy");
	}

	{//�ֿ������߶���
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 224, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(32, 224, 32, 32));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "HelmetWalk");		
		//�ֿ����
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 224, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "HelmetHull");
		//�ֿ��ڹ���ʱ��Ķ���
		arr = CCArray::create();
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(96, 224, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 224, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(160, 224, 32, 32));
		arr->addObject(frame);
		animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "HelmetCrazy");
	}

	{//���̹����߶���
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(32, 192, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 192, 32, 32));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Backstab");
	}

	{//����
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 608, 64, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "Stair");
	}

	{//ˮ���㶯��
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 384, 64, 64));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 384, 64, 64));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Piranha");
	}

	{//ʳ�˻�����
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 192, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(160, 192, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 192, 32, 32));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "SFlower");
	}

	{//�𵯶���
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(160, 256, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 256, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(224, 256, 32, 32));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "AnBiao");
	}

	{//boss����+���䶯��
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 512, 64, 64));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 512, 64, 64));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 512, 64, 64));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 1.0f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "BossWalk");

		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 512, 64, 64));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "BossShoot");
	}

	{//boss�ӵ��Ķ���		
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(0, 608, 64, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 608, 64, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 608, 64, 32));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "BossBullet");
	}

	{//Բ��
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 224, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "Disk");
	}

	{//�ڵ����ӵ�
		CCArray *arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(64, 256, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(96, 256, 32, 32));
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 256, 32, 32));
		arr->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 0.2f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "CannonBullet");
	}

	{//����µ���ͨ�ӵ�1
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(192, 128, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MarioBULLET");

		frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(224, 128, 32, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MarioBULLETBLAST1");	
	}

	{//��������
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pObjectTexture, CCRectMake(128, 480, 64, 32));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "End");	
	}
}

//��������
Monster* Monster::create(Biology *obj)
{
	Monster *pRet = new Monster;
	if (pRet && pRet->init(obj))
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

//��ʼ��
bool Monster::init()
{
	if (!Biology::init()){ return false; }	
	//���ù����zorder
	this->setZOrder(Common::Z_FOOD);	

	m_Biology = NULL;//	

	m_IsMove = false;//Ĭ�ϲ����ƶ�
	return true;
}

bool Monster::init(Biology *obj)
{
	if (!Monster::init()){ return false; }
	
	m_Biology = obj;
	return true;
}

void Monster::addAward(CCPoint p, bool isMakeCoin, bool isMonster, int score)
{
	MAwardData *data = MAwardData::create();
	data->setPosition(p);
	data->setMakeCoin(isMakeCoin);
	data->setMonster(isMonster);
	data->setScore(score);
	m_MAwardDatas->addObject(data);
}

//�ж��Ƿ���ײ
bool Monster::isCollision(Biology *obj)
{	
	if (obj->getLife() <= 0)return false;//����С�ڵ���0�󣬲�����ײ	
	return (this->boundingBox().intersectsRect(obj->boundingBox()));
}

//�Ƿ�ש������
bool Monster::isCollisionBrick(int *pos)
{
	CCTMXLayer *layer = getMap()->layerNamed("monster_image");

	CCRect rect = this->boundingBox();
	//-10��Ϊ�˵���ת���Ƿ���ש�飬����Ӧ���Ǽ�ש��߶ȵ�һ��
	CCPoint p[3] = { ccp(rect.getMidX(), rect.getMinY() - 10), ccp(rect.getMinX(), rect.getMinY() - 10), ccp(rect.getMaxX(), rect.getMinY() - 10) };

	for (int i = 0; i < 3; i++)
	{
		CCPoint pt1 = Common::pointToTile(getMap(), p[i]);
		CCSprite *spr = layer->tileAt(pt1);
		if (!spr)
			continue;

		//�������ڶ���
		CCPoint pt2 = Common::tileToPoint(getMap(), pt1);
		if (pt2.y != spr->getPositionY())
		{
			if (pos)			
				*pos = i;
			return true;
		}
	}
	return false;
}

//��ײ���
/*void Monster::logic(Biology *obj)
{
	if (m_Life && isCollision(obj))
	{
		//m_Life = 0;	
		autoDead(obj);
	}

	//ÿ�ζ��ж��Ƿ�Ҫ�Ƴ��Լ�
	removeSelf();
	
}*/
//��ײ���+�ƶ�
/*void Monster::logic(float dt, Biology *obj)
{
	if (m_Life && m_IsMove)
	{
		move(dt);
	}
	logic(obj);		
}*/

