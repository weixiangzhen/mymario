#include "MonsterBullet.h"

CCArray *MonsterBullet::m_Bullets = NULL;

MonsterBullet* MonsterBullet::create(Biology *obj)
{
	MonsterBullet *pRet = new MonsterBullet;
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

bool MonsterBullet::init(Biology *obj)
{
	if (!Biology::init()){ return false; }
	
	this->setZOrder(Common::Z_FOOD);	

	m_Biology = obj;

	//ˮƽ�ٶ�
	m_H_a = 0;//ˮƽ����û�м��ٶ�
	m_H_Max_v1 = BIOLOGY_H_V * 1.4f;
	m_H_v1 = m_H_Max_v1;

	//��ֱ�ٶ�
	m_V_a = 0;
	m_V_Max_v1 = 0;
	m_V_v1 = m_V_Max_v1;

	m_IsMove = true;

	m_H_s = 0;
	return true;
}

void MonsterBullet::updateStatus()
{
	if (m_H_v1 > 0)
		this->setFlipX(false); 
	else 
		setFlipX(true); 
}

void MonsterBullet::autoDead()
{
	m_Life = 0;
	removeSelf();
	//CCLog("monster bullet remove");
}

bool MonsterBullet::isCollision(Biology *obj)
{
	return this->boundingBox().intersectsRect(obj->boundingBox());
}

void MonsterBullet::logic(float dt, Biology *obj)
{
	move(dt);

	//С�ڵ�ͼһ��ש��Ŀ�ȣ����ߵ�ͼһ��ש��ĸ߶�
	float dx = obj->getPositionX() - this->getPositionX();
	if (m_Life && ((dx * dx > winSize.width * winSize.width && m_H_s * m_H_s > winSize.width * winSize.width) || 
										this->getPositionX() <= 0 || this->getPositionY() <= getMap()->getTileSize().height))
	{
		autoDead();
	}
}

//ˮƽ�����˶�
void MonsterBullet::moveH(float dt)
{
	//dtʱ���λ��
	float s = m_H_v1 * dt;
	this->setPositionX(this->getPositionX() + s);
	//�ۼ�ˮƽλ��
	m_H_s += s;	
}

//��ֱ���򲻻��˶�
void MonsterBullet::moveV(float dt)
{

}

void MonsterBullet::removeSelf()
{
	this->removeFromParent();
	m_Bullets->removeObject(this);
}

/************************************************************************/
/* boss �ӵ�                                                            */
/************************************************************************/
BossBullet* BossBullet::create(Biology *obj)
{
	BossBullet *pRet = new BossBullet;
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

bool BossBullet::init(Biology *obj)
{
	if (!MonsterBullet::init(obj)){ return false; }

	this->setDisplayFrameWithAnimationName("BossBullet", 0);
	this->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("BossBullet"))));

	return true;
}


/************************************************************************/
/* cannon �ӵ�                                                          */
/************************************************************************/
CannonBullet* CannonBullet::create(Biology *obj)
{
	CannonBullet *pRet = new CannonBullet;
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

bool CannonBullet::init(Biology *obj)
{
	if (!MonsterBullet::init(obj)){ return false; }
	
	this->setZOrder(Common::Z_GROUND);
	this->setDisplayFrameWithAnimationName("CannonBullet", 0);
	this->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("CannonBullet"))));

	return true;
}
