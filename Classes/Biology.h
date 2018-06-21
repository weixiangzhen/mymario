#ifndef __BIOLOGY_H__
#define __BIOLOGY_H__

#include "Common.h"

#define BIOLOGY_H_V			90

#define BIOLOGY_V_MAX_V		500
#define BIOLOGY_V_V			300
#define BIOLOGY_V_A			900

/* ���ж���ĸ��� */
class Biology : public CCSprite
{
public:	
	static CCArray *m_Stairs;
	
	CREATE_FUNC(Biology);
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();
	//��ȡ��ͼ����
	virtual CCTMXTiledMap* getMap(){ return (CCTMXTiledMap*)this->getParent(); }
	//�ɳ�״̬
	virtual void setGrowState(int state){ this->m_GrowState = state; }
	int getGrowState(){ return m_GrowState; }
	//����ֵ����
	virtual void loseLife();
	void setLife(int life){ m_Life = life; }
	int getLife(){ return m_Life; }
	//���û�ȡ�޵�ģʽ
	bool isGodMode(){ return m_IsGodMode; }
	void startGodMode();
	void stopGodMode();
protected:
	virtual void godmodeing(float);
public:
	//�Ƿ��ڿ���
	bool isFly(){ return m_IsFly; }
	//���û�ȡˮƽ�ٶ�
	float getHV1(){ return m_H_v1; }
	void setHV1(float v1){ m_H_v1 = v1; }
	//���û�ȡ��ֱ�ٶ�
	float getVV1(){ return m_V_v1; }	
	float setVV1(float v1){ m_V_v1 = v1; }

	virtual void jump(float, float, bool);
	virtual void jump(float vv, bool isIgnore){ jump(vv, BIOLOGY_V_A, isIgnore); }//��Ծ	
	virtual void jump(){ jump(BIOLOGY_V_V, false); }


	virtual void mapMoveH(Biology *b, float s)
	{		
		CCPoint pt = getMap()->convertToWorldSpace(b->getPosition());
		if ((this->getHV1() > 0 && winSize.width / 2 < pt.x) || (this->getHV1() <= 0 && winSize.width / 2 >= pt.x && getMap()->getPositionX() < 0))
		{
			getMap()->setPositionX(getMap()->getPositionX() - s);

			if (getMap()->getPositionX() > 0)
			{
				getMap()->setPositionX(0);
			}
			Common::bgMove(getMap(), s / 2);
		}
	}

	virtual void mapMoveV(Biology *b, float s)
	{	
		CCPoint pt = getMap()->convertToWorldSpace(b->getPosition());
	
		if ((this->getVV1() > 0 && winSize.height * 2 / 3 < pt.y &&
			getMap()->getPositionY() > -(getMap()->getContentSize().height - winSize.height - getMap()->getTileSize().height)) ||
			(this->getVV1() <= 0 && winSize.height / 3 >= pt.y && getMap()->getPositionY() < 0))			
		{
			getMap()->setPositionY(getMap()->getPositionY() - s);
			if (getMap()->getPositionY() > 0)
			{
				getMap()->setPositionY(0);
			}
		}
	}

protected:	
	virtual int _isCollision(CCPoint *p, int size);
	virtual CCRect _isCollisionStair(CCPoint *p, int size);
	virtual bool _isCollisionUp();
	virtual bool _isCollisionDown();
	virtual bool _isCollisionLeft();
	virtual bool _isCollisionRight();
	virtual void calcX(float dt);
	virtual void moveH(float dt);
	virtual void calcY(float dt);
	virtual void moveV(float dt);
	virtual void move(float dt){ moveV(dt); moveH(dt); }
	virtual void updateStatus(){}	
protected:
	//��ǰ�ɳ����
	int m_GrowState;
	//��ǰ����ֵ
	int m_Life;
	//�ж��Ƿ����޵�ģʽ
	bool m_IsGodMode;
	unsigned int m_GodModeRepeat;
	//ˮƽ������ٶȺͼ��ٶ�
	float m_H_v1;
	float m_H_Max_v1;
	float m_H_a;
	//��ֱ������ٶȺͼ��ٶ�
	float m_V_v1;
	float m_V_Max_v1;
	float m_V_a;
	//�ж��Ƿ��ڿ���
	bool m_IsFly;
	
};
#endif
