// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 로거에 사용되는 열거형입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

namespace EnumIdx
{
	namespace LogOption
	{
		enum Data : Uint32
		{
			TIME = 0,
			ABSOLUTE_FILEPATH,
			RELATIVE_FILEPATH,
			LINE,
			COUNT,
		};
	}
}