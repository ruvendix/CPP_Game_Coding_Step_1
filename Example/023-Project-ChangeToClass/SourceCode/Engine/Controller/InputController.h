// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 키보드와 마우스 입력을 제어합니다.
// 델타타임마다 폴링하므로 문자열 비교 대신 열거형으로 고정합니다.
// =====================================================================================

#ifndef INPUT_CONTROLLER__H__
#define INPUT_CONTROLLER__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonEnum.h"
#include "Common\CommonMacro.h"

DECLARE_LOG_CATEGORY(InputController);

struct InputMappingInfo
{
	std::vector<TInput> vecInput; // 입력 조합 (가상키는 0 ~ 255)
	std::list<TInput> listInputChecker; // 입력 조합이 완성되었는지 확인하기 위한 것 (이전 프레임도 확인해야 하므로...)
	EInputMappingState state = EInputMappingState::NONE; // 입력 조합의 상태 (5가지)
};

class InputController final
{
	DECLARE_SINGLETON(InputController);

public:
	using MapInputMappingInfo = std::unordered_map<std::string, InputMappingInfo*>;

	static const Int32 INPUT_DOWN_FLAG = 0x8000; // 입력값이 눌렸거나 눌려있는지 확인하는 용도
	static const Uint8 MAX_INPUT_RANGE = UINT8_MAX;

	void PollInput();
	void DeleteAllInputMappingInfo();
	bool CheckInputState(const std::string_view& szInputAction, EInputMappingState inputState) const;
	InputMappingInfo* FindInputMappingInfo(const std::string_view& szInputAction) const;

	// 가변 인자 템플릿에서의 Base Case에요!
	template <typename TInputVal>
	void InsertInputMappingInfo(const TInputVal& inputVal)
	{
		const std::string& strInputValType = typeid(TInputVal).name();
		if (strInputValType == "char")
		{
			if (std::isupper((Int32)inputVal) == 0)
			{
				DEBUG_LOG_CATEGORY(InputController, "매핑 입력값은 대문자만 가능해요!");
				return;
			}

			m_pInputMappingInfo->vecInput.push_back((Uint32)inputVal);
		}
		else if (strInputValType == "int") // 가상키를 의미해요!
		{
			m_pInputMappingInfo->vecInput.push_back((Uint32)inputVal);
		}

		return;
	}
	
	// 입력값을 추가할 때 자료형이 달라질 수 있으므로 가변 인자 템플릿을 사용할게요! (매핑 입력값은 char 아니면 int)
	// const로 인해 C++의 캐스팅은 사용할 수 없으니까 강제로 캐스팅해야 해요!
	template <typename TInputVal, typename ... types>
	void InsertInputMappingInfo(const TInputVal& inputVal, const types& ... args)
	{
		if (m_pInputMappingInfo == nullptr)
		{
			m_pInputMappingInfo = new InputMappingInfo; // 해제는 자료구조에서!
		}

		const std::string& strInputValType = typeid(TInputVal).name();
		if (strInputValType == "char")
		{
			if (std::isupper((Int32)inputVal) == 0)
			{
				DEBUG_LOG_CATEGORY(InputController, "매핑 입력값은 대문자만 가능해요!");
				return;
			}

			m_pInputMappingInfo->vecInput.push_back((Uint32)inputVal);
		}
		else if (strInputValType == "int") // 가상키를 의미해요!
		{
			m_pInputMappingInfo->vecInput.push_back((Uint32)inputVal);
		}
		else // 첫 번째 인자만 여기에 들어와야 해요!
		{
			if (m_bCheckInputAction == true)
			{
				DEBUG_LOG_CATEGORY(InputController, "매핑 입력값의 두 번째 인자는 문자열이 올 수 없어요!");
				return;
			}

			m_mapInputMappingInfo[reinterpret_cast<const char*>(inputVal)] = m_pInputMappingInfo;
			m_bCheckInputAction = true;
		}

		InsertInputMappingInfo(args ...);

		m_pInputMappingInfo = nullptr;
		m_bCheckInputAction = false;

		DEBUG_LOG_CATEGORY(InputController, "입력 조합 추가 완료! (%s)", inputVal);
	}

private:
	// InsertInputMappingInfo()에서만 사용되는 변수들
	bool m_bCheckInputAction = false; // 두 번째 인자부터 걸러내기 위한 것!
	InputMappingInfo* m_pInputMappingInfo = nullptr; // 중복 할당을 막기 위한 것!
	
	MapInputMappingInfo m_mapInputMappingInfo;
};

#endif