// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 스톱워치입니다.
// 종료 시간까지의 경과 시간을 계산합니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

// 전방 선언
class StopwatchInside;

class Stopwatch
{
public:
	Stopwatch();
	~Stopwatch();

	void StartTime();
	Float EndTime();

private:
	std::unique_ptr<StopwatchInside> m_spInside = nullptr;
};