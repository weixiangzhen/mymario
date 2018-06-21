#include "MonsterEnemy.h"
#include "MonsterBullet.h"

CCArray *MonsterEnemy::m_MonsterEnemys = NULL;

MonsterEnemy* MonsterEnemy::create(Biology *obj)
{
	MonsterEnemy *pRet = new MonsterEnemy;
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

bool MonsterEnemy::init(Biology *obj)
{
	if (!Monster::init(obj)){ return false; }

	//this->setAnchorPoint(ccp(0.5f, 0));
	this->setZOrder(Common::Z_MONSTER);
	m_IsRun = false;//Ĭ��û������

	//�����ٶȺͷ���
	//Ĭ�����������ߣ����Է���logic(float, Biology*)���������о������һ��
	m_H_Max_v1 = BIOLOGY_H_V / 2;//����������ˮƽ������ٶ�
	m_H_v1 = -m_H_Max_v1;	

	//���ߵ���Ĭ����0
	m_LeftScope = 0;
	m_RightScope = 0;

	m_UpScope = 0;
	m_DownScope = 0;	
	return true;
}
//��дˮƽ������ƶ�����
void MonsterEnemy::moveH(float dt)
{
	if (m_H_v1 < 0)
	{
		calcX(dt);
		if (_isCollisionLeft() || (m_LeftScope != 0 && this->getPositionX() <= m_LeftScope))
		{
			m_H_v1 = m_H_Max_v1;//����ǽ���ٶȷ�����
			updateStatus();//����һ��״̬
		}
	}
	else if (m_H_v1 > 0)
	{
		calcX(dt);
		if (_isCollisionRight() || (m_RightScope != 0 && this->getPositionX() >= m_RightScope))
		{
			m_H_v1 = -m_H_Max_v1;//����ǽ���ٶȷ�����
			updateStatus();
		}
	}
	else//���ᶯ
	{

	}
}
//��д��ֱ������ƶ�����
void MonsterEnemy::moveV(float dt)
{
	if (m_V_v1 <= 0)//����
	{
		if (m_IsFly)
			calcY(dt);//�����䣬����ײ��⣬������΢������Ȼˮƽ�ƶ����������		
		if (_isCollisionDown() || (m_DownScope != 0 && this->getPositionY() <= m_DownScope))
		{
			if (m_IsFly)
			{
				m_IsFly = false;
				m_V_v1 = 0;//ÿһ��ֹͣ����ʱ�ٶȶ���0			
				updateStatus();
			}
		}
		else
		{
			if (!m_IsFly)
			{
				m_IsFly = true;
				//m_V_v1 = 0;			
				updateStatus();
			}
		}
	}
	else//����
	{
		calcY(dt);
		if (_isCollisionUp() || (m_UpScope != 0 && this->getPositionY() >= m_UpScope))
		{
			m_V_v1 = 0;
			m_V_a = -BIOLOGY_V_A;
		}
	}
}

//�ж��Ƿ񱻱�����ײ��ͷ��
bool MonsterEnemy::isCollisionHeader(Biology *obj)
{
	if (obj->getLife() <= 0)
		return false;

	if (obj->isGodMode() || obj->getLife() <= 0)//�������´����޵�״̬������²����ж��Ƿ��вȵ����ˣ�����bug
		return false;

	CCRect rect = obj->boundingBox();
	CCPoint p[3] = { ccp(rect.getMidX(), rect.getMinY()), ccp(rect.getMinX(), rect.getMinY()), ccp(rect.getMaxX(), rect.getMinY()) };

	CCRect rect2 = this->boundingBox();

	for (int i = 0; i < 3; i++)
	{
		if ((obj->getVV1() >= 0 && rect2.containsPoint(p[i]) && rect2.getMaxY() - rect.getMinY() < this->getContentSize().height / 5) ||
					(obj->getVV1() < 0 && rect2.containsPoint(p[i]) && rect2.getMaxY() - rect.getMinY() < this->getContentSize().height / 2))
		{
			//������½���΢������ֹ������ײ
			obj->setPositionY(rect2.origin.y + rect2.size.height + 2);
			//�ȵ������ˣ������������һ��(obj)
			obj->jump(300, true);
			return true;
		}
	}
	return false;
}
//��дremoveSelf
void MonsterEnemy::removeSelf()
{ 	
	if (m_Life)
		m_Life = 0;

	if (this->getParent())
	{
		this->removeFromParent();
	}
	
	m_MonsterEnemys->removeObject(this); 
}

//��ײ���
void MonsterEnemy::logic(Biology *obj)
{
	if (m_Life)
	{
		if(isCollisionHeader(obj))//���ȵ��ˣ�����Ϊ0
		{			
			autoDead(obj, 0);
		}
		else if (isCollision(obj))//û�б��ȵ����������������ˣ�����£�
		{
			obj->loseLife();
		}
		else if (isCollisionBrick())
		{
			autoDead(obj, 1);
		}
	}		

	//ÿ�ζ��ж��Ƿ�Ҫ�Ƴ��Լ�
	//this��ê�������ĵ㣬С��0����������ΪС�ڵ�ͼһ��ש��Ŀ�ȣ�32��������-5/32=0�����Բ��ᱨ������ש��Ŀ�ȵĻ��ͻᱨ����		
	if (Common::isOutScreen(getMap(), this, obj->getPositionX()))
	{
		removeSelf();
	}
}
//��ײ���+�ƶ�
void MonsterEnemy::logic(float dt, Biology *obj)
{	
	/*---------------------------������δ��벻�ܷ���logic(Biology*)�����Ϊ��������Ḳдlogic(Biology*)�ⷽ��----------------------*/
	/*---------------------------��ʾ��һ�������Ҫ��дlogic(float dt, Biology *obj)�÷���--------------------------------------------*/
	//�ж��Ƿ�����Ļ�ڣ��ǵĻ���ʼ�ƶ�	
	if (!m_IsRun && Common::isOnScreen(getMap(), this))
	{		
		updateStatus();//����״̬������ſ�ʼ���������ô����ڲ���һ��ʼ����ҪrunAction���Ż����߼���
		m_IsRun = true;
	}
	/*------------------------------------------------------------------------------------------*/
	if (m_Life && m_IsMove)
	{
		move(dt);
	}
	logic(obj);
}

/************************************************************************/
/* Ģ���ֶ���                                                            */
/************************************************************************/
MonsterSmall* MonsterSmall::create(Biology *obj, bool isDiscolor)
{
	MonsterSmall *pRet = new MonsterSmall;
	if (pRet && pRet->init(obj, isDiscolor))
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

bool MonsterSmall::init(Biology *obj, bool isDiscolor)
{
	if (!MonsterEnemy::init(obj)){ return false; }

	m_IsDiscolor = isDiscolor;
	if (m_IsDiscolor)
		initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MonsterSmallBlack"));
	else
		initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MonsterSmall"));
	
	return true;
}
//����������������������һ�ֱ������ģ���һ�ֱ��ӵ������Ļ��߱�ש��������
void MonsterSmall::autoDead(Biology *obj, int num)
{
	addAward(this->getPosition(), false, true, 100);

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[8], false);
	}

	m_Life = 0;
	//��ש�鶥��		
	if (num)
	{
		CCMoveBy *by = CCMoveBy::create(0.2f, ccp(obj->getHV1() * 0.1f, 20));
		CCMoveBy *by2 = CCMoveBy::create(2.0f, ccp(obj->getHV1(), -winSize.width));
		CCRotateBy *rotate = CCRotateBy::create(.8f, 360);
		CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(MonsterEnemy::removeSelf));
		CCSequence *seq = CCSequence::create(by, by2, done, NULL);
		this->runAction(seq);
		this->runAction(CCRepeatForever::create(rotate));		
		return;
	}
	//���ȵ���
	if (m_IsDiscolor)
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MonsterSmallBlackDead"));
	else
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MonsterSmallDead"));
	CCFadeOut *fadeout = CCFadeOut::create(3.0f);
	CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(MonsterEnemy::removeSelf));//��ɺ�Ҫ�Ƴ��Լ�
	CCSequence *seq = CCSequence::create(fadeout, done, NULL);                
	this->runAction(seq);
}

