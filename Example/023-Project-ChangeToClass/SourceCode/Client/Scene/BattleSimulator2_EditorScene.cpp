// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터 에디터 씬입니다.
// 기본 월드에 다양한 레벨 디자인을 만들 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_EditorScene.h"

#include "Controller\FrameController.h"
#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "Element\Menu\Menu.h"
#include "Element\Menu\MenuTable_Row.h"

#include "Scene\IntroMenuScene.h"
#include "IntroMenu\IntroMenu_ComeBack.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2World.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_LevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_ResetLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_EditLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_SaveLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_LoadLevelDesign.h"
#include "MiniGame\BattleSimulator2\Menu\Menu_StartGame.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\MedievalKnight.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\Viking.h"

namespace
{
	std::unique_ptr<UI_PosInfo> s_spUI_posInfo;
}

class BattleSimulator2_EditorSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2_EditorSceneHelper);

public:
	static void DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Row> spMenuTable);

	static void OnInput_MenuMode(_Inout_ BattleSimulator2_EditorScene& targetHelper);
	static void OnInput_EditorMode(_Inout_ BattleSimulator2_EditorScene& targetHelper);
};

void BattleSimulator2_EditorSceneHelper::DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Row> spMenuTable)
{
	Int32 drawPosX = pos.X;
	Int32 drawPosY = spMenuTable->getFirstMenu()->getPos().Y - 1;

#pragma region 위쪽 경계선
	PUT_STRING(drawPosX, drawPosY, "┏");
	
	TSize drawLength =
		(spMenuTable->getLongestMenu()->getNameTag().size() / 2) + (ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU / 2) + 1;

	for (TSize i = 0; i < drawLength; ++i)
	{
		drawPosX += 2;
		PUT_STRING(drawPosX, drawPosY, "━");		
	}

	PUT_STRING(drawPosX, drawPosY, "┓");
#pragma endregion

#pragma region 양쪽 경계선
	drawPosX = pos.X;
	TSize menuCnt = spMenuTable->getMenuCnt();
	for (TSize i = 0; i < menuCnt; ++i)
	{
		PUT_STRING(drawPosX, ++drawPosY, "┃");
		PUT_STRING(drawPosX + (drawLength * 2), drawPosY, "┃");
	}
#pragma endregion

#pragma region 아래쪽 경계선
	drawPosX = pos.X;
	PUT_STRING(drawPosX, ++drawPosY, "┗");

	for (TSize i = 0; i < drawLength; ++i)
	{
		drawPosX += 2;
		PUT_STRING(drawPosX, drawPosY, "━");
	}

	PUT_STRING(drawPosX, drawPosY, "┛");
#pragma endregion

	spMenuTable->DrawMenu();
}

void BattleSimulator2_EditorSceneHelper::OnInput_MenuMode(_Inout_ BattleSimulator2_EditorScene& targetHelper)
{
	targetHelper.m_spEditorMenuTable->OnInput();

	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		targetHelper.m_spEditorMenuTable->getLastMenu()->OnExcute();
	}
}

