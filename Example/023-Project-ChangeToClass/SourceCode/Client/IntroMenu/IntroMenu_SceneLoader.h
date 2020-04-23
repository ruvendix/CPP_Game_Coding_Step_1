// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ�����Դϴ�.
// �������� �̿��ؼ� ���� �ε��մϴ�.
// =====================================================================================

#ifndef INTRO_MENU_SCENE_LOADER_H__
#define INTRO_MENU_SCENE_LOADER_H__

#include "Element\Menu\Menu.h"

enum class EMiniGameSceneType
{
	UNKNOWN = 0,
	BATTLE_SIMULATOR2,
	DIALOG_TREE,
	MISCELLANEOUS_SHOP2
};

class IntroMenu_SceneLoader final : public Menu
{
	DECLARE_RTTI(IntroMenu_SceneLoader, Menu);

public:
#pragma region ������ �� �Ҹ���
	using Menu::Menu;

	IntroMenu_SceneLoader() = default;
	virtual ~IntroMenu_SceneLoader() = default;

	IntroMenu_SceneLoader(const std::string_view& szNameTag,
		const COORD& pos, const COORD& offsetCenterPos, EMiniGameSceneType miniGameSceneType);
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_Excute() override;

private:
	EMiniGameSceneType m_selectedSceneType = EMiniGameSceneType::UNKNOWN;
};

#endif