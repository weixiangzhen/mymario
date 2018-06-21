#include "Mario.h"
#include "MarioBullet.h"

void Mario::preload()
{	
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("mario.png");	
	{/* С�������� */
		CCArray* arr = CCArray::create();

		//���߶���
		CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_SMALL_RECT_WALKING1);
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_SMALL_RECT_DAFAULT);
		arr->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr, 0.1f), "SmallMarioWalk");

		//��Ծ֡
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_SMALL_RECT_JUMP);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "SmallMarioJump");

		//ɲ��֡
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_SMALL_RECT_BRAKING);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "SmallMarioBaking");

		//ֹͣ����
		CCArray* arr2 = CCArray::create();
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_SMALL_RECT_STOPWALK1);
		arr2->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_SMALL_RECT_DAFAULT);
		arr2->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr2, 0.1f), "SmallMarioStop");
	}

	{/* ����������1 */
		CCArray* arr = CCArray::create();

		//���߶���
		CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG1_RECT_WALKING1);
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG1_RECT_DAFAULT);
		arr->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr, 0.1f), "Big1MarioWalk");

		//��Ծ֡
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG1_RECT_JUMP);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "Big1MarioJump");

		//ɲ��֡
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG1_RECT_BRAKING);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "Big1MarioBaking");

		//ֹͣ����
		CCArray* arr2 = CCArray::create();
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG1_RECT_STOPWALK1);
		arr2->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG1_RECT_DAFAULT);
		arr2->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr2, 0.1f), "Big1MarioStop");
	}

	{/* ����������1 */
		CCArray* arr = CCArray::create();

		//���߶���
		CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG2_RECT_WALKING1);
		arr->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG2_RECT_DAFAULT);
		arr->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr, 0.1f), "Big2MarioWalk");

		//��Ծ֡
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG2_RECT_JUMP);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "Big2MarioJump");

		//ɲ��֡
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG2_RECT_BRAKING);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "Big2MarioBaking");

		//ֹͣ����
		CCArray* arr2 = CCArray::create();
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG2_RECT_STOPWALK1);
		arr2->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_BIG2_RECT_DAFAULT);
		arr2->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr2, 0.1f), "Big2MarioStop");
	}

	{//����֡		
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_RECT_DEAD);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MarioDead");		
	}	

	{//�����ӵ�֡		
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(pTexture, MARIO_RECT_SHOOT);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MarioShoot");
	}
}

bool Mario::init()
{
	if (!Figure::init()){ return false; }

	m_State = M_NONE;//��ʼ��Ϊû������	

	m_GrowState = 0;
	//����
	m_Life = 1;	
	//ˮƽ������ٶȺ��ٶ�
	m_H_Max_v1 = MARIO_H_MAX_V;
	m_H_a = MARIO_H_A;
	m_H_v1 = 0;

	//��ֱ����ļ��ٶȺ��ٶ�
	m_V_Max_v1 = MARIO_V_MAX_V;
	m_V_a = MARIO_V_A;
	m_V_v1 = 0;

	m_IsFly = false;

	m_IsReadyShoot = true;	
	m_ShootCount = 0;	

	this->scheduleUpdate();	
	this->setDisplayFrameWithAnimationName("SmallMarioWalk", 1);	
	return true;
}

/* ��Ծ */
void Mario::jump(float vv, bool isIgnore)
{
	if (m_Life <= 0 || m_IsAutoRun)
		return;

	if (!isIgnore && m_IsFly)	
		return;	

	m_IsFly = true;
	m_V_v1 = vv;
	//m_V_a = -MARIO_V_A;
	m_V_a = m_V_a > 0 ? -m_V_a : m_V_a;
	updateStatus();

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[6], false);
	}
}

