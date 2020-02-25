// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 인트로 메뉴 씬에서 사용되는 보조 클래스의 기본형입니다.
// =====================================================================================

#include "PCH.h"
#include "IntroMenu.h"

IntroMenu::IntroMenu(const std::string_view& szNameTag, const COORD& offsetCenterPos) :
	m_nameTag(szNameTag),
	m_pos{ 0, 0 },
	m_offsetCenterPos(offsetCenterPos)
{

}

EErrorType IntroMenu::OnExcute()
{
	DEBUG_LOG("IntroMenu에서 이게 보이면 OnExcute()를 재정의해주세요!");
	return EErrorType::NONE;
}
