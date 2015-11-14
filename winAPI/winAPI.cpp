//======================================================
// 2014.10.22 ## ������� ���ش� ##
//======================================================
#include "stdafx.h"
#include "gameStudy.h"

//======================================================
// 2014.10.22 ## �������� ���ش� ##
//======================================================
HINSTANCE _hInstance; 
HWND _hWnd;
POINT _ptMouse = {0, 0};

//���ӽ��͵� Ŭ����
gameStudy _gs;

//======================================================
// 2014.10.22 ## �Լ��� ������Ÿ�� ���ش� ##
//======================================================

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					 LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//MSG : �ü������ �����ϴ� �޽��� ������ �����ϱ� ���� ����ü
	MSG message;		

	//WNDCLASS : �������� ������ �����ϱ� ���� ����ü
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;		//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;		//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������
	wndClass.hInstance = hInstance;									//�ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ�����̸�
	wndClass.lpszMenuName = NULL;									//�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	DEVMODE dm; //����̽� ���

	//����̽���带 0���� �ʱ�ȭ ���ش�
	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32; //Ʈ���÷� 32��Ʈ
	dm.dmPelsWidth = 1600; //�ػ� ���α���
	dm.dmPelsHeight = 900; //�ػ� ���α���
	dm.dmDisplayFrequency = 60; //����� 60Hz
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
	
	//ȭ���� ����Ǹ� �ڵ����� ���� ȭ���� �ػ󵵷� ���������ִ� �ڵ�
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,						//������ Ŭ������ �̸�
		WINNAME,						//������ Ÿ��Ʋ�� �̸�
		WS_POPUPWINDOW | WS_MAXIMIZE,	//������ ��Ÿ��
		0,								//������ ȭ����ǥ x
		0,								//������ ȭ����ǥ y
		WINSIZEX,						//������ ȭ����ǥ width
		WINSIZEY,						//������ ȭ����ǥ height
		NULL,							//�θ� ������
		(HMENU)NULL,					//�޴��ڵ�
		hInstance,						//�ν��Ͻ� ����
		NULL);							//������ �� �ڽ� �����츦 �����ϸ�
	//�������ֵ� �׷��� ������ NULL

	//ȭ�� �۾� ������ ���� ���
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#else
	//������ ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTARTX,				//������ ȭ����ǥ x
		WINSTARTY,				//������ ȭ����ǥ y
		WINSIZEX,				//������ ȭ����ǥ width
		WINSIZEY,				//������ ȭ����ǥ height
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL);					//������ �� �ڽ� �����츦 �����ϸ�
								//�������ֵ� �׷��� ������ NULL

	//ȭ�� �۾� ������ ���� ���
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#endif

	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, nCmdShow);


	if (FAILED(_gs.init()))
	{
		//�����ϸ� �ٷ� ����.
		return 0;
	}

	while (true) //���ӿ�
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0F);
			_gs.update(); //���͵� ������Ʈ
			_gs.render(); //���͵� ����
		}
	}

	//���͵� ����..
	_gs.release();
	
	/*
	//�Ϲ� ���α׷���
	while (GetMessage(&message, 0, 0, 0)) 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/


	//������ Ŭ���� ��� ����...
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}
//======================================================
//======================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
						 WPARAM wParam, LPARAM lParam)
{
	return _gs.MainProc(hWnd, iMessage, wParam, lParam);
}
//======================================================
//======================================================
void setWindowSize(int x, int y, int width, int height)
{
	//������ �۾����� ����
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);
	//���� RECT ������ ������ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}

