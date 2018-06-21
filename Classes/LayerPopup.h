#ifndef __LayerPOPUP_H__
#define __LayerPOPUP_H__

#include "Common.h"

class LayerPopup : public CCLayer
{
public:
	CREATE_FUNC(LayerPopup);
	virtual bool init();

private:
	//ע�ᴥ���¼���ʵ��ccTouchBegan()����
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch * touch, CCEvent * pevent);

protected:
	int m_TouchStretch;

	CCDictionary *m_Dict;
};

/* ������Ϸ�Ի��� */
class LayerBack :public LayerPopup
{
public:
	CREATE_FUNC(LayerBack);
	virtual bool init();

	//�ڵ����ĶԻ����ϼ�������ť�����µĺ����Ƕ�Ӧ�İ�ť�Ĵ����¼�
	virtual void backCallBack(CCObject*);
protected:
	CCSprite *bgSprite;
};

/* ���öԻ��� */
class LayerSettings : public LayerBack
{
public:
	CREATE_FUNC(LayerSettings);
	virtual bool init();

protected:
	void backCallBack(CCObject*);
	void backMenuCallBack(CCObject*);
	void musicCallBack(CCObject*);
	void soundCallBack(CCObject*);
};

/* �̵�Ի��� */
class LayerShop : public LayerBack
{
public:
	CREATE_FUNC(LayerShop);
	virtual bool init();

protected:
	void addMushroom(CCObject*);
	void addLife(CCObject*);

	virtual void update(float);
	virtual void backCallBack(CCObject*);
private:
	int m_GrowCount;
	int m_Life;
	int m_Coin;

	int m_TempCoin;

	CCLabelBMFont *m_LifeLabel;
	CCLabelBMFont *m_GrowLabel;
	CCLabelBMFont *m_CoinLabel;
};


/* ��Ϸ�������˳���Ϸ�Ի��� */
class LayerOver : public LayerPopup
{
public:
	//CREATE_FUNC(LayerOver);
	static LayerOver* create(bool isEsc);
	virtual bool init(bool);

	void button1CallBack(CCObject*);
	void button2CallBack(CCObject*);

private:
	bool m_IsEsc;
};

#endif

