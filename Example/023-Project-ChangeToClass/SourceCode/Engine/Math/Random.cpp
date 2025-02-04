// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 랜덤 관련 유틸리티 클래스입니다.
// 시드값을 초기화해야 정상적으로 사용할 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "Random.h"

namespace rx_math
{

	std::default_random_engine Random::m_defaultRandomEngine;

	/*
	디폴트 랜덤 엔진에 시드값 목록을 적용해서 초기화합니다.
	*/
	void Random::Initialize()
	{
		std::array<Int32, std::default_random_engine::state_size> arrRandomSeed; // 시드값은 624개
		std::generate_n(arrRandomSeed.begin(), arrRandomSeed.size(), std::ref(m_defaultRandomEngine)); // 624개의 랜덤 시드값 생성
		std::seed_seq seedSeq(std::begin(arrRandomSeed), std::end(arrRandomSeed)); // 생성된 624개의 랜덤 시드값을 전용 객체로 복사
		m_defaultRandomEngine = std::default_random_engine(seedSeq); // 메르센 트위스터에 시드값 적용
	}

	/*
	정수 균일 분포로 랜덤값을 뽑습니다.
	일반적인 랜덤값 생성입니다.
	*/
	Int32 Random::GenerateRandom(Int32 begin, Int32 end)
	{
		std::uniform_int_distribution<Int32> uniformIntDistribution(begin, end);
		return uniformIntDistribution(m_defaultRandomEngine);
	}

	/*
	실수 균일 분포로 랜덤값을 뽑습니다.
	일반적인 랜덤값 생성입니다.
	*/
	Real32 Random::GenerateRandom(Real32 begin, Real32 end)
	{
		std::uniform_real_distribution<Real32> uniformRealDistribution(begin, end);
		return uniformRealDistribution(m_defaultRandomEngine);
	}

	/*
	사건 개수와 사건이 일어날 확률을 넣은 정수 이항 분포로 랜덤값을 뽑습니다.
	*/
	Int32 Random::GenerateBinormalRandom(Int32 eventCnt, Real32 probability)
	{
		std::binomial_distribution<Int32> binomialDistribution(eventCnt, probability);
		return binomialDistribution(m_defaultRandomEngine);
	}

} // namespace math end