/* �����ӵ� */
void Mario::shoot()
{
	Bullet *bullet = NULL;
	if (m_GrowState == 2)
	{
		//��ͨ�ӵ�				
		bullet = Bullet::create();//�����ӵ�����		
	}
	else if (m_GrowState >= 3)
	{
		//���ӵ�
		bullet = IceBullet::create();
	}
	/*else if (m_GrowState == 4)
	{
	//��ͨ�ӵ�+50%���ʴ��������ý��
	}
	else if (m_GrowState == 5)
	{
	//��ͨ�ӵ�+����������4�����򷢳�һ���ӵ�
	}
	else if (m_GrowState == 6)
	{
	//��ͨ�ӵ�+���ٹ���
	}
	else if (m_GrowState == 7)
	{
	//�������£������׵�
	}
	else if (m_GrowState == 8)
	{
	//��ͨ�ӵ�+����������
	}
	else if (m_GrowState >= 9)
	{
	//��ͨ�ӵ�+����1���������ָ����Լ�
	}*/
	if (bullet == NULL)
		return;	
	bullet->setPosition(ccp(this->getPositionX() + this->getContentSize().width / 2, this->getPositionY() + 40));
	bullet->setRunDir(m_IsLeftFace);
	getMap()->addChild(bullet);
	Bullet::m_Bullets->addObject(bullet);	

	this->stopAllActions();
	setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MarioShoot"));
	scheduleOnce(schedule_selector(Mario::restoreNomal), 0.1f);

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[4], false);
	}
}

void Mario::setShoot(bool b)
{
	/*if (m_Life <= 0 || m_IsAutoRun)
	{
		if (m_IsShoot)
		{
			unschedule(schedule_selector(Mario::shoot));
			m_IsShoot = false;
		}
		return;
	}*/
	if (m_GrowState < 2)
		return;

	if (m_IsShoot == b)//��ֹ�ظ������ӵ�	
		return;
	
	m_IsShoot = b;
	/*if (m_IsShoot && m_IsReadyShoot)
	{
		m_ShootCount = 0;
		m_IsReadyShoot = false;
		shoot();
	}*/
	/*if (m_IsShoot)
	{
		if (m_GrowState >= 2)
		{			
			schedule(schedule_selector(Mario::shoot), 0.3f);
			shoot(0.0f);
		}
	}
	else
	{
		unschedule(schedule_selector(Mario::shoot));
	}	*/
}
/*************************************************************************/
/* �ٶȹ�ʽ��v2=v1+at                                                     */
/* λ��ʱ�乫ʽ��s=(v1+v2)*t/2=(2v1+at)*t/2=v1*t+1/2at^2                  */
/* λ���ٶȹ�ʽ��2as=v2^2-v1^2                                            */
/************************************************************************/
void Mario::calcX(float dt)
{
	//dtʱ���λ��
	float s = m_H_v1 * dt + m_H_a *dt*dt / 2;
	m_H_v1 = m_H_v1 + m_H_a * dt;//dtʱ���ٶ�
	//CCLog("%g", m_H_v1);

	this->mapMoveH(this, s);

	this->setPositionX(this->getPositionX() + s);
	if (this->getPositionX() < 0)
	{
		//΢��	
		this->setPositionX(0);
	}
}

void Mario::calcY(float dt)
{
	//dtʱ���λ��
	float s = m_V_v1 * dt + m_V_a *dt*dt / 2;
	m_V_v1 = m_V_v1 + m_V_a * dt;//dtʱ���ٶ�
	//CCLog("%g", m_V_v1);

	this->mapMoveV(this, s);
	this->setPositionY(this->getPositionY() + s);
}

void Mario::moveV(float dt)
{
	//��ֱ������ƶ��ж�
	if (m_V_v1 <= 0)//����
	{
		if (m_IsFly)
			calcY(dt);//�����䣬�ڽ�����ײ��⣬��ֹ�������ߵ�ʱ�����ж�		
		if (this->_isCollisionDown())
		{
			//CCLog("mario mario,%p", this);
			if (m_IsFly)
			{
				m_IsFly = false;
				m_V_v1 = 0;
				updateStatus();
			}
		}
		else
		{
			if (!m_IsFly)
			{
				m_IsFly = true;
				m_V_v1 = 0;
				//m_V_a = -MARIO_V_A;
				m_V_a = m_V_a > 0 ? -m_V_a : m_V_a;
				updateStatus();
			}
			if (m_V_v1 <= -m_V_Max_v1*1.5f)
			{
				m_V_v1 = -m_V_Max_v1*1.5f;
				//CCLog("%g", m_V_v1);	
			}
		}
	}
	else//����
	{
		calcY(dt);
		if (_isCollisionUp())
		{			
			m_V_v1 = 0;
			//m_V_a = -MARIO_V_A;
			m_V_a = m_V_a > 0 ? -m_V_a : m_V_a;
		}
	}
}

