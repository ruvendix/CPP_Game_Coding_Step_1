// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 마지막에 발생된 에러에 해당되는 내용을 알려줍니다.
// 에러가 발생되자마자 에러 핸들러가 작동됩니다.
// =====================================================================================
#include "EnginePCH.h"
#include "ErrorTracer.h"

class ErrorTracerInside final
{
public:
	ErrorTracerInside() = default;
	~ErrorTracerInside() = default;

	void StartUp();
	const Char* FindErrorString(EErrorCode errorCode) const;

private:
	std::unordered_map<EErrorCode, std::string> m_mapErrorString;
};

void ErrorTracerInside::StartUp()
{
	m_mapErrorString.emplace(EErrorCode::UNKNOWN, "알 수 없는 에러!");
	m_mapErrorString.emplace(EErrorCode::INDIRECT_NULLPTR, "nullptr을 역참조할 수 없음!!");
	m_mapErrorString.emplace(EErrorCode::OUT_OF_HEAP_MEMORY, "힙 메모리 부족!");

	m_mapErrorString.emplace(EErrorCode::DUPLICATED_SUBSYSTEM, "중복된 서브시스템!");
	m_mapErrorString.emplace(EErrorCode::REGISTER_SUBSYSTEM_FAIL, "서브시스템 등록 실패!");
	m_mapErrorString.emplace(EErrorCode::NOT_EXIST_SUBSYSTEM, "존재하지 않는 서브시스템!");	

	m_mapErrorString.emplace(EErrorCode::CLEAR_SCREEN_FAIL, "화면 지우기 실패!");
	m_mapErrorString.emplace(EErrorCode::INVALID_SCREEN_COLOR, "유효하지 않은 화면 색상!");

	m_mapErrorString.emplace(EErrorCode::OUT_OF_GAMEOBJECT, "더 이상 게임 오브젝트를 생성할 수 없음!");

	m_mapErrorString.emplace(EErrorCode::OPEN_FILE_STREAM_FAIL, "파일 스트림 열기 실패!");
	m_mapErrorString.emplace(EErrorCode::CLOSE_FILE_STREAM_FAIL, "파일 스트림 닫기 실패!");

	m_mapErrorString.emplace(EErrorCode::DUPLICATED_COMPONENT, "중복된 컴포넌트: %s!");
	m_mapErrorString.emplace(EErrorCode::ADD_COMPONENT_FAIL, "컴포넌트 추가 실패: %s!");
	m_mapErrorString.emplace(EErrorCode::NOT_EXIST_COMPONENT, "존재하지 않는 컴포넌트: %s!");

	m_mapErrorString.emplace(EErrorCode::CASTING_FAIL, "캐스팅 실패!");
}

const Char* ErrorTracerInside::FindErrorString(EErrorCode errorCode) const
{
	const auto& iter = m_mapErrorString.find(errorCode);
	if (iter == m_mapErrorString.cend())
	{
		return "등록되지 않은 에러입니다!";
	}

	return iter->second.c_str();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	에러 핸들러를 초기화합니다.
	에러 타입에 해당되는 에러 내용을 설정해요.
*/
void ErrorTracer::StartUp()
{
	m_pInside = new ErrorTracerInside;
	m_pInside->StartUp();
}

/*
	에러 핸들러를 정리합니다.
	아직은 추가할 내용이 없어요.
*/
void ErrorTracer::CleanUp()
{
	SAFE_DELETE(m_pInside);
}

/*
	마지막에 발생된 에러에 해당되는 내용을 가져옵니다.
*/
const Char* ErrorTracer::LastErrorString() const
{
	EErrorCode errorCode = GetLastErrorCode();
	return m_pInside->FindErrorString(errorCode);
}