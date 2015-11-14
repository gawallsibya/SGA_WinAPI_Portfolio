#pragma once
#include "object.h"
#include "myProgressBar.h"

class stage;
class character : public object
{
public:
	enum WAY {WAY_LEFT, WAY_RIGHT };
public:

	character();
	virtual ~character();
	
	void calcGravity();
	void calcKnockBackRight();
	void calcKnockBackLeft();

	void moveFromDamagedRect(float x, float y);
	void moveFromAttackRect(float x, float y);

	void addDamagedRects(float x, float y, float width, float height, float pivotX, float pivotY);
	void addAttackRects(float x, float y, float width, float height, float pivotX, float pivotY);

	void releaseAttackRects();

	const bool isDamagedFromObjectAdress(void* damagedFromObjectAdress);
	void addDamagedFromObjectAdress(void* damagedFromObjectAdress);
	void releaseDamagedFromObjectAdress(void* damagedFromObjectAdress);

	void pixelCollisionTopAndBottom();
	void pixelCollisionLeftAndRight();

	virtual void setDie() = 0;
	virtual void setDamaged(float damage) = 0;
	
	inline 	void moveTo(float x, float y) 
	{ 
		this->setPos(this->getPos().x + x, this->getPos().y);
		pixelCollisionLeftAndRight();
		
		this->setPos(this->getPos().x, this->getPos().y + y);
		pixelCollisionTopAndBottom();
		
	}
	inline void moveTo(VECTOR2D vecPos) { this->setPos(this->getPos() + vecPos); }

	inline void moveFrom(float x, float y) { this->setPos(x, y); }
	inline void moveFrom(VECTOR2D vecPos) { this->setPos(vecPos); }

private:
	virtual void boundingRectUpdate() = 0;
	
public:
	inline image* getImage() const { return _img; }
	inline void setImage(image* pImage) { _img = pImage; }

	inline animation* getAnimation() const { return _ani; }
	inline void setAnimation(animation* pAnimation) { _ani = pAnimation; }

	inline const float getVelocityY() const { return _velocityY; }
	inline void setVelocityY(float velocityY){ _velocityY = velocityY; }

	inline const float getVelocityX() const { return _velocityX; }
	inline void setVelocityX(float velocityX){ _velocityX = velocityX; }

	inline const float getSpeed() const { return _speed; }
	inline void setSpeed(float speed) { _speed = speed; }

	inline float* getHPAdress() { return &_hp; }
	inline const float& getMaxHP() const { return _maxHp; }
	inline const float getHP() const { return _hp; }
	inline void setHP(float hp) { _hp = hp; }

	inline void addHP(float hp) { _hp += hp; if (_hp > _maxHp) _hp = _maxHp; }
	inline void subHP(float hp) { _hp -= hp; if (_hp < 0.f) _hp = 0.f; }

	inline const float getEnegy() const { return _enegy; }
	inline void setEnegy(float enegy) { _enegy = enegy; }

	inline void releaseDamagedRects() { _damagedRt.clear(); }
	inline vector<MYRECT>* getDamagedRects() { return &_damagedRt; }
	inline vector<MYRECT>* getAttackRects() { return &_attackRt; }

	inline WAY getWay() { return _way; }
	inline void setWay(WAY way) { _way = way; }

	inline void setTargetMemoryAddressLink(character* cha) { _target = cha; }
	inline character* getTargetMemoryAddressLink() { return _target; }

	inline void setStageMemoryAddressLink(stage* myStage) { _curStage = myStage; }
	inline stage* getStageMemoryAddressLink() { return _curStage; }

	inline MYRECT* getBoundingRect() { return dynamic_cast<MYRECT*>(this); }
	inline void setBoundingRect(float width, float height) { this->setSize(width, height); }

protected:
	vector<MYRECT> _damagedRt;
	vector<MYRECT> _attackRt;

	MYRECT _boundingRt;

	WAY _way;

	float _hp;
	float _maxHp;

	float _enegy;
	// 점프 높이
	float _velocityY;
	// 대시 거리
	float _velocityX;
	// 이동 속도
	float _speed;

	map<void*, void*> _damagedFromObjectAdress;

	character* _target;

public:
	stage* _curStage;
};