void Mario::moveH(float dt)
{
	//ˮƽ������ƶ��ж�
	if (m_DirRun == MOVE_LEFT)
	{
		//��һ�������ж�ˮƽ�ٶ��Ƿ����0���ڶ�������Ϊ�����ж�
		if ((m_H_v1 > 0 && m_State != M_LEFTBRAKING))
		{
			m_IsLeftFace = true;
			m_State = M_LEFTBRAKING;
			//m_H_a = -MARIO_H_A;
			m_H_a = m_H_a > 0 ? -m_H_a : m_H_a;
			updateStatus();
		}
		else if (m_H_v1 <= 0 && m_State != M_LEFT)
		{
			m_IsLeftFace = true;
			m_State = M_LEFT;
			//m_H_a = -MARIO_H_A;
			m_H_a = m_H_a > 0 ? -m_H_a : m_H_a;
			updateStatus();
		}

		if (m_H_v1 <= -m_H_Max_v1)
			m_H_v1 = -m_H_Max_v1;
		//�����ɲ���Ļ�������ʹ���ұ���Ϊ�ж�
		if (m_H_v1 > 0)
		{
			this->calcX(dt);
			_isCollisionRight();
		}
		else
		{
			this->calcX(dt);
			if (_isCollisionLeft())
			{
				m_H_v1 = 0;//����ǽ���ٶ�����Ϊ0
			}
		}

		//m_DirRun = MOVE_NONE;
	}
	else if (m_DirRun == MOVE_RIGHT)
	{
		//��һ�������ж�ˮƽ�ٶ��Ƿ�С��0���ڶ�������Ϊ�����ж�	
		if (m_H_v1 < 0 && m_State != M_RIGHTBRAKING)
		{
			m_IsLeftFace = false;
			m_State = M_RIGHTBRAKING;
			//m_H_a = MARIO_H_A;
			m_H_a = m_H_a > 0 ? m_H_a : -m_H_a;
			updateStatus();
		}
		else if (m_H_v1 >= 0 && m_State != M_RIGHT)
		{
			m_IsLeftFace = false;
			m_State = M_RIGHT;
			//m_H_a = MARIO_H_A;
			m_H_a = m_H_a > 0 ? m_H_a : -m_H_a;
			updateStatus();
		}

		if (m_H_v1 >= m_H_Max_v1)
		{
			m_H_v1 = m_H_Max_v1;
			//CCLog("%g", m_H_v1);
		}

		//�����ɲ���Ļ�������ʹ�������Ϊ�ж�
		if (m_H_v1 < 0)
		{
			this->calcX(dt);
			_isCollisionLeft();
		}
		else
		{
			this->calcX(dt);
			if (_isCollisionRight())
			{
				m_H_v1 = 0;
			}
		}
		//m_DirRun = MOVE_NONE;
	}
	else
	{
		if (m_State != M_NONE)
		{
			m_State = M_NONE;
			m_H_v1 = 0;
			updateStatus();
		}
	}
}

//�����ƶ��ķ����������������������
void Mario::move(float dt)
{
	//��ֱ����
	moveV(dt);

	//ˮƽ����
	moveH(dt);	
}

void Mario::update(float dt)
{
	//����Ϊ0�������������������
	if (m_Life <= 0 || this->getPositionY() <= 0)//�ж��Ƿ�������
	{
		m_Life = 0;//��Ϊthis->getPositionY() <= 0�Ļ���û�а�������λ0
		dead();//����
		return;
	}
	//�����յ�վ���Զ�����
	if (m_IsAutoRun)
	{
		if (m_DirRun != MOVE_RIGHT)
			m_DirRun = MOVE_RIGHT;
		if (this->getPositionX() > m_RunDistance)
			return;
	}

	//�ж��Ƿ�ִ����Ծ
	if (m_IsJump)
	{
		jump();
	}
	//�ж��Ƿ�ִ�з����ӵ�
	if (!m_IsReadyShoot)
	{
		m_ShootCount += dt;
		if (m_ShootCount >= 0.3f)
		{
			m_IsReadyShoot = true;
			m_ShootCount = 0;
		}
	}
	else if (m_IsShoot)
	{		
		shoot();
		m_IsReadyShoot = false;		
	}	
	//�ƶ�
	move(dt);
}

