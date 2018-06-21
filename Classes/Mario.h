#ifndef __MARIO_H__
#define __MARIO_H__

#include "Biology.h"

//#define MARIO_H_V1 50
#define MARIO_H_A					550
#define MARIO_H_MAX_V				330

//Ӱ������/������ٶ�
#define MARIO_V_A					1300
//Ӱ����Ծ�ĸ߶�
#define MARIO_V_MAX_V				600

#define STALLONE_H_A				550
#define STALLONE_H_MAX_V			330
#define STALLONE_V_A				1300
#define STALLONE_V_MAX_V			600

#define MARIO_SMALL_RECT_DAFAULT			CCRectMake(5*(512 / 9.0f), 0, (512 / 9.0f), 57)
#define MARIO_SMALL_RECT_WALKING1			CCRectMake((512 / 9.0f), 0, (512 / 9.0f), 57)
#define MARIO_SMALL_RECT_BRAKING			CCRectMake(3*(512 / 9.0f), 0, (512 / 9.0f), 57)
#define MARIO_SMALL_RECT_JUMP				CCRectMake(2*(512 / 9.0f), 0, (512 / 9.0f), 57)
#define MARIO_SMALL_RECT_STOPWALK1			CCRectMake(0, 0, (512 / 9.0f), 57)

#define MARIO_BIG1_RECT_DAFAULT				CCRectMake(5*(512 / 9.0f), 57, (512 / 9.0f), 57)
#define MARIO_BIG1_RECT_WALKING1			CCRectMake((512 / 9.0f), 57, (512 / 9.0f), 57)
#define MARIO_BIG1_RECT_BRAKING				CCRectMake(3*(512 / 9.0f), 57, (512 / 9.0f), 57)
#define MARIO_BIG1_RECT_JUMP				CCRectMake(2*(512 / 9.0f), 57, (512 / 9.0f), 57)
#define MARIO_BIG1_RECT_STOPWALK1			CCRectMake(0, 57, (512 / 9.0f), 57)

#define MARIO_BIG2_RECT_DAFAULT				CCRectMake(5*(512 / 9.0f), 114, (512 / 9.0f), 57)
#define MARIO_BIG2_RECT_WALKING1			CCRectMake((512 / 9.0f), 114, (512 / 9.0f), 57)
#define MARIO_BIG2_RECT_BRAKING				CCRectMake(3*(512 / 9.0f), 114, (512 / 9.0f), 57)
#define MARIO_BIG2_RECT_JUMP				CCRectMake(2*(512 / 9.0f), 114, (512 / 9.0f), 57)
#define MARIO_BIG2_RECT_STOPWALK1			CCRectMake(0, 114, (512 / 9.0f), 57)

#define MARIO_RECT_DEAD						CCRectMake(6*(512 / 9.0f), 0, (512 / 9.0f), 57)
#define MARIO_RECT_SHOOT					CCRectMake(6*(512 / 9.0f), 114, (512 / 9.0f), 57)

/* ����ºͻ궷�����ǵĸ���*/
class Figure : public Biology
{
public:
	//�ƶ�����
	enum MOVE_DIR{ MOVE_LEFT = -1, MOVE_NONE, MOVE_RIGHT };

	CREATE_FUNC(Figure);
	virtual bool init()
	{ 
		if (!Biology::init()){ return false; }	

		this->setZOrder(Common::Z_Figure);
		this->setAnchorPoint(ccp(0, 0));

		m_IsLeftFace = false;//Ĭ�ϵ����ǳ��ҵ�
		m_DirRun = MOVE_NONE;
		//�Ƿ���ȫ����
		m_IsDead = false;
		//�Զ�����
		m_IsAutoRun = false;
		//һֱ��
		m_IsJump = false;
		//һֱ����
		m_IsShoot = false;
		//�Զ����еľ���
		m_RunDistance = 0;
		return true; 
	}

	virtual void setGrowState(int, bool){}

	bool isDead(){ return m_IsDead; }

	void setAutoRun(bool b){ m_IsAutoRun = b; }
	bool isAutoRun(){ return m_IsAutoRun; }

	void setRunDir(MOVE_DIR dir){ if (m_Life <= 0)return; if (m_IsAutoRun)return; m_DirRun = dir; }
	MOVE_DIR getRunDir(){ return m_DirRun; }

