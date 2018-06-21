#include "Biology.h"

CCArray *Biology::m_Stairs = NULL;

bool Biology::init()
{
	if (!CCSprite::init()){ return false; }	

	//��ʼ�ɳ�״̬Ϊ0
	m_GrowState = 0;
	//Ĭ������ֵΪ1
	m_Life = 1;
	//Ĭ�ϲ����޵�
	m_IsGodMode = false;
	m_GodModeRepeat = 0;
	//�ٶȷ���
	m_H_a = 0;//ˮƽ����û�м��ٶ�
	m_H_Max_v1 = 0;
	m_H_v1 = m_H_Max_v1;	

	m_V_a = -BIOLOGY_V_A;
	m_V_Max_v1 = BIOLOGY_V_MAX_V;
	m_V_v1 = 0;	
	//Ĭ��û����Ծ����������
	m_IsFly = false;
	
	return true;
}

void Biology::onEnter()
{
	CCSprite::onEnter();	
}

void Biology::onExit()
{
	CCSprite::onExit();
}
//�������������ȼ�ȥ�ɳ�״̬���ټ�ȥ����
void Biology::loseLife()
{
	if (m_GrowState)
	{
		m_GrowState--;//�ɳ�״̬-1		
	}
	else if (m_Life)
	{
		m_Life--;//������1����Ϊ0�ˣ���������
	}
}
//�����޵�ģʽ
void Biology::startGodMode()
{
	stopGodMode();

	m_IsGodMode = true;
	this->schedule(schedule_selector(Biology::godmodeing), 0.1f);//ÿ0.1��ִ��һ�ι�30���޵�ʱ��Ϊ3����
}
//ֹͣ�޵�ģʽ
void Biology::godmodeing(float)
{
	m_GodModeRepeat++;
	if (m_GodModeRepeat == 20)
	{
		stopGodMode();
	}	
}

void Biology::stopGodMode()
{ 
	if (m_IsGodMode)//����Ѿ��������޵�ģʽ����ֹͣ��ʱ
	{
		m_GodModeRepeat = 0;
		m_IsGodMode = false;
		this->unschedule(schedule_selector(Biology::godmodeing));
	}	
}

//��Ծ������1����Ծʱ���ٶȣ�����2�����ٶȣ�����3���Ƿ�����ڿ���
void Biology::jump(float vv, float va, bool isIgnore)
{
	if (m_IsFly && !isIgnore)
	{
		return;
	}

	m_IsFly = true;
	m_V_a = -va;	
	m_V_v1 = vv;
	updateStatus();
}

/***********************************5����ײ���ķ��������á��������ײ�����ߡ��ұ�****************************************/
int Biology::_isCollision(CCPoint *p , int size)
{	
	CCTMXLayer *barrierLayer = getMap()->layerNamed("barrier");
	CCTMXLayer *objectsLayer = getMap()->layerNamed("monster_image");
	for (int i = 0; i < size; i++)
	{
		CCPoint pt = Common::pointToTile(getMap(), p[i]);
		if (barrierLayer->tileGIDAt(pt) ||
			(objectsLayer->tileGIDAt(pt) == 11 && objectsLayer->tileAt(pt)->isVisible()) ||
			objectsLayer->tileGIDAt(pt) == 17 ||
			objectsLayer->tileGIDAt(pt) == 25 ||
			objectsLayer->tileGIDAt(pt) == 26 ||
			objectsLayer->tileGIDAt(pt) == 27)
		{			
			return i;
		}
	}
	return size;
}

CCRect Biology::_isCollisionStair(CCPoint *p, int size)
{
	CCObject *obj = NULL;
	CCARRAY_FOREACH(m_Stairs, obj)
	{
		Biology *b = (Biology*)obj;
		for (int i = 0; i < size; i++)
		{
			if (b->boundingBox().containsPoint(p[i]))
			{
				return b->boundingBox();
			}
		}
	}
	return CCRectZero;
}

