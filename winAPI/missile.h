#pragma once
#include "object.h"

class stage;
class missile : public object
{
public:
	typedef list<missile*>::iterator liMissile;
public:
	missile();
	~missile();

	virtual void init(character* master, float x, float y, VECTOR2D vMovePos, bool reverse) = 0;
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc) = 0;

	void checkRangeUpdate();
	void moveFromAttackRect(float x, float y);
	void addAttackRects(float x, float y, float width, float height, float pivotX, float pivotY);

	void pixelCollisionTopAndBottom();
	void pixelCollisionLeftAndRight();

public:
	inline vector<MYRECT>* getAttackRects() { return &_attackRt; }

	inline const liMissile getMyIterator() const { return _myIter; }
	inline void setMyIterator(liMissile iter) { _myIter = iter; }
	inline bool isLife() { return _bLife; }
	inline bool setLife(bool life) { _bLife = life; }

	inline 	void moveTo(float x, float y)
	{
		this->setPos(this->getPos().x + x, this->getPos().y);
		this->setPos(this->getPos().x, this->getPos().y + y);
	}
	inline void moveTo(VECTOR2D vecPos) { this->setPos(this->getPos() + vecPos); }

	inline void moveFrom(float x, float y) { this->setPos(x, y); }
	inline void moveFrom(VECTOR2D vecPos) { this->setPos(vecPos); }

	inline void setStageMemoryAddressLink(stage* myStage) { _curStage = myStage; }
	inline stage* getStageMemoryAddressLink() { return _curStage; }

	inline MYRECT* getBoundingRect() { return dynamic_cast<MYRECT*>(this); }
	inline void setBoundingRect(float width, float height) { this->setSize(width, height); }

private:
	virtual void animationUpdate();
	virtual void moveUpdate();

protected:
	VECTOR2D _vStartPos;
	VECTOR2D _vMovePos;
	float _speed;
	float _range;
	bool _bReverse;

	vector<MYRECT> _attackRt;
	character* _master;

	float _deltaTime;
	bool _bOnEffect;
	float _damage;

	effectManager* _effectMgr;
	
	liMissile _myIter;

	bool _bLife;

	stage* _curStage;
};