void Mario::walking()
{	
	//this->setDisplayFrameWithAnimationName("SmallMarioWalk", 0);
	CCAnimate *animate;
	if(m_GrowState == 0)
		animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("SmallMarioWalk"));
	else if (m_GrowState == 1)
		animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Big1MarioWalk"));
	else
		animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Big2MarioWalk"));
	this->runAction(CCRepeatForever::create(animate));
}

void Mario::stopWalk()
{	
	/*CCAnimate *animate;
	if(m_GrowState == 0)
		animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("SmallMarioStop"));
	else if (m_GrowState == 1)
		animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Big1MarioStop"));
	else
		animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Big2MarioStop"));
	this->runAction(animate);*/
	if (m_GrowState == 0)
		setDisplayFrameWithAnimationName("SmallMarioStop", 1);
	else if (m_GrowState == 1)
		setDisplayFrameWithAnimationName("Big1MarioStop", 1);
	else
		setDisplayFrameWithAnimationName("Big2MarioStop", 1);
}

void Mario::updateStatus()
{	
	this->stopAllActions();
	//���·��е�״̬
	if (m_IsFly)
	{
		if (m_IsLeftFace && !isFlipX())		
			this->setFlipX(true);		
		else if (!m_IsLeftFace && isFlipX())		
			this->setFlipX(false);
		
		if (m_GrowState == 0)
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SmallMarioJump"));
		else if (m_GrowState == 1)
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Big1MarioJump"));
		else
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Big2MarioJump"));
		return;
	}
	
	//�������ߵ�״̬
	if (m_State == M_LEFT)
	{
		this->setFlipX(true);
		walking();
	}
	else if (m_State == M_LEFTBRAKING)
	{
		//��ʾ�����������ɲ��		
		this->setFlipX(false);
		if (m_GrowState == 0)
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SmallMarioBaking"));
		else if (m_GrowState == 1)
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Big1MarioBaking"));
		else
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Big2MarioBaking"));
	}
	else if (m_State == M_RIGHT)
	{
		this->setFlipX(false);
		walking();
	}
	else if (m_State == M_RIGHTBRAKING)
	{
		//��ʾ�����������ɲ��		
		this->setFlipX(true);
		if (m_GrowState == 0)
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SmallMarioBaking"));
		else if (m_GrowState == 1)
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Big1MarioBaking"));
		else
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Big2MarioBaking"));
	}
	else
	{
		if (m_IsLeftFace)		
			this->setFlipX(true);		
		else		
			this->setFlipX(false);
		//CCLog("stop");
		//����
		stopWalk();
	}
}

//��дboundingBox
CCRect Mario::boundingBox()
{
	CCRect rect = CCSprite::boundingBox();
	//CCLog("%g,%g", rect.size.width, rect.size.height);
	if (m_GrowState == 0)
	{
		rect.origin.x += 19;
		rect.origin.y += 0;
		rect.size.width -= 37;
		rect.size.height -= 34;
	}
	else if (m_GrowState == 1)
	{
		rect.origin.x += 16;
		rect.origin.y += 0;
		rect.size.width -= 31;
		rect.size.height -= 12;
	}
	else
	{
		rect.origin.x += 16;
		rect.origin.y += 0;
		rect.size.width -= 31;
		rect.size.height -= 10;
	}

	return rect;
}

//��дsetGrowState
void Mario::setGrowState(int state, bool isIgnore)
{
	this->m_GrowState = state;
	updateStatus();

	if (isIgnore)
		return;
	m_H_v1 = 0;	
	startGodMode();
}

//�޵�ʱ�Ϳ�ʼ��˸����ʾ�޵�
void Mario::godmodeing(float dt)
{	
	Biology::godmodeing(dt);

	if (!isGodMode())
	{
		this->setColor(ccc3(255, 255, 255));
		return;
	}

	if (this->getColor().b == 255)
	{
		this->setColor(ccc3(255, 0, 0));
	}
	else
	{
		this->setColor(ccc3(255, 255, 255));
	}	
}

