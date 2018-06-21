#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Biology.h"

class MAwardData : public CCObject
{
public:
	CREATE_FUNC(MAwardData);

	bool init()
	{ 
		m_pt = CCPointZero;
		m_score = 0;
		m_IsMakeCoin = false;
		m_IsMonster = false;
		return true; 
	}

	void setPosition(CCPoint p){ m_pt = p; }
	CCPoint getPosition(){ return m_pt; }

	void setScore(int score){ m_score = score; }
	int getScore(){ return m_score; }

	bool isMonster(){ return m_IsMonster; }
	void setMonster(bool isMonster){ this->m_IsMonster = isMonster; }

	void setMakeCoin(bool b){ m_IsMakeCoin = b; }
	bool isMakeCoin(){ return m_IsMakeCoin; }

private:
	int m_score;
	CCPoint m_pt;
	bool m_IsMakeCoin;
	bool m_IsMonster;
};

//���й���ĸ��࣬�����ѷ��͵з���
class Monster : public Biology
{
public:	
	static CCArray *m_MAwardDatas;

	static void preload();
	//��������
	CREATE_FUNC(Monster);
	static Monster* create(Biology*);
	//��ʼ��
	virtual bool init();
	virtual bool init(Biology*);

	//��дboundingBox��Ϊ�����˹���պ���һ�����Ӵ�С�����ƶ�ʱ�������µ��ռ�ֻ��һ�����ӵĵط�
	virtual CCRect boundingBox()
	{
		CCRect rect = CCSprite::boundingBox();
		rect.origin.x += 1;
		rect.size.width -= 2;
		return rect;
	}
	//��ӵ�����������ȥ
	void addAward(CCPoint p, bool isMakeCoin, bool isMonster, int score);

	bool isMove(){ return m_IsMove; }

	//ά����һ������½���
	void setBiology(Biology *b){ this->m_Biology = b; }
	Biology* getBiology(){ return m_Biology; }	

	//�жϹ����Ƿ�ש������
	bool isCollisionBrick(int * = NULL);

	virtual bool isCollision(Biology *obj);
	bool isCollision(){ return isCollision(m_Biology); }
	//
	virtual void autoDead(Biology*, int num){}//����ײ��Ҫ��������
	virtual void autoDead(Biology *obj){ autoDead(obj, 0); }//����ײ��Ҫ��������

	virtual void removeSelf(){}
	virtual void logic(Biology *obj){}
	virtual void logic(float dt, Biology *obj){}
	//void logic(){ logic(m_Biology); }	
	void logic(float dt){ logic(dt, m_Biology); }	
	
protected:
	Biology *m_Biology;	
	
	bool m_IsMove;//�ܷ��ƶ�
};

#endif//__MONSTER_H__