void MonsterSmall::updateStatus()
{	
	if (!m_IsRun)
	{		
		this->schedule(schedule_selector(MonsterSmall::walk), 0.2f);
		m_IsMove = true;
	}
}

void MonsterSmall::walk(float)
{
	if (this->isFlipX())
		this->setFlipX(false);
	else
		this->setFlipX(true);
}

/*void MonsterSmall::logic(Biology *obj)
{
	MonsterEnemy::logic(obj);
}*/

/************************************************************************/
/* �ڹ����                                                              */
/************************************************************************/
Tortoise* Tortoise::create(Biology *obj, int state)
{
	Tortoise *pRet = new Tortoise;
	if (pRet && pRet->init(obj, state))
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

bool Tortoise::init(Biology *obj, int state)
{
	if (!MonsterEnemy::init(obj)){ return false; }
	//����ê��
	this->setAnchorPoint(ccp(0.5f, 0));
	
	//�ڹ���4��״̬,3����ꡢ2�������߹ꡢ1��ǡ�0�����ƶ�	
	m_MoveState = state;
	if (m_MoveState >= 6)
	{		
		m_GrowState = 3;
	}
	else
	{			
		m_GrowState = 2;
	}	
	
	m_IsReviving = false;//Ĭ�ϲ��ø���	
	return true;
}
//��ɹ�Ǻ󸴻�
void Tortoise::revive(float)
{
	m_GrowState = 2;
	m_IsReviving = false;
	updateStatus();
	//CCLog("revive");
}
//������������ײ
bool Tortoise::isCollisionAll(CCArray *arrays)
{
	if (m_GrowState)
		return false;
	CCObject *obj = NULL;
	CCARRAY_FOREACH_REVERSE(arrays, obj)
	{
		Monster *monster = (Monster*)obj;
		if (!monster->getLife() || monster == this)
			continue;

		if (isCollision(monster))
		{				
			monster->autoDead(this, 1);
			if (m_H_v1 < 0)
			{				
				m_H_v1 = m_H_Max_v1;
			}
			else
			{				
				m_H_v1 = -m_H_Max_v1;
			}
			return true;
		}
	}
	return false;
}

//��дˮƽ�����ƶ��Ĵ���
void Tortoise::moveH(float dt)
{
	if (m_MoveState == 9)//����ˮƽ�ƶ�
		return;

	MonsterEnemy::moveH(dt);
}

//��д��ֱ�����ƶ��Ĵ��룬�ڹ�Ƚ�����
void Tortoise::moveV(float dt)
{
	if (m_GrowState == 3)
	{
		if (m_UpScope != 0 || m_DownScope != 0)
		{
			jump(420, 710, false);
		}
		else
		{
			jump();
		}		
	}		
	MonsterEnemy::moveV(dt);
}

void Tortoise::updateStatus()
{
	if (!m_IsRun)//˵���ǵ�һ�ε��ã����ڹ궯����	
		m_IsMove = true;	
	
	this->stopAllActions();	
	switch (m_GrowState)
	{
	case 3:
	{
		this->setDisplayFrameWithAnimationName("TortoiseFlyWalk", 0);
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseFlyWalk"));
		this->runAction(CCRepeatForever::create(animate));

		if (m_H_v1 <= 0)
		{
			this->setFlipX(true);//��������
			m_H_Max_v1 = TORTOISE_H_V_FLY;
			m_H_v1 = -m_H_Max_v1;
		}
		else
		{
			this->setFlipX(false);//��������		
			m_H_Max_v1 = TORTOISE_H_V_FLY;
			m_H_v1 = m_H_Max_v1;
		}
	}
		break;
	case 2:
	{
		this->setDisplayFrameWithAnimationName("TortoiseWalk", 0);
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseWalk"));
		this->runAction(CCRepeatForever::create(animate));

		if (m_H_v1 <= 0)
		{
			this->setFlipX(true);//��������
			m_H_Max_v1 = TORTOISE_H_V;
			m_H_v1 = -m_H_Max_v1;
		}
		else
		{
			this->setFlipX(false);//��������		
			m_H_Max_v1 = TORTOISE_H_V;
			m_H_v1 = m_H_Max_v1;
		}
	}
		break;
	case 1:
		//��ɹ��			
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("TortoiseHull"));
		m_H_v1 = 0;
		m_H_Max_v1 = 0;
		if (!m_IsReviving)
		{
			this->scheduleOnce(schedule_selector(Tortoise::revive), 5.0f);
			if (Common::isPlayEffect)
			{
				SimpleAudioEngine::sharedEngine()->playEffect(effectNames[9], false);
			}
		}			
		//CCLog("m_life = %d", m_Life);
		m_IsReviving = true;
		break;
	case 0:
	{
		//�����ƶ�		
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseCrazy"));
		this->runAction(CCRepeatForever::create(animate));
		//����һЩû��Ҫ���жϣ���Ϊ���Ĺ������ǽ������һ��״̬�������ظ���ֵ
		if (m_H_Max_v1 == 0)
		{
			if (m_H_v1 <= 0)
			{
				m_H_Max_v1 = TORTOISE_H_V_CRAZY;
				m_H_v1 = -m_H_Max_v1;
			}
			else
			{
				m_H_Max_v1 = TORTOISE_H_V_CRAZY;
				m_H_v1 = m_H_Max_v1;
			}
		}
		//CCLog("TortoiseCrazy~~~~~~~~~");
		if (m_IsReviving)
		{
			this->unschedule(schedule_selector(Tortoise::revive));
			m_IsReviving = false;
		}
	}
		break;
	default:
		break;
	} 	
}