//��дloseLife
void Mario::loseLife()
{
	if (isAutoRun())//�Ѿ�Ӯ�ˣ���ײ��Ҳû��Ч��	
		return;
	
	//�޵�״ֱ̬�ӷ���
	if (m_IsGodMode) return;
		
	if (m_GrowState > 1)
	{
		m_GrowState = 1;
		setGrowState(m_GrowState);
	}
	else if (m_GrowState == 1)
	{
		m_GrowState = 0;
		setGrowState(m_GrowState);
	}
	else
	{
		m_Life--;
	}
}

//�����ķ���
void Mario::dead()
{	
	unscheduleUpdate();

	this->stopAllActions();
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MarioDead"));
	CCMoveBy *by1 = CCMoveBy::create(0.3f, ccp(0, 80));
	CCMoveBy *by2 = CCMoveBy::create(3.0f, ccp(0, -winSize.width));
	CCSequence *seq = CCSequence::create(by1, by2, NULL);
	this->runAction(seq);

	this->scheduleOnce(schedule_selector(Mario::dieFinish), 2.0f);
	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[10], false);
	}

	if (Common::isPlayMusic)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
}

void Mario::dieFinish(float)
{
	m_IsDead = true;
}

/************************************************************************/
/* ʷ̩��                                                               */
/************************************************************************/
void Stallone::preload()
{	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("stallone.plist");
	{/* ʷ̩������ */
		CCArray* arr = CCArray::create();
		//���߶���
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run_1.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run_2.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run_3.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run_4.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run_5.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run_6.png");
		arr->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr, 0.1f), "StalloneWalk");

		arr->removeAllObjects();
		//��Ծ֡
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump_1.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump_2.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump_3.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump_4.png");
		arr->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr, 0.1f), "StalloneJump");		
	}

	{//����֡		
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("drop.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "StalloneDead");
	}

	{//�����ӵ�����	
		CCArray* arr = CCArray::create();
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("normal.png");
		arr->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("normalS.png");
		arr->addObject(frame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(arr, 0.1f), "StalloneNormalShoot");
	}
}

bool Stallone::init()
{
	if (!Figure::init()){ return false; }

	m_State = MOVE_NONE;

	m_GrowState = 0;
	//����
	m_Life = 1;
	//ˮƽ������ٶȺ��ٶ�
	m_H_a = STALLONE_H_A;
	m_H_Max_v1 = STALLONE_H_MAX_V;
	m_H_v1 = 0;

	//��ֱ����ļ��ٶȺ��ٶ�
	m_V_a = STALLONE_V_A;
	m_V_Max_v1 = STALLONE_V_MAX_V;
	m_V_v1 = 0;

	m_IsFly = false;
	m_IsFlyRunning = false;

	m_IsReadyShoot = false;
	m_ShootCount = 0;

	this->scheduleUpdate();
	this->setDisplayFrameWithAnimationName("StalloneNormalShoot", 0);
	this->setScale(1.5f);
	return true;
}

//��дsetGrowState
void Stallone::setGrowState(int state, bool isIgnore)
{
	this->m_GrowState = state;
	updateStatus();

	if (isIgnore)
		return;
	m_H_v1 = 0;
	startGodMode();
}

//�޵�ʱ�Ϳ�ʼ��˸����ʾ�޵�
void Stallone::godmodeing(float dt)
{
	Biology::godmodeing(dt);

	if (!isGodMode())
	{
		this->setColor(ccc3(255, 255, 255));
		return;
	}

	if (this->getColor().b == 255)
	{
		this->setColor(ccc3(255, 0, 0));
	}
	else
	{
		this->setColor(ccc3(255, 255, 255));
	}
}

/* ��Ծ */
void Stallone::jump(float vv, bool isIgnore)
{
	if (m_Life <= 0 || m_IsAutoRun)
		return;

	if (!isIgnore && m_IsFly)
		return;

	m_IsFly = true;
	m_V_v1 = vv;
	m_V_a = m_V_a > 0 ? -m_V_a : m_V_a;
	updateStatus();

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[13], false);
	}
}

void Stallone::loseLife()
{
	if (isAutoRun())//�Ѿ�Ӯ�ˣ���ײ��Ҳû��Ч��	
		return;
	//�޵�״ֱ̬�ӷ���
	if (m_IsGodMode) return;	

	if (m_GrowState > 1)
	{
		m_GrowState = 1;
		setGrowState(m_GrowState);
	}
	else if (m_GrowState == 1)
	{
		m_GrowState = 0;
		setGrowState(m_GrowState);
	}
	else
	{
		m_Life--;
	}
}

