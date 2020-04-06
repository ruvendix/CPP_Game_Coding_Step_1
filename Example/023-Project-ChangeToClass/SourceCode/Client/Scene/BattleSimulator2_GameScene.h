// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2 게임 씬입니다.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_GAME_SCENE_H__
#define BATTLE_SIMULATOR2_GAME_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2World.h"

class MedievalKnight;
class Viking;

DECLARE_LOG_CATEGORY(BattleSimulator2_GameScene);

class BattleSimulator2_GameScene final : public Scene
{
	FRIEND_WITH_HELPER(BattleSimulator2SceneHelper);

public:
#pragma region 생성자 및 소멸자
	using Scene::Scene;
	virtual ~BattleSimulator2_GameScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	std::unique_ptr<BattleSimulator2World> m_world;
	std::vector<std::shared_ptr<MedievalKnight>> m_vecMedievalKnight;
	std::vector<std::shared_ptr<Viking>> m_vecViking;

	bool m_bBattleEnd = false;
};

#endif