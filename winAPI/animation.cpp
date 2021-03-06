#include "StdAfx.h"
#include "animation.h"

animation::animation(void)
	:_frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIdx(0),
	_play(FALSE)
{
}

animation::~animation(void)
{
}


//이미지 총 가로세로크기와 한 프레임의 가로세로 크기로 셋팅
HRESULT	animation::init(int totalW, int totalH, int frameW, int frameH)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//가로 프레임 수
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	//프레임 위치 리스트 셋팅
	_frameList.clear();
	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 리스트에 추가
			_frameList.push_back(framePos);
		}
	}

	//기본 프레임 으로 셋팅
	setDefPlayFrame();

	return S_OK;
}


//기본 셋팅
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//다시 되돌아 오는 애니메이션이라면...
	if (reverse)
	{
		//루프 애니메이션이면...
		if (_loop)
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i > 0; i--)		// 루프기때문에 마지막 시작 프레임은 빠진다.
			{
				_playList.push_back(i);
			}
		}
		//루프 애니메이션이 아니면..
		else
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i >= 0; i--)		// 루프가 아니기 때문에 마지막 시작 프레임 까지 포함
			{
				_playList.push_back(i);
			}
		}
	}

	//다시 되될아 오는 애니메이션이 아니라면..
	else
	{
		//갈때 저장
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	//콜백
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//다시 되돌아 오는 애니메이션이라면...
	if (reverse)
	{
		//루프 애니메이션이면...
		if (_loop)
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i > 0; i--)		// 루프기때문에 마지막 시작 프레임은 빠진다.
			{
				_playList.push_back(i);
			}
		}
		//루프 애니메이션이 아니면..
		else
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i >= 0; i--)		// 루프가 아니기 때문에 마지막 시작 프레임 까지 포함
			{
				_playList.push_back(i);
			}
		}
	}

	//다시 되될아 오는 애니메이션이 아니라면..
	else
	{
		//갈때 저장
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	//콜백
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//다시 되돌아 오는 애니메이션이라면...
	if (reverse)
	{
		//루프 애니메이션이면...
		if (_loop)
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i > 0; i--)		// 루프기때문에 마지막 시작 프레임은 빠진다.
			{
				_playList.push_back(i);
			}
		}
		//루프 애니메이션이 아니면..
		else
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i >= 0; i--)		// 루프가 아니기 때문에 마지막 시작 프레임 까지 포함
			{
				_playList.push_back(i);
			}
		}
	}

	//다시 되될아 오는 애니메이션이 아니라면..
	else
	{
		//갈때 저장
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//플레이 프레임 배열로 셋팅
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//정직하게 프레임으로 셋팅
	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//정직하게 프레임으로 셋팅
	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//정직하게 프레임으로 셋팅
	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

//플레이 프레임 시작과 종료로 셋팅
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//if (start == end)
	//{
	//	//시작프레임과 끝프레임이 같은경우
	//	_playList.clear();
	//	stop();			//애니메이션 실행이 될 필요가 없다.
	//	return;
	//}


	//시작 프레임이 종료 프레임 보다 큰경우 
	if (start > end)
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}

			}

			//루프 애니메이션이 아니면..
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}

		else
		{
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//nStart < nEnd
	else
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}

			//루프 애니메이션이 아니면..
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	if (start == end)
	{
		//시작프레임과 끝프레임이 같은경우
		_playList.clear();
		stop();			//애니메이션 실행이 될 필요가 없다.
		return;
	}


	//시작 프레임이 종료 프레임 보다 큰경우 
	if (start > end)
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}

			}

			//루프 애니메이션이 아니면..
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}

		else
		{
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//nStart < nEnd
	else
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}

			//루프 애니메이션이 아니면..
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	if (start == end)
	{
		//시작프레임과 끝프레임이 같은경우
		_playList.clear();
		stop();			//애니메이션 실행이 될 필요가 없다.
		return;
	}


	//시작 프레임이 종료 프레임 보다 큰경우 
	if (start > end)
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}

			}

			//루프 애니메이션이 아니면..
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}

		else
		{
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//nStart < nEnd
	else
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}

			//루프 애니메이션이 아니면..
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::release(void)
{
}

//초당 갱신 횟수
void animation::setFPS(float framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//프레임 업데이트
void animation::frameUpdate(float elpasedTime)
{
	if (_play)
	{
		_elapsedSec += elpasedTime;
		
		//프레임 업데이트 시간이 되었다면..
		if (_elapsedSec >= _frameUpdateSec)
		{
			//_elapsedSec -= _frameUpdateSec;
			_elapsedSec = 0.f;
			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{
				//루프 플레이 라면...
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				//루프 플레이가 아니라면..
				else
				{
					if (_obj == NULL)
					{
						if (_callbackFunction != NULL) _callbackFunction();
					}
					else
					{
						_callbackFunctionParameter(_obj);
					}
					_nowPlayIdx--;
					_play = FALSE;
				}
			}
		}
	}
}


//플레이 시작
void animation::start(void)
{

	_play = TRUE;
	_nowPlayIdx = 0;
}

//플레이 완전 정지
void animation::stop(void)
{
	_play = FALSE;
	_nowPlayIdx = 0;
}

//플레이 일시 정시
void animation::pause(void)
{
	_play = FALSE;
}

//플레이 다시 시작
void animation::resume(void)
{
	_play = TRUE;
}