void Stallone::shoot()
{
	Bullet *bullet = NULL;
	if (m_GrowState >= 2)			
		bullet = IceBullet::create();//���ӵ�		
	else 						
		bullet = Bullet::create();//������ͨ�ӵ�����
	
	if (bullet == NULL)
		return;
	bullet->setPosition(ccp(this->getPositionX() + this->getContentSize().width / 2, this->getPositionY() + 35));
	bullet->setRunDir(m_IsLeftFace);
	getMap()->addChild(bullet);
	Bullet::m_Bullets->addObject(bullet);

	this->stopAllActions();
	CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("StalloneNormalShoot"));
	CCCallFunc *done = CCCallFunc::create(this, callfunc_selector(Stallone::shootFinish));
	CCSequence *seq = CCSequence::create(animate, done, NULL);
	this->runAction(seq);

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[12], false);
	}
}

void Stallone::shootFinish()
{
	if (m_IsFly)
	{
		if (m_IsLeftFace && !isFlipX())
			this->setFlipX(true);
		else if (!m_IsLeftFace && isFlipX())
			this->setFlipX(false);
		
		m_IsFlyRunning = true;
		this->setDisplayFrameWithAnimationName("StalloneJump", 0);
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("StalloneJump"));
		this->runAction(CCRepeatForever::create(animate));
	}
}

void Stallone::setShoot(bool b)
{
	if (m_IsShoot == b)//��ֹ�ظ������ӵ�	
		return;

	m_IsShoot = b;
}

void Stallone::dead()
{
	unscheduleUpdate();

	this->stopAllActions();
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StalloneDead"));
	CCMoveBy *by1 = CCMoveBy::create(0.3f, ccp(0, 80));
	CCMoveBy *by2 = CCMoveBy::create(3.0f, ccp(0, -winSize.width));
	CCSequence *seq = CCSequence::create(by1, by2, NULL);
	this->runAction(seq);

	this->scheduleOnce(schedule_selector(Stallone::dieFinish), 2.0f);

	if (Common::isPlayEffect)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(effectNames[10], false);
	}

	if (Common::isPlayMusic)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
}

void Stallone::dieFinish(float)
{
	m_IsDead = true;
}

void Stallone::update(float dt)
{
	//����Ϊ0�������������������
	if (m_Life <= 0 || this->getPositionY() <= 0)//�ж��Ƿ�������
	{
		m_Life = 0;//��Ϊthis->getPositionY() <= 0�Ļ���û�а�������λ0
		dead();//����
		return;
	}
	//�����յ�վ���Զ�����
	if (m_IsAutoRun)
	{
		if (m_DirRun != MOVE_RIGHT)
			m_DirRun = MOVE_RIGHT;
		if (this->getPositionX() > m_RunDistance)
			return;
	}

	//�ж��Ƿ�ִ����Ծ
	if (m_IsJump)
	{
		jump();
	}
	//�����ӵ�
	//�ж��Ƿ�ִ�з����ӵ�
	if (!m_IsReadyShoot)
	{
		m_ShootCount += dt;
		if (m_ShootCount >= 0.3f)
		{
			m_IsReadyShoot = true;
			m_ShootCount = 0;
		}
	}
	else if (m_IsShoot)
	{
		shoot();
		m_IsReadyShoot = false;
	}
	//�ƶ�
	move(dt);
}

