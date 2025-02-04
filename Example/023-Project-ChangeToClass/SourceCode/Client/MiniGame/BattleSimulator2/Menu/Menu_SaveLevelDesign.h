// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 메뉴입니다.
// 레벨 디자인을 저장합니다.
// =====================================================================================

#ifndef MENU_SAVE_LEVEL_DESIGN_H__
#define MENU_SAVE_LEVEL_DESIGN_H__

#include "Element\Menu\Menu.h"

class BattleSimulator2_EditorScene;

class Menu_SaveLevelDesign final : public Menu
{
	DECLARE_RTTI(Menu_SaveLevelDesign, Menu);

public:
	using Menu::Menu;

#pragma region 생성자 및 소멸자
	Menu_SaveLevelDesign() = default;
	virtual ~Menu_SaveLevelDesign() = default;

	Menu_SaveLevelDesign(const std::string_view& szNameTag,
		const COORD& pos, BattleSimulator2_EditorScene* pTargetScene);
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_Excute() override;

private:
	BattleSimulator2_EditorScene* m_pTargetScene = nullptr;
};

#endif