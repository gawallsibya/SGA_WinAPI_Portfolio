#pragma once
#include "vector2D.h"

typedef struct tagPOINT_F
{
	float x = 0.f;
	float y = 0.f;
	// 없어질때 알아서 초기화
	~tagPOINT_F()
	{
		x = 0.f;
		y = 0.f;
	}
}POINT_F;

typedef struct tagSIZE_F
{
	float width = 0.f;
	float height = 0.f;
	// 없어질때 알아서 초기화
	~tagSIZE_F()
	{
		width = 0.f;
		height = 0.f;
	}
}SIZE_F;

typedef class myRect
{
public:
	inline myRect() {}
	inline ~myRect() {}

	// myRect m_halfSize anchorPoint
	inline void setPivot(float x, float y)
	{
		m_pivot.x = x;
		m_pivot.y = y;
	}
	inline const POINT_F& getPivot() const
	{
		return m_pivot;
	}

	// myRect position
	inline void setPos(float x, float y)
	{
		m_pos.x = x;
		m_pos.y = y;
	}

	inline void setPos(VECTOR2D& vPos)
	{
		m_pos = vPos;
	}

	inline void setPosX(float x)
	{
		m_pos.x = x;
	}

	inline void setPosY(float y)
	{
		m_pos.y = y;
	}

	inline const VECTOR2D& getPos() const
	{
		return m_pos;
	}

	// myRect size
	inline void setSize(float width, float height)
	{
		m_size.width = width;
		m_size.height = height;
		m_halfSize.width = width / 2;
		m_halfSize.height = height / 2;
	}
	inline const SIZE_F& getSize() const
	{
		return m_size;
	}
	inline const SIZE_F& getHalfSize() const
	{
		return m_halfSize;
	}

	// myRect point
	inline const float getMinX() const
	{
		return m_pos.x - m_pivot.x * m_size.width;
	}
	inline const float getMinY() const
	{
		return m_pos.y - m_pivot.y * m_size.height;
	}
	inline const float getMidX() const
	{
		return m_pos.x - m_pivot.x * m_size.width + getHalfSize().width;
	}
	inline const float getMidY() const
	{
		return m_pos.y - m_pivot.y * m_size.height + getHalfSize().height;
	}
	inline const float getMaxX() const
	{
		return m_pos.x - m_pivot.x * m_size.width + m_size.width;
	}
	inline	const float getMaxY() const
	{
		return m_pos.y - m_pivot.y * m_size.height + m_size.height;
	}

private:
	VECTOR2D m_pos;
	POINT_F m_pivot;
	SIZE_F m_size;
	SIZE_F m_halfSize;
	
}MYRECT;