void Tortoise::autoDead(Biology *obj , int)
{
	addAward(this->getPosition(), false, true, 200);

	m_Life = 0;
	//��ɹ��	
	this->stopAllActions();
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("TortoiseHull"));
	CCMoveBy *by = CCMoveBy::create(0.2f, ccp(obj->getHV1() * 0.1f, 20));
	CCMoveBy *by2 = CCMoveBy::create(2.0f, ccp(obj->getHV1(), -winSize.width));
	CCRotateBy *rotate = CCRotateBy::create(.8f, 360);
	CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(MonsterEnemy::removeSelf));
	CCSequence *seq = CCSequence::create(by, by2, done, NULL);
	this->runAction(seq);
	this->runAction(CCRepeatForever::create(rotate));

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[9], false);
	}
}

void Tortoise::logic(Biology *obj)
{
	//��ײ����ж�
	if (m_Life)
	{
		if (isCollisionHeader(obj))//���ȵ��ˣ��ɳ�״̬�仯
		{		
			if (m_GrowState == 3)//����Ƿ���꣬���ٷ�
			{
				//m_V_Max_v1 = TORTOISE_V_V;
				m_V_v1 = 0;
				m_V_a = -BIOLOGY_V_A;//���¸������ٶȣ��ָ�Ĭ��
				m_IsFly = false;

				//������ʧЧ
				m_UpScope = 0;
				m_DownScope = 0;
			}

			if (m_GrowState == 0)			
				m_GrowState = 1;//�ڷ����ƶ���ʱ�򱻲��У���Ϊ���				
			else			
				m_GrowState--;
			//���ڹ��ɷ���ƶ�ʱ����һЩ�����ϵĴ���
			if (!m_GrowState)
			{
				CCRect r1 = obj->boundingBox();
				CCRect r2 = this->boundingBox();
				if (r1.getMinX() < r2.getMinX())
				{
					m_H_v1 = 1;//���ڹ����ҷ���ƶ�
				}
				else if (r1.getMaxX() > r2.getMaxX())
				{
					m_H_v1 = -1;//���ڹ��������ƶ�
				}
			}
			//CCLog("%d", m_GrowState);
			updateStatus();
		}
		else if (isCollision(obj))
		{
			if (m_GrowState == 1)//���ǹ�ǵ�ʱ�����������ʱ����ɷ���
			{
				//m_DirRun = obj->getFaceDir();
				//CCLog("%f", obj->getHV1());							
				m_H_v1 = obj->getHV1();//������µ��ٶȸ��ڹ�				
				obj->setHV1(0);//������µ��ٶȽ�Ϊ0
				m_GrowState = 0;//
				updateStatus();//����һ��״̬�������ٶ�
			}
			else
			{
				obj->loseLife();//����¼�����
			}
		}
		else if (isCollisionBrick())
		{			
			//autoDead(obj, 0);			
			Monster::autoDead(obj);
		}

		isCollisionAll(MonsterEnemy::m_MonsterEnemys);
		
	}
	
	//ֻҪ�������趨����Ļ�⣬�Զ�����
	if (m_Life && Common::isOutScreen(getMap(), this, obj->getPositionX()))
	{
		removeSelf();
	}
}