void BattleSimulator2_EditorSceneHelper::OnInput_EditorMode(_Inout_ BattleSimulator2_EditorScene& targetHelper)
{
	if (InputController::I()->CheckInputState("MenuMode", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->RestoreConsoleSelector();

		COORD selectorPos = ConsoleController::I()->QueryCurrentConsoleSelectorPos();
		selectorPos.X += (ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);

		Int32 currentMenuIdx = targetHelper.m_spEditorMenuTable->ToMenuIdx(selectorPos);
		targetHelper.m_spEditorMenuTable->setCurrentMenuIdx(currentMenuIdx);

		targetHelper.m_currentSampleUnitIdx = 0;
		targetHelper.m_mode = EMode::MENU;
	}

	if (InputController::I()->CheckInputState("Left", EInputMappingState::DOWN) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		Int32 movePosX = static_cast<Int32>(consoleSelector.getShapeLength()) * -1;
		ConsoleController::I()->AddSelectorPosX(movePosX);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuLeft 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Right", EInputMappingState::DOWN) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		ConsoleController::I()->AddSelectorPosX(+consoleSelector.getShapeLength());

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuRight 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Up", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Down", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuDown 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SpawnObj", EInputMappingState::DOWN) == true)
	{
		// 레벨을 통해서 월드에 스폰!
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		COORD mappingPos = consoleSelector.getSelectorPos();
		mappingPos.X = mappingPos.X / consoleSelector.getShapeLength();

		// 현재 선택된 아이디
		switch (targetHelper.getCurrentSampleUnit()->getObjID())
		{
		case EDynamicObjID::VIKING:
		{
			std::shared_ptr<Viking> spViking = std::make_shared<Viking>();
			spViking->Copy(targetHelper.getCurrentSampleUnit());
			spViking->setPos(mappingPos);
			targetHelper.m_spCurrentLevelDesign->SpawnGameObj(spViking);

			break;
		}

		case EDynamicObjID::MEDIEVALKNIGHT:
		{
			std::shared_ptr<MedievalKnight> spMedievalKnight = std::make_shared<MedievalKnight>();
			spMedievalKnight->Copy(targetHelper.getCurrentSampleUnit());
			spMedievalKnight->setPos(mappingPos);
			targetHelper.m_spCurrentLevelDesign->SpawnGameObj(spMedievalKnight);

			break;
		}

		default:
		{
			ERROR_HANDLER(false, EErrorType::UNKNOWN_DYNAMIC_OBJ);
			break;
		}
		}

		DEBUG_LOG("SpawnObj 눌렀다!");
	}

	if (InputController::I()->CheckInputState("ChangeObj", EInputMappingState::DOWN) == true)
	{	
		++targetHelper.m_currentSampleUnitIdx;
		targetHelper.m_currentSampleUnitIdx = math::ClampCycle(targetHelper.m_currentSampleUnitIdx,
			0, targetHelper.m_vecSampleUnit.size() - 1);

		ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		std::shared_ptr<Unit> spSampleUnit = targetHelper.getSampleUnit(targetHelper.m_currentSampleUnitIdx);
		consoleSelector.setShape(spSampleUnit->getShape());

		DEBUG_LOG("SpawnObj 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
	if (InputController::I()->CheckInputState("Left", EInputMappingState::PRESSING) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		Int32 movePosX = static_cast<Int32>(consoleSelector.getShapeLength()) * -1;
		ConsoleController::I()->AddSelectorPosX(movePosX);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuLeft 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Right", EInputMappingState::PRESSING) == true)
	{
		const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		ConsoleController::I()->AddSelectorPosX(+consoleSelector.getShapeLength());

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuRight 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Up", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Down", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);

		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("MenuDown 눌렀다!");
	}
	END_INPUT_FPS_LIMITED();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulator2_EditorScene);

EErrorType BattleSimulator2_EditorScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulator2_EditorScene, "배틀 시뮬레이터 에디터 씬!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("MenuMode", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("Up", VK_UP);
	InputController::I()->InsertInputMappingInfo("Down", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("Left", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("Right", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("ChangeObj", 'A');
	InputController::I()->InsertInputMappingInfo("SpawnObj", VK_RETURN);

	m_spWorld = std::make_shared<BattleSimulator2World>(SizeInfo{ 40, 30 });

	// 월드 파일이 있는지?
	// 있다면 파일을 읽고, 아니면 새로 초기화해야 해요!
	EErrorType errorType = m_spWorld->LoadFile("BattleSimulatorWorld2.world");
	if (errorType == EErrorType::LOAD_FILE_FAIL)
	{
		m_spWorld->setLastError(EErrorType::LOAD_FILE_FAIL);

		if (m_spWorld->OnInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}
	}

	s_spUI_posInfo = std::make_unique<UI_PosInfo>();
	s_spUI_posInfo->startPos = COORD{ 85, 10 };
	s_spUI_posInfo->menuStartPos = s_spUI_posInfo->startPos;
	s_spUI_posInfo->menuStartPos.X += ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU;
	s_spUI_posInfo->menuStartPos.Y += 1;
	s_spUI_posInfo->diffSize.height = 1;

	m_spEditorMenuTable = std::make_shared<MenuTable_Row>();
	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_ResetLevelDesign>("레벨 디자인 초기화",
		COORD{ s_spUI_posInfo->menuStartPos.X, s_spUI_posInfo->menuStartPos.Y }, this));

	Int32 diffMultipleFactor = 0;
	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_EditLevelDesign>("레벨 디자인 편집",
		COORD{ s_spUI_posInfo->menuStartPos.X,
			   s_spUI_posInfo->menuStartPos.Y +
			   static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }, this));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_SaveLevelDesign>("레벨 디자인 저장",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }, this));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu_LoadLevelDesign>("레벨 디자인 열기",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }, this));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu>("게임 시작",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

	m_spEditorMenuTable->AddMenu(std::make_shared<IntroMenu_ComeBack>("나가기",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		       s_spUI_posInfo->menuStartPos.Y +
		       static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

	m_vecSampleUnit.push_back(std::make_shared<MedievalKnight>(EDynamicObjID::MEDIEVALKNIGHT, "Ω"));
	m_vecSampleUnit.push_back(std::make_shared<Viking>(EDynamicObjID::VIKING, "♠"));

	m_spCurrentLevelDesign = std::make_shared<BattleSimulator2_LevelDesign>(m_spWorld);

	return EErrorType::NONE;
}

EErrorType BattleSimulator2_EditorScene::OnPostInitialize()
{
	if (m_spWorld->getLastError() == EErrorType::LOAD_FILE_FAIL)
	{
		if (m_spWorld->OnPostInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}

		m_spWorld->ResetError();
	}

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(
		s_spUI_posInfo->startPos.X + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER, s_spUI_posInfo->menuStartPos.Y);
	consoleSelector.setMinSelectorPosY(s_spUI_posInfo->startPos.Y);
	consoleSelector.setMaxSelectorPosY(s_spUI_posInfo->startPos.Y + m_spEditorMenuTable->getLastIdx());

	return EErrorType::NONE;
}

EErrorType BattleSimulator2_EditorScene::OnInput()
{
	if (m_mode == EMode::MENU)
	{
		BattleSimulator2_EditorSceneHelper::OnInput_MenuMode(*this);
	}
	else
	{
		BattleSimulator2_EditorSceneHelper::OnInput_EditorMode(*this);
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulator2_EditorScene::OnUpdate()
{
	return EErrorType::NONE;
}

EErrorType BattleSimulator2_EditorScene::OnRender()
{
	if (m_spWorld->OnRender() == EErrorType::RENDER_FAIL)
	{
		return EErrorType::RENDER_FAIL;
	}

	BattleSimulator2_EditorSceneHelper::DrawMenu(s_spUI_posInfo->startPos, m_spEditorMenuTable);
	ConsoleController::I()->DrawSelector();

	return EErrorType::NONE;
}

EErrorType BattleSimulator2_EditorScene::OnFinalize()
{
	m_spWorld->SaveFile("BattleSimulator2.world"); // 월드는 오토 세이브!
	return EErrorType::NONE;
}