	void setJump(bool b){ m_IsJump = b; }
	bool isJump(){ return m_IsJump; }

	virtual void shoot(){}
	virtual void setShoot(bool){}
	bool isShoot(){ return m_IsShoot; }

	virtual void dead(){}

	void setRunDistance(float d){ this->m_RunDistance = d; }
protected:
	//���з���
	MOVE_DIR m_DirRun;
	//������
	bool m_IsLeftFace;

	bool m_IsShoot;

	//��Ծ���
	bool m_IsJump;
	//�Ƿ��Զ�����
	bool m_IsAutoRun;
	//��͸��
	bool m_IsDead;
	//�Զ����к���Ҫ���еľ���
	float m_RunDistance;
};

/* ����� */
class Mario : public Figure
{
public:
	static void preload();
	//������ƶ��ķ���
	enum MARIO_STATE{ M_LEFT = -2, M_LEFTBRAKING, M_NONE, M_RIGHT, M_RIGHTBRAKING };

	CREATE_FUNC(Mario);
	virtual bool init();

	virtual CCRect boundingBox();
	virtual void setGrowState(int state){ setGrowState(state, false); }
	virtual void setGrowState(int, bool);
protected:
	void godmodeing(float);
public:
	//��Ծ	
	virtual void jump(float, bool);
	virtual void jump(){ jump(MARIO_V_MAX_V, false); }

	virtual void loseLife();


	//bool isDead(){ return m_IsDead; }

	//void setAutoRun(bool b){ m_IsAutoRun = b; }
	//bool isAutoRun(){ return m_IsAutoRun; }

	//virtual void setRunDir(MOVE_DIR dir){ if (m_Life <= 0)return; if (m_IsAutoRun)return; m_DirRun = dir; }
	//MOVE_DIR getRunDir(){ return m_DirRun; }	

	virtual void shoot();
	virtual void setShoot(bool);	
	//bool isShoot(){ return m_IsShoot; }	

	virtual void dead();
	void dieFinish(float);

	//void setRunDistance(float d){ this->m_RunDistance = d; }
protected:
	virtual void update(float);

	virtual void calcX(float);//���㲢����ˮƽ����ľ���
	virtual void moveH(float);//ˮƽ������ƶ�
	virtual void calcY(float);//���㲢���ô�ֱ����ľ���
	virtual void moveV(float);//��ֱ������ƶ�		
	virtual void move(float);//�ƶ�����
	//���ߺ�ֹͣ
	void walking();
	void stopWalk();
	//����״̬
	virtual void updateStatus();

	void restoreNomal(float){ updateStatus(); }	
private:	
	//������������ĸ���������
	MARIO_STATE m_State;

	//�����ӵ����
	//bool m_IsShoot;
	bool m_IsReadyShoot;
	float m_ShootCount;
}; 

/* ʷ̩�� */
class Stallone : public Figure
{
public:
	static void preload();

	CREATE_FUNC(Stallone);
	virtual bool init();

	virtual CCRect boundingBox()
	{
		CCRect rect = CCSprite::boundingBox();
		//CCLog("%f,%f", rect.size.width, rect.size.height);
		if (m_IsFly)
			return CCRectMake(rect.origin.x, rect.origin.y, 30, 30);
		return CCRectMake(rect.origin.x, rect.origin.y, 30, 48);
	}

	virtual void setGrowState(int state){ setGrowState(state, false); }
	virtual void setGrowState(int, bool);
protected:
	void godmodeing(float);

public:
	//��Ծ	
	virtual void jump(float, bool);
	virtual void jump(){ jump(m_V_Max_v1, false); }

	virtual void loseLife();

	virtual void shoot();
	void shootFinish();
	virtual void setShoot(bool);

	virtual void dead();
	void dieFinish(float);	
protected:
	virtual void update(float);

	virtual void calcX(float);//���㲢����ˮƽ����ľ���
	virtual void moveH(float);//ˮƽ������ƶ�
	virtual void calcY(float);//���㲢���ô�ֱ����ľ���
	virtual void moveV(float);//��ֱ������ƶ�	
	virtual void move(float dt);//�ƶ�����
	//����״̬
	virtual void updateStatus();

private:
	MOVE_DIR m_State;

	bool m_IsFlyRunning;
	bool m_IsReadyShoot;
	float m_ShootCount;
};
#endif