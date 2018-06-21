#include "MarioBullet.h"

CCArray *Bullet::m_Bullets = NULL;

void Bullet::preload()
{
	{//�ӵ�����ը����
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("skill4.png");		
		CCArray* arr = CCArray::create();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				/*CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pTexture, CCRectMake(j*(1024 / 5.0f), i*(1024 / 5.0f), 
																									(1024 / 5.0f), (1024 / 5.0f)));*/
				CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pTexture, CCRectMake(j * 192, i * 192 + 32, 192, 160));
				arr->addObject(frame);
			}
		}		
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr, 0.05f), "IceBulletBlast");
	}
}

bool Bullet::init()
{
	if (!Biology::init()){ return false; }

	this->setZOrder(Common::Z_BULLETFRIEND);
	this->setScale(0.5f);	
	//this->setRotation(CCRANDOM_0_1() * 360);//360������õ�һ���Ƕ�

	m_IsMove = true;
	m_IsFly = false;

	m_H_s = 0;//����ˮƽλ�ƣ������ж��ӵ��Ƿ��ƶ�һ����Ļ�ľ���

	//�����÷����ʱ����ٽ��и�ֵ
	m_H_v1 = BULLET_H_V1;
	m_H_Max_v1 = BULLET_H_V1;
	//��ֱ����ļ��ٶȺ��ٶ�
	m_V_a = -BULLET_V_A;
	m_V_v1 = 0;
	m_V_Max_v1 = BULLET_MAX_V;
	return true;
}

//ˮƽ�����ϵ��ƶ�
void Bullet::moveH(float dt)
{
	//dtʱ���λ��
	float s = m_H_v1 * dt;
	this->setPositionX(this->getPositionX() + s);
	//�ۼ�ˮƽλ��
	m_H_s += s;
	if (_isCollisionLeft())
	{
		//�ӵ���ը
		//CCLog("left collision");
		autoDead();
	}
	else if (_isCollisionRight())
	{
		//�ӵ���ը
		//CCLog("right collision");
		autoDead();
	}
}

//��ֱ�����ϵ��ƶ�
void Bullet::moveV(float dt)
{		
	//dtʱ���λ��
	float s = m_V_v1 * dt + m_V_a *dt*dt / 2;
	m_V_v1 = m_V_v1 + m_V_a * dt;//dtʱ���ٶ�
	this->setPositionY(this->getPositionY() + s);

	if (m_V_v1 <= -m_V_Max_v1)
		m_V_v1 = -m_V_Max_v1;	
	if (_isCollisionDown())
	{		
		//CCLog("_isCollisionDown , m_V_v1 = %g", m_V_v1);
		m_V_v1 = BULLET_V_V1;			
	}
	else if (_isCollisionUp())
	{
		m_V_a = -BULLET_V_A;
		m_V_v1 = 0;		
	}	
}

//�����ӵ���״̬
void Bullet::updateStatus()
{
	if (!m_IsMove)
	{			
		//��ͨ�ӵ�		
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MarioBULLETBLAST1"));
		scheduleOnce(schedule_selector(Bullet::removeSelf), 0.2f);	
		return;
	}	
	//��ͨ�ӵ�
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MarioBULLET"));	
}
//�ӵ������Ƴ�
void Bullet::removeSelf(float)
{
	this->removeFromParent();
	m_Bullets->removeObject(this);
}

//��ײ�����ִ�еķ���
void Bullet::autoDead()
{
	//CCLog("%g", m_V_v1);
	m_IsMove = false;
	m_Life = 0;
	updateStatus();
}

//�ж��Ƿ���ײ
bool Bullet::isCollision(Biology *obj)
{	
	return (this->boundingBox().intersectsRect(obj->boundingBox()));
}

//�߼�
void Bullet::logic(float dt)
{
	if (m_IsMove)
	{
		move(dt);		
	}	

	if (m_Life && (m_H_s * m_H_s > winSize.width * winSize.width || this->getPositionX() <= 0 || this->getPositionY() <= getMap()->getTileSize().height))
	{
		autoDead();
	}
}

/************************************************************************/
/* ����һ���ӵ����󣬱�ըʱΪ����                                          */
/************************************************************************/
bool IceBullet::init()
{
	if (!Bullet::init()){ return false; }
	
	m_GrowState = 1;
	return true;
}

void IceBullet::autoDead()
{
	m_IsMove = false;	
	//m_Life = 0;//����������Ϊ0����Ϊ��ը��ʱ��Ҳ��������˺�
	if (m_GrowState)
	{
		if (Common::isPlayEffect)
		{
			SimpleAudioEngine::sharedEngine()->playEffect(effectNames[5], false);
		}
	}
	updateStatus();	
}

//�����ӵ���״̬
void IceBullet::updateStatus()
{
	if (!m_IsMove)
	{
		if (m_GrowState)
		{
			//CCLog("IceBulletBlast");
			//this->setRotation(0);//��ը�ѽǶȻָ�
			//��ͨ�ӵ�	
			this->setScale(1.0f);
			this->setDisplayFrameWithAnimationName("IceBulletBlast", 0);
			CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("IceBulletBlast"));
			CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(IceBullet::removeSelf));
			this->runAction(CCSequence::create(animate, done, NULL));
			m_GrowState = 0;
		}		
		return;
	}
	//��ͨ�ӵ�
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MarioBULLET"));
}

void IceBullet::removeSelf()
{
	//CCLog("xxxxxxxxx");
	m_Life = 0;
	Bullet::removeSelf(0);
}

/************************************************************************/
/* ʷ̩���ӵ�����                                         */
/************************************************************************/
bool FireBullet::init()
{
	if (!Bullet::init()){ return false; }

	m_GrowState = 1;
	return true;
}

void FireBullet::autoDead()
{
	m_IsMove = false;
	m_Life = 0;//������Ϊ0
	/*if (m_GrowState)
	{
		if (Common::isPlayEffect)
		{
			SimpleAudioEngine::sharedEngine()->playEffect(effectNames[5], false);
		}
	}*/
	updateStatus();
}

//�����ӵ���״̬
void FireBullet::updateStatus()
{
	if (!m_IsMove)
	{
		if (m_GrowState)
		{
			//CCLog("IceBulletBlast");
			//this->setRotation(0);//��ը�ѽǶȻָ�
			//��ͨ�ӵ�	
			this->setScale(1.0f);
			this->setDisplayFrameWithAnimationName("IceBulletBlast", 0);
			CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("IceBulletBlast"));
			CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(FireBullet::removeSelf));
			this->runAction(CCSequence::create(animate, done, NULL));
			m_GrowState = 0;
		}
		return;
	}
	//��ͨ�ӵ�
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MarioBULLET"));
}

void FireBullet::removeSelf()
{
	//CCLog("xxxxxxxxx");
	m_Life = 0;
	Bullet::removeSelf(0);
}