/************************************************************************/
/* ���̹�                                                                */
/************************************************************************/
Backstab* Backstab::create(Biology *obj)
{
	Backstab *pRet = new Backstab;
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

bool Backstab::init(Biology *obj)
{
	if (!MonsterEnemy::init(obj)){ return false; }

	this->setDisplayFrameWithAnimationName("Backstab", 0);//����д��updateStatus������

	return true;
}

void Backstab::updateStatus()
{
	if (!m_IsRun)//˵���ǵ�һ�ε��ã����ڹ궯����
	{
		m_IsMove = true;
	}

	this->stopAllActions();

	CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Backstab"));
	this->runAction(CCRepeatForever::create(animate));
	if (m_H_v1 <= 0)
	{
		this->setFlipX(true);//��������		
	}
	else
	{
		this->setFlipX(false);//��������			
	}
}

void Backstab::autoDead(Biology *obj, int)
{
	addAward(this->getPosition(), false, true, 200);

	m_Life = 0;
	//ֹͣ���ж�������ת�����ƶ�����
	this->stopAllActions();
	//this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Backstab"));
	CCMoveBy *by = CCMoveBy::create(0.2f, ccp(obj->getHV1() * 0.1f, 20));
	CCMoveBy *by2 = CCMoveBy::create(2.0f, ccp(obj->getHV1(), -winSize.width));
	CCRotateBy *rotate = CCRotateBy::create(.8f, 360);
	CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(MonsterEnemy::removeSelf));
	CCSequence *seq = CCSequence::create(by, by2, done, NULL);
	this->runAction(seq);
	this->runAction(CCRepeatForever::create(rotate));
}

