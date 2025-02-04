// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 바이킹입니다.
// =====================================================================================

#include "PCH.h"
#include "Viking.h"

VikingPtr Viking::Clone()
{
	return std::make_shared<Viking>(*this);
}