//������ײ���
bool Biology::_isCollisionUp()
{
	CCRect rect = boundingBox();
	//���ڵ�ͼ��ȵ���ߵ�,������ײ���
	//CCLog("aaaaaaaaaaaaaaaaaaaaaaaaaaaa,%g,%g", this->getPositionY() + rect.size.height, getMap()->getContentSize().height - getMap()->getTileSize().height);
	if (rect.origin.y + rect.size.height > getMap()->getContentSize().height - getMap()->getTileSize().height)
		return false;

	CCPoint p[3] = { ccp(rect.getMidX(), rect.getMaxY()), ccp(rect.getMinX(), rect.getMaxY()), ccp(rect.getMaxX(), rect.getMaxY()) };

	CCTMXLayer *barrierLayer = getMap()->layerNamed("barrier");
	int v = 0;	
	if ((v = _isCollision(p, 3)) != 3)
	{
		CCPoint pt = Common::pointToTile(getMap(), p[v]);
		//΢����-1����Ϊ���ܸ���ײ��պ�ճ��һ�𣬱���պ����ϰ�����ײ�������ƶ��������
		float dy = rect.origin.y - (Common::tileToPoint(getMap(), pt).y - rect.size.height - 1);
		this->setPositionY(this->getPositionY() - dy);
		//CCLog("Mario %g,%g", Common::tileToPoint(getMap(), pt).x, rect.origin.x);
		return true;		
	}
	CCRect stairRect = _isCollisionStair(p, 3);
	if (stairRect.size.width != 0 && stairRect.size.height != 0)
	{
		//һ��Ҫ�����ֵ������Ϊ��Щ�����ê�㲻��0��0
		float dy = rect.origin.y - stairRect.origin.y - 1;
		//this->setPositionY(stairRect.origin.y - rect.size.height - 1);
		this->setPositionY(this->getPositionY() + dy);
		return true;
	}
	return false;
}
//_isCollisionDown��_isCollisionUp�е㲻һ����Ϊʲô����Ҫԭ�򣺻��ǵ�ͼ��ש���λ�ö���int��������µ�λ�ö���float���漰����ǿת�����⣬����Ϊ�˹����Щ����
//��Ҫ�����޸ĵ����⣺ͳһê���ڣ�0.5��0��������µ�ê���ڣ�0��0�������������ê�������ģ��޸�ê��ô����ڣ�������µ�ͼƬ�кܴ��͸���ռ䣬����λ�õ�ʱ��Ҫ�ó�һ����ֵ�������ã����鷳��
//�ײ���ײ���
bool Biology::_isCollisionDown()
{
	CCRect rect = boundingBox();	
	//���ڵ�ͼ��ȵ���ߵ�,������ײ���
	if (rect.origin.y + rect.size.height > getMap()->getContentSize().height - getMap()->getTileSize().height)
		return false;

	//����-1��ʾ��ǰ����������Ϊ����-1����»�һֱ�����Ͳ���֮�䣬
	//��֤��ÿ�ζ���ǰ�������ײ���ô�������²���һֱ����
	CCPoint p[3] = { ccp(rect.getMidX(), rect.getMinY() - 1), ccp(rect.getMinX(), rect.getMinY() - 1), ccp(rect.getMaxX(), rect.getMinY() - 1) };
	
	int v = _isCollision(p, 3);
	if (v != 3)
	{		
		CCPoint pt = Common::pointToTile(getMap(), p[v]);
		//΢��,dy��������ΪͼƬ�пհ����򣬵ó�һ����ֵ
		float dy = Common::tileToPoint(getMap(), pt + ccp(0, -1)).y - rect.origin.y;			
		this->setPositionY(this->getPositionY() + dy);
		return true;					
	}
	CCRect stairRect = _isCollisionStair(p, 3);
	if (stairRect.size.width != 0 && stairRect.size.height != 0)
	{
		//CCLog("down %g", stairRect.origin.y + stairRect.size.height);
		float dy = stairRect.origin.y + stairRect.size.height + 1 - rect.origin.y;
		this->setPositionY(this->getPositionY() + dy);
		return true;
	}
	return false;
}

//�����ײ���
bool Biology::_isCollisionLeft()
{
	CCRect rect = boundingBox();
	//���ڵ�ͼ��ȵ���ߵ�,������ײ���
	if (rect.origin.y + rect.size.height > getMap()->getContentSize().height - getMap()->getTileSize().height)
		return false;

	CCPoint p[3] = { ccp(rect.getMinX(), rect.getMidY()), ccp(rect.getMinX(), rect.getMinY()), ccp(rect.getMinX(), rect.getMaxY()) };

	int v = _isCollision(p, 3);
	if (v != 3)
	{
		CCPoint pt = Common::pointToTile(getMap(), p[v]);
		//΢��
		float dx = Common::tileToPoint(getMap(), pt + ccp(1, 0)).x - rect.origin.x;
		this->setPositionX(this->getPositionX() + dx);
		return true;		
	}
	CCRect stairRect = _isCollisionStair(p, 3);
	if (stairRect.size.width != 0 && stairRect.size.height != 0)
	{		
		//CCLog("left %g", stairRect.size.width);
		float dx = stairRect.origin.x + stairRect.size.width - rect.origin.x;
		this->setPositionX(this->getPositionX() + dx);
		return true;
	}
	return false;
}

//�ұ���ײ���
bool Biology::_isCollisionRight()
{
	CCRect rect = boundingBox();
	//���ڵ�ͼ��ȵ���ߵ�,������ײ���
	if (rect.origin.y + rect.size.height > getMap()->getContentSize().height - getMap()->getTileSize().height)
		return false;

	CCPoint p[3] = { ccp(rect.getMaxX(), rect.getMidY()), ccp(rect.getMaxX(), rect.getMinY()), ccp(rect.getMaxX(), rect.getMaxY()) };

	int v = _isCollision(p, 3);
	if (v != 3)
	{
		CCPoint pt = Common::pointToTile(getMap(), p[v]);
		//΢��,-1��Ϊ�˲�����������ש	
		float dx = rect.origin.x - (Common::tileToPoint(getMap(), pt).x - rect.size.width - 1);			
		this->setPositionX(this->getPositionX() - dx);			
		return true;		
	}
	CCRect stairRect = _isCollisionStair(p, 3);
	if (stairRect.size.width != 0 && stairRect.size.height != 0)
	{
		//CCLog("right %g,%g", stairRect.origin.x, rect.size.width);
		//float dx = rect.origin.x + rect.size.width - stairRect.origin.x -1;
		float dx = rect.origin.x - (stairRect.origin.x - rect.size.width - 1);
		this->setPositionX(this->getPositionX() - dx);
		return true;
	}
	return false;
}
/******************************************End*********************************************/
/* ˮƽmove�ķ����ƶ��������ƶ�����ֱ�ƶ��ķ������ȼ����ƶ�*/
/***********************************�ƶ��������������ͼ����ײ**********************************/
void Biology::calcX(float dt)
{
	this->setPositionX(this->getPositionX() + m_H_v1 * dt);
}
//ˮƽ������ƶ��ж�
void Biology::moveH(float dt)
{
	if (m_H_v1 < 0)
	{
		calcX(dt);
		if (_isCollisionLeft())
		{			
			m_H_v1 = m_H_Max_v1;//����ǽ���ٶȷ�����
			updateStatus();//����һ��״̬
		}
	}
	else if (m_H_v1 > 0)
	{
		calcX(dt);
		if (_isCollisionRight())
		{		
			m_H_v1 = -m_H_Max_v1;//����ǽ���ٶȷ�����
			updateStatus();
		}
	}
	else//���ᶯ
	{

	}
}
void Biology::calcY(float dt)
{
	float s = m_V_v1 * dt + m_V_v1 * dt * dt / 2;
	m_V_v1 = m_V_v1 + m_V_a * dt;
	this->setPositionY(this->getPositionY() + s);//�����������䣬�ڽ�����ײ���΢������ֹ�������ߵ�ʱ�����ж�
	//CCLog("%g", m_V_v1);
	if (m_V_v1 <= -m_V_Max_v1)//���ƴ�ֱ������ٶȣ��������		
		m_V_v1 = -m_V_Max_v1;
}
//��ֱ������ƶ��ж�
void Biology::moveV(float dt)
{	
	if (m_V_v1 <= 0)//����
	{
		if (m_IsFly)
			calcY(dt);//�����䣬����ײ��⣬������΢������Ȼˮƽ�ƶ����������		
		if (_isCollisionDown())
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
		if (_isCollisionUp())
		{
			m_V_v1 = 0;
			m_V_a = -BIOLOGY_V_A;
		}
	}	
}