void Backstab::logic(Biology *obj)
{
	if (m_Life)
	{
		if (isCollision(obj))//û�б��ȵ����������������ˣ�����£�
		{
			obj->loseLife();
		}
		else if (isCollisionBrick())
		{
			autoDead(obj, 1);
		}
	}

	//ֻҪ�����趨��Χ�⣬�Զ�����
	if (Common::isOutScreen(getMap(), this, obj->getPositionX()))
	{
		removeSelf();
	}
}

/************************************************************************/
/* ¥��                                                                */
/************************************************************************/
Stair* Stair::create(Biology *obj, int dir)
{
	Stair *pRet = new Stair;
	if (pRet && pRet->init(obj, dir))
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

bool Stair::init(Biology *obj, int dir)
{
	if (!MonsterEnemy::init(obj)){ return false; }

	m_Dir = dir;
	if (m_Dir == -1)
	{
		//ֻ�����»�����
		m_H_Max_v1 = BIOLOGY_H_V;
		m_H_v1 = -m_V_Max_v1;
		m_H_a = 0;

		m_V_Max_v1 = BIOLOGY_H_V *1.3f;
		m_V_v1 = -m_V_Max_v1;
		m_V_a = 0;
	}
	else if (m_Dir == 1)
	{
		//ֻ�����ϻ�����
		m_H_Max_v1 = BIOLOGY_H_V;
		m_H_v1 = m_V_Max_v1;
		m_H_a = 0;

		m_V_Max_v1 = BIOLOGY_H_V *1.3f;
		m_V_v1 = m_V_Max_v1;
		m_V_a = 0;
	}	

	CCSprite *spr1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Stair"));
	spr1->setAnchorPoint(ccp(0, 0));
	CCSprite *spr2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Stair"));
	spr2->setPositionX(spr1->getContentSize().width);
	spr2->setAnchorPoint(ccp(0, 0));

	this->setAnchorPoint(ccp(0, 0));
	this->addChild(spr1);
	this->addChild(spr2);
	this->setContentSize(CCSizeMake(spr1->getContentSize().width * 2, spr1->getContentSize().height));	

	//m_IsMove = true;//��ʼ����������ƶ�
	m_IsOnLadders = false;
	return true;
}
/* ״̬���� */
void Stair::updateStatus()
{		
	if (!m_IsRun)
	{
		m_IsMove = true;
	}
}

/* �������߼� */
void Stair::logic(Biology *obj)
{
	//ֻҪ�����趨��Χ�⣬�Զ�����
	if (obj->getPositionX() > this->getPositionX() + winSize.width * 3 / 2)
	{
		removeSelf();
	}
}
void Stair::calcX(float dt)
{
	float s = m_H_v1 * dt;
	//CCLog("%p,%g", this, m_H_v1);
	// �ж�������ǲ��ǲ���������
	CCRect rect = this->boundingBox();
	if (m_H_v1 < 0)
		rect.size.height += -s + 1;
	else
		rect.size.height += s + 1;

	if (rect.intersectsRect(m_Biology->boundingBox()))
	{
		m_Biology->setPositionX(m_Biology->getPositionX() + s);
		if (!m_IsOnLadders)
			m_IsOnLadders = true;
	}
	else if (m_IsOnLadders)
		m_IsOnLadders = false;

	this->setPositionX(this->getPositionX() + s);
	if (m_IsOnLadders)
	{
		this->mapMoveH(m_Biology, s);
	}	
}

//�����ƶ��Ľ���
void Stair::moveH(float dt)
{	
	if (m_LeftScope != 0 || m_RightScope != 0)
	{
		calcX(dt);
	}
	if (m_Dir == -1 && m_LeftScope != 0)
	{		
		if (this->getPositionX() <= m_LeftScope)
		{
			m_Dir = 1;
			m_H_v1 = m_H_Max_v1;//�ƶ����̶�λ�ú��ٶȷ�����			
		}
	}
	else if (m_Dir == 1 && m_RightScope != 0)
	{		
		if (this->getPositionX() >= m_RightScope)
		{
			m_Dir = -1;
			m_H_v1 = -m_H_Max_v1;//�ƶ����̶�λ�ú��ٶȷ�����			
		}
	}	
}
//�����ƶ��Ľ���
void Stair::moveV(float dt)
{	
	if (m_UpScope != 0 || m_DownScope != 0)
	{
		float s = m_V_v1 * dt;

		/* �ж�������ǲ��ǲ��������� */
		CCRect rect = this->boundingBox();
		if (m_V_v1 < 0)
			rect.size.height += -s + 1;
		else
			rect.size.height += s + 1;

		if (rect.intersectsRect(m_Biology->boundingBox()))
		{
			m_Biology->setPositionY(m_Biology->getPositionY() + s - 1);//˵�������������
			if (!m_IsOnLadders)
				m_IsOnLadders = true;
		}
		else if (m_IsOnLadders)
			m_IsOnLadders = false;

		/*---------------------------------------------*/
		this->setPositionY(this->getPositionY() + s);
		if (m_IsOnLadders)
			this->mapMoveV(m_Biology, s);
	}

	if (m_Dir == 1 && m_UpScope != 0)
	{
		if (this->getPositionY() >= m_UpScope)
		{
			this->setPositionY(m_DownScope);			
			//CCLog("up movev %g,%g,%g", m_DownScope, m_UpScope, m_V_v1);
		}
	}		
	else if (m_Dir == -1 && m_DownScope != 0)
	{		
		if (this->getPositionY() <= m_DownScope)
		{
			this->setPositionY(m_UpScope);		
			//CCLog("down movev %g", m_UpScope);
		}
	}	
}

//��д��ײ���+�ƶ������ֵ�������һ��
void Stair::logic(float dt, Biology *obj)
{	
	//�ж��Ƿ�����Ļ�ڣ��ǵĻ���ʼ�ƶ�	
	if (!m_IsRun && getMap()->convertToWorldSpace(this->getPosition()).x < winSize.width + this->getContentSize().width / 2)
	{
		updateStatus();//����״̬������ſ�ʼ���������ô����ڲ���һ��ʼ����ҪrunAction���Ż����߼���
		m_IsRun = true;
	}
	/*------------------------------------------------------------------------------------------*/
	if (m_Life && m_IsMove)
	{
		move(dt);
	}
	logic(obj);
}

/************************************************************************/
/* �ڵ�                                                                 */
/************************************************************************/
Cannon* Cannon::create(Biology *obj)
{
	Cannon *pRet = new Cannon;
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
bool Cannon::init(Biology *obj)
{
	if (!MonsterEnemy::init(obj)){ return false; }

	m_IsDefaultFace = true;
	return true;
}

void Cannon::updateStatus()
{
	if (!m_IsRun)
	{
		schedule(schedule_selector(Cannon::shoot), 3.0f + CCRANDOM_0_1()*0.5f);
	}
}

void Cannon::shoot(float)
{
	CannonBullet *bullet = CannonBullet::create(m_Biology);
	bullet->setPosition(ccp(this->getPositionX() + 8, this->getPositionY() + 8));
	bullet->setRunDir(m_IsDefaultFace);
	getMap()->addChild(bullet);
	MonsterBullet::m_Bullets->addObject(bullet);
	//CCLog("CannonBullet shoot");
}

void Cannon::logic(Biology *obj)
{
	//��ײ����ж�
	if (m_Life)
	{
		if (isCollision(obj))
		{
			obj->loseLife();//����¼�����			
		}

		//�ж�������ǲ��ǳ����ڵ�
		if (obj->getPositionX() > this->getPositionX() && m_IsDefaultFace)
		{
			m_IsDefaultFace = false;			
		}
		else if (obj->getPositionX() <= this->getPositionX() && !m_IsDefaultFace)
		{
			m_IsDefaultFace = true;		
		}
	}

	//ֻҪ�����趨��Χ�⣬�Զ�����
	if (Common::isOutScreen(getMap(), this, obj->getPositionX()))
	{
		removeSelf();
	}
}
/************************************************************************/
/* �ֿ������                                                              */
/************************************************************************/
Helmet* Helmet::create(Biology *obj)
{
	Helmet *pRet = new Helmet;
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

bool Helmet::init(Biology *obj)
{
	if (!MonsterEnemy::init(obj)){ return false; }
	//����ê��
	this->setAnchorPoint(ccp(0.5f, 0));

	//�ֿ�����3��״̬,2�������߹ꡢ1��ǡ�0�����ƶ�		
	m_GrowState = 2;	

	m_IsReviving = false;//Ĭ�ϲ��ø���	
	return true;
}
//��ɹ�Ǻ󸴻�
void Helmet::revive(float)
{
	m_GrowState = 2;
	m_IsReviving = false;
	updateStatus();
	//CCLog("revive");
}

void Helmet::updateStatus()
{
	if (!m_IsRun)//˵���ǵ�һ�ε��ã����ڹ궯����	
		m_IsMove = true;

	this->stopAllActions();
	switch (m_GrowState)
	{	
	case 2:
	{
			  this->setDisplayFrameWithAnimationName("HelmetWalk", 0);
			  CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("HelmetWalk"));
			  this->runAction(CCRepeatForever::create(animate));

			  if (m_H_v1 <= 0)
			  {
				  this->setFlipX(true);//��������
				  m_H_Max_v1 = TORTOISE_H_V;
				  m_H_v1 = -m_H_Max_v1;
			  }
			  else
			  {
				  this->setFlipX(false);//��������		
				  m_H_Max_v1 = TORTOISE_H_V;
				  m_H_v1 = m_H_Max_v1;
			  }
	}
		break;
	case 1:
		//��ɹ��			
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("HelmetHull"));
		m_H_v1 = 0;
		m_H_Max_v1 = 0;
		if (!m_IsReviving)
			this->scheduleOnce(schedule_selector(Helmet::revive), 5.0f);
		//CCLog("m_life = %d", m_Life);
		m_IsReviving = true;
		break;
	case 0:
	{
			  //�����ƶ�		
			  CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("HelmetCrazy"));
			  this->runAction(CCRepeatForever::create(animate));
			  //����һЩû��Ҫ���жϣ���Ϊ���Ĺ������ǽ������һ��״̬�������ظ���ֵ
			  if (m_H_Max_v1 == 0)
			  {
				  if (m_H_v1 <= 0)
				  {
					  m_H_Max_v1 = TORTOISE_H_V_CRAZY;
					  m_H_v1 = -m_H_Max_v1;
				  }
				  else
				  {
					  m_H_Max_v1 = TORTOISE_H_V_CRAZY;
					  m_H_v1 = m_H_Max_v1;
				  }
			  }
			  //CCLog("TortoiseCrazy~~~~~~~~~");
			  if (m_IsReviving)
			  {
				  this->unschedule(schedule_selector(Helmet::revive));
				  m_IsReviving = false;
			  }
	}
		break;
	default:
		break;
	}
}