void Stallone::calcX(float dt)
{
	//dtʱ���λ��
	float s = m_H_v1 * dt + m_H_a *dt*dt / 2;
	m_H_v1 = m_H_v1 + m_H_a * dt;//dtʱ���ٶ�
	//CCLog("%g", m_H_v1);

	this->mapMoveH(this, s);

	this->setPositionX(this->getPositionX() + s);
	if (this->getPositionX() < 0)
	{
		//΢��	
		this->setPositionX(0);
	}
}
void Stallone::moveH(float dt)
{
	//ˮƽ������ƶ��ж�
	if (m_DirRun == MOVE_LEFT)
	{
		if (m_State != MOVE_LEFT)
		{
			m_IsLeftFace = true;
			m_State = MOVE_LEFT;	
			m_H_v1 = 0;
			m_H_a = m_H_a > 0 ? -m_H_a : m_H_a;
			updateStatus();
		}

		if (m_H_v1 <= -m_H_Max_v1)
			m_H_v1 = -m_H_Max_v1;
		
		this->calcX(dt);
		if (_isCollisionLeft())
		{
			m_H_v1 = 0;//����ǽ���ٶ�����Ϊ0
		}
	}
	else if (m_DirRun == MOVE_RIGHT)
	{
		if (m_State != MOVE_RIGHT)
		{
			m_IsLeftFace = false;
			m_State = MOVE_RIGHT;
			m_H_v1 = 0;
			m_H_a = m_H_a < 0 ? -m_H_a : m_H_a;
			updateStatus();
		}

		if (m_H_v1 >= m_H_Max_v1)		
			m_H_v1 = m_H_Max_v1;		

		this->calcX(dt);
		if (_isCollisionRight())
		{
			m_H_v1 = 0;
		}	
	}
	else
	{
		if (m_State != MOVE_NONE)
		{
			m_State = MOVE_NONE;
			m_H_v1 = 0;
			updateStatus();
		}
	}
}

void Stallone::calcY(float dt)
{
	//dtʱ���λ��
	float s = m_V_v1 * dt + m_V_a *dt*dt / 2;
	m_V_v1 = m_V_v1 + m_V_a * dt;//dtʱ���ٶ�
	//CCLog("%g", m_V_v1);

	this->mapMoveV(this, s);
	this->setPositionY(this->getPositionY() + s);
}

void Stallone::moveV(float dt)
{
	//��ֱ������ƶ��ж�
	if (m_V_v1 <= 0)//����
	{
		if (m_IsFly)
			calcY(dt);//�����䣬�ڽ�����ײ��⣬��ֹ�������ߵ�ʱ�����ж�		
		if (this->_isCollisionDown())
		{
			//CCLog("mario mario,%p", this);
			if (m_IsFly)
			{
				m_IsFly = false;
				m_V_v1 = 0;
				updateStatus();
			}
		}
		else
		{
			if (!m_IsFly)
			{
				m_IsFly = true;
				m_V_v1 = 0;
				m_V_a = m_V_a > 0 ? -m_V_a : m_V_a;
				updateStatus();
			}
			if (m_V_v1 <= -m_V_Max_v1*1.5f)			
				m_V_v1 = -m_V_Max_v1*1.5f;			
		}
	}
	else//����
	{
		calcY(dt);
		if (_isCollisionUp())
		{
			m_V_v1 = 0;
			m_V_a = m_V_a > 0 ? -m_V_a : m_V_a;
		}
	}
}

void Stallone::move(float dt)
{
	//��ֱ����
	moveV(dt);

	//ˮƽ����
	moveH(dt);
}

//����״̬
void Stallone::updateStatus()
{	
	//���·��е�״̬	
	if (m_IsFly)
	{		
		if (m_IsLeftFace && !isFlipX())
			this->setFlipX(true);
		else if (!m_IsLeftFace && isFlipX())
			this->setFlipX(false);
		
		if (m_IsFlyRunning)		
			return;
		
		this->stopAllActions();
		m_IsFlyRunning = true;
		this->setDisplayFrameWithAnimationName("StalloneJump", 0);
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("StalloneJump"));
		this->runAction(CCRepeatForever::create(animate));	
		return;
	}

	this->stopAllActions();
	m_IsFlyRunning = false;
	//�������ߵ�״̬
	if (m_State == MOVE_LEFT)
	{
		this->setFlipX(true);
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("StalloneWalk"));
		this->runAction(CCRepeatForever::create(animate));
	}
	
	else if (m_State == MOVE_RIGHT)
	{
		this->setFlipX(false);
		CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("StalloneWalk"));
		this->runAction(CCRepeatForever::create(animate));
	}		
	else
	{
		if (m_IsLeftFace)
			this->setFlipX(true);
		else
			this->setFlipX(false);
		//CCLog("stop");
		//����
		this->setDisplayFrameWithAnimationName("StalloneNormalShoot", 0);
	}
}