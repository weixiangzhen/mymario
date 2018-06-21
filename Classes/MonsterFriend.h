#ifndef __MONSTERFRIEND_H__
#define __MONSTERFRIEND_H__

#include "Monster.h"

class MonsterFriend : public Monster
{
public:
	static CCArray *m_MonsterFriends;

	static MonsterFriend* create(Biology*, CCSprite*);
	bool init(Biology*, CCSprite*);

	virtual CCTMXTiledMap* getMap()	{ return m_Sprite ? (CCTMXTiledMap*)(m_Sprite->getParent()->getParent()) : (CCTMXTiledMap*)this->getParent(); }

	bool isMake(){ return m_IsMake; }
	virtual void setMake(bool b){ this->m_IsMake = b; }
	
	void setSprite(CCSprite *s){ this->m_Sprite = s; }
	CCSprite* getSprite(){ return this->m_Sprite; }
	//�жϵײ��Ƿ���
	bool isCollisionBottom(Biology *obj);	
	
	virtual bool isCollision(Biology *obj);

	//���·���һ��Ҫ��д�����
	virtual void autoDead(Biology*, int num){}
	virtual void removeSelf();
	virtual void logic(Biology *obj){}
	virtual void logic(float dt, Biology *obj);
protected:
	CCSprite	*m_Sprite;
	bool		m_IsMake;//�ж��Ƿ�Ҫ����ʳ��Ģ��
	bool		m_IsRun;
};

/* ���н�ҵķ��� */
class Brick : public MonsterFriend
{
public:
	static Brick* create(Biology*, CCSprite*, bool);
	bool init(Biology*, CCSprite*, bool);
	
	virtual void autoDead(Biology*, int);//��������
	virtual void logic(Biology*);
	virtual void updateStatus();

	void tiledChanged();
	void removeNode(CCNode*, void*);

	//��дremoveSelf�ķ���
	//virtual void removeSelf();
protected:
	bool m_IsNoKill;
};

/* ��ʯש�� */
class Rock : public MonsterFriend
{
public:
	static Rock* create(Biology*, CCSprite*);
	bool init(Biology*, CCSprite*);

	virtual void setMake(bool b)
	{ 
		this->m_IsMake = b; 
		if (m_IsMake)
		{
			m_GrowState = 5;
		}
	}

	virtual void autoDead(Biology*, int);
	virtual void logic(Biology*);
	
	void tiledChanged1();
	void tiledChanged2();
	void tiledChanged3();
	void removeNode(CCNode *node, void *data);
private:

};

/* ����� */
class Prop : public MonsterFriend
{
public:
	static Prop* create(Biology*, CCSprite*);
	bool init(Biology*, CCSprite*);

	virtual void updateStatus();
	virtual void autoDead(Biology*, int);
	virtual void logic(Biology *obj);
};

/* ʳ�� */
class FoodMushroom : public MonsterFriend
{
public:
	static FoodMushroom* create(Biology*);
	bool init(Biology*);

	virtual void autoDead(Biology*, int);
	virtual void logic(Biology*);	
protected:
	void startMove();

};

/* ˮ���� ������ʳ�˻� */
class Piranha : public MonsterFriend
{
public:
	static Piranha* create(Biology*);
	bool init(Biology*);

	virtual CCRect boundingBox()
	{
		CCRect rect = CCSprite::boundingBox();
		rect.origin.x += 4;
		rect.size.width -= 8;
		rect.size.height -= 24;
		return rect;
	}

	virtual void updateStatus();
	virtual void logic(Biology *obj);

	void setVS(float maxs, float mins){ this->m_Max_V_S = maxs; this->m_Min_V_S = mins; }
protected:
	virtual void moveH(float dt);
	virtual void moveV(float dt);

private:
	float m_Max_V_S;
	float m_Min_V_S;
	float m_Wait;
};

/* ʳ�˻� */
class SFlower : public MonsterFriend
{
public:
	static SFlower* create(Biology*);
	bool init(Biology*);

	virtual void updateStatus();
	virtual void logic(Biology *obj);
};

/* �������ƶ� */
class AnBiao : public MonsterFriend
{
public:
	static AnBiao* create(Biology*);
	bool init(Biology*);

	void setRange(float mins, float maxs){ m_Max_V_s = maxs; m_Min_V_s = mins; }

	virtual void updateStatus();
	virtual void logic(Biology *obj);

protected:
	virtual void moveH(float dt){}
	virtual void moveV(float dt);

private:
	float m_Max_V_s;
	float m_Min_V_s;
};

/* Բ�� */
class Disk : public MonsterFriend
{
public:
	static Disk* create(Biology*, CCPoint, float, bool = false);
	bool init(Biology*, CCPoint, float, bool);

	virtual void updateStatus();
	virtual void logic(Biology *obj);

protected:
	virtual void moveH(float dt);
	virtual void moveV(float dt){}

private:
	bool m_IsNoKill;
	//unsigned int m_MoveTimes;
	float m_Radius;
	CCPoint m_Center;

	float m_Radian;
};

/* ������־ */
class EndBlack : public MonsterFriend
{
public:
	static EndBlack* create(Biology*);
	bool init(Biology*);

	virtual void updateStatus();
	virtual void autoDead(Biology *obj, int);
	virtual void logic(Biology*);
private:
	CCPoint m_StartPoint;
};

/* ���Ģ�����е�ʳ�� */
class DarkFoodMushroom : public MonsterFriend
{
public:
	static DarkFoodMushroom* create(Biology*);
	bool init(Biology*);

	virtual void autoDead(Biology*, int);
	virtual void logic(Biology*);
protected:
	virtual void moveH(float dt);
	virtual void moveV(float dt);
};

#endif // __MONSTERFRIEND_H__