void Helmet::autoDead(Biology *obj, int num)
{
	//���ӵ�����������
	if (num)	
		return;	

	addAward(this->getPosition(), false, true, 200);

	m_Life = 0;
	//��ɹ��	
	this->stopAllActions();
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("HelmetHull"));
	CCMoveBy *by = CCMoveBy::create(0.2f, ccp(obj->getHV1() * 0.1f, 20));
	CCMoveBy *by2 = CCMoveBy::create(2.0f, ccp(obj->getHV1(), -winSize.width));
	CCRotateBy *rotate = CCRotateBy::create(.8f, 360);
	CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(MonsterEnemy::removeSelf));
	CCSequence *seq = CCSequence::create(by, by2, done, NULL);
	this->runAction(seq);
	this->runAction(CCRepeatForever::create(rotate));
}

void Helmet::logic(Biology *obj)
{
	//��ײ����ж�
	if (m_Life)
	{
		if (isCollisionHeader(obj))//���ȵ��ˣ��ɳ�״̬�仯
		{
			if (m_GrowState == 0)
				m_GrowState = 1;//�ڷ����ƶ���ʱ�򱻲��У���Ϊ���				
			else
				m_GrowState--;
			//���ڹ��ɷ���ƶ�ʱ����һЩ�����ϵĴ���
			if (!m_GrowState)
			{
				CCRect r1 = obj->boundingBox();
				CCRect r2 = this->boundingBox();
				if (r1.getMinX() < r2.getMinX())
				{
					m_H_v1 = 1;//���ڹ����ҷ���ƶ�
				}
				else if (r1.getMaxX() > r2.getMaxX())
				{
					m_H_v1 = -1;//���ڹ��������ƶ�
				}
			}
			//CCLog("%d", m_GrowState);
			updateStatus();
		}
		else if (isCollision(obj))
		{
			if (m_GrowState == 1)//���ǹ�ǵ�ʱ�����������ʱ����ɷ���
			{
				//m_DirRun = obj->getFaceDir();
				//CCLog("%f", obj->getHV1());
				m_H_v1 = obj->getHV1();//������µ��ٶȸ��ڹ�				
				obj->setHV1(0);//������µ��ٶȽ�Ϊ0
				m_GrowState = 0;//
				updateStatus();//����һ��״̬�������ٶ�
			}
			else
			{
				obj->loseLife();//����¼�����
			}
		}
		else if (isCollisionBrick())
		{
			//autoDead(obj, 0);			
			Monster::autoDead(obj);
		}
	}

	//ֻҪ�������趨����Ļ�⣬�Զ�����
	if (m_Life && Common::isOutScreen(getMap(), this, obj->getPositionX()))
	{
		removeSelf();
	}
}

/************************************************************************/
/* boss����                                                             */
/************************************************************************/
Boss* Boss::create(Biology *obj)
{
	Boss *pRet = new Boss;
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

bool Boss::init(Biology *obj)
{
	if (!MonsterEnemy::init(obj)){ return false; }

	this->setDisplayFrameWithAnimationName("BossWalk", 0);
	
	m_Life = 2;
	m_IsRun = false;
	m_JumpCount = CCRANDOM_0_1() * 2 + 2.0f;//��Ծ����
	m_CurJumpCount = 0;

	m_IsDefaultFace = true;//Ĭ��������
	return true;
}

void Boss::updateStatus()
{
	if (!m_IsRun)
	{
		if (!m_IsMove)
		{
			m_IsMove = true;
			schedule(schedule_selector(Boss::jump), 0.1f);
		}
				
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("BossWalk"));
		CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(Boss::shoot));
		this->runAction(CCSequence::create(animate, done, NULL));
		m_IsRun = true;
	}	

	if (m_IsDefaultFace)
	{
		this->setFlipX(true);//��������	
	}
	else
	{
		this->setFlipX(false);//��������	
	}
}

void Boss::jump(float dt)
{ 
	m_CurJumpCount += dt;
	if (m_CurJumpCount >= m_JumpCount)
	{
		Biology::jump(350, false);
		m_CurJumpCount = 0;
		m_JumpCount = CCRANDOM_0_1() * 2 + 2.0f;
	}	
}

void Boss::shoot()
{
	BossBullet *bullet = BossBullet::create(m_Biology);
	bullet->setPosition(ccp(this->getPositionX(), this->getPositionY() + 5));
	bullet->setRunDir(m_IsDefaultFace);
	getMap()->addChild(bullet);
	MonsterBullet::m_Bullets->addObject(bullet);
	//CCLog("boss shoot");

	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BossShoot"));
	this->scheduleOnce(schedule_selector(Boss::shootFinish), CCRANDOM_0_1() + 0.6f);
}

void Boss::shootFinish(float)
{
	m_IsRun = false;
	updateStatus();
}

void Boss::autoDead(Biology *obj, int)
{
	if (isGodMode())
		return;
	m_Life--;
	if (m_Life)	//��û����
	{
		startGodMode();
		return;
	}		
	
	//ֹͣ���ж�������ת�����ƶ�����
	this->stopAllActions();	
	CCMoveBy *by = CCMoveBy::create(0.2f, ccp(obj->getHV1() * 0.1f, 20));
	CCMoveBy *by2 = CCMoveBy::create(2.0f, ccp(obj->getHV1(), -winSize.width));
	CCRotateBy *rotate = CCRotateBy::create(.8f, 360);
	CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(MonsterEnemy::removeSelf));
	CCSequence *seq = CCSequence::create(by, by2, done, NULL);
	this->runAction(seq);
	this->runAction(CCRepeatForever::create(rotate));

	this->scheduleOnce(schedule_selector(Boss::deadfinish), 2.0f);
}

void Boss::deadfinish(float)
{
	*m_IsDead = true;
}

void Boss::logic(Biology *obj)
{
	//��ײ����ж�
	if (m_Life)
	{		
		if (isCollision(obj))
		{			
			obj->loseLife();//����¼�����			
		}

		//�ж�������ǲ��ǳ���boss
		if (obj->getPositionX() > this->getPositionX() && m_IsDefaultFace)
		{
			m_IsDefaultFace = false;
			updateStatus();
		}
		else if (obj->getPositionX() < this->getPositionX() && !m_IsDefaultFace)
		{
			m_IsDefaultFace = true;
			updateStatus();
		}
	}
	
	//ֻҪ�����趨��Χ�⣬�Զ�������boss������������
	/*if (Common::isOutScreen(getMap(), this, obj->getPositionX()))
	{
		removeSelf();
	}*/
}
