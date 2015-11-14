#include "stdafx.h"

template <class T>
class iState
{
public:
	virtual inline ~iState() {}

public:
	// ���� ����
	virtual void enter(T* pCha) = 0;	// = 0  PURE VIRTUAL.
	// ���� ������
	virtual void execute(T* pCha) = 0;
	// ���� ��Ż
	virtual void exit(T* pCha) = 0;

	//virtual void change

};