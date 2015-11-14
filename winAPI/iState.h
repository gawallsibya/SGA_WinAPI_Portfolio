#include "stdafx.h"

template <class T>
class iState
{
public:
	virtual inline ~iState() {}

public:
	// 상태 진입
	virtual void enter(T* pCha) = 0;	// = 0  PURE VIRTUAL.
	// 상태 진행중
	virtual void execute(T* pCha) = 0;
	// 상태 이탈
	virtual void exit(T* pCha) = 0;

	//virtual void change

};