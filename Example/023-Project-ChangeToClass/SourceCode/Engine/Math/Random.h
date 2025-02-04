// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 랜덤 클래스입니다.
// 시드값을 초기화해야 정상적으로 사용할 수 있습니다.
// =====================================================================================

#ifndef RANDOM__H__
#define RANDOM__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

namespace rx_math
{
	
	class Random
	{
		NON_COPYABLE_ONLY_PRIVATE_CLASS(Random);

	public:
		static void Initialize();
		
		static Int32 GenerateRandom(Int32 begin, Int32 end);
		static Int32 GenerateBinormalRandom(Int32 eventCnt, Real32 probability);

		static Real32 GenerateRandom(Real32 begin, Real32 end);

	private:
		static std::default_random_engine m_defaultRandomEngine; // std::mt19937 (Mersenne Twister, 메르센 트위스터)
	};

} // namespace math end

#endif