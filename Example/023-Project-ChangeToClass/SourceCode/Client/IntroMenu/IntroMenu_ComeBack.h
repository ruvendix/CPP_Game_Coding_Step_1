// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 인트로 메뉴 씬으로 돌아오게 해줍니다.
// 여러 게임에서 사용 가능합니다.
// =====================================================================================

#ifndef INTRO_MENU_COME_BACK_H__
#define INTRO_MENU_COME_BACK_H__

#include "Element\Menu\Menu.h"

class IntroMenu_ComeBack final : public Menu
{
	DECLARE_RTTI(IntroMenu_ComeBack, Menu);

public:
#pragma region 생성자 및 소멸자
	using Menu::Menu;
	virtual ~IntroMenu_ComeBack() = default;
#pragma endregion

	virtual EErrorType OnExcute() override;
};

#endif