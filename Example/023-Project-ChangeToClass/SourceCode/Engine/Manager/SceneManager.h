// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 씬 생성 및 전환 등을 처리해주는 매니저입니다.
// =====================================================================================

#ifndef SCENE_MGR__H__
#define SCENE_MGR__H__

#include "Common\CommonType.h"
#include "Element\Scene.h"

DECLARE_LOG_CATEGORY(SceneMgr);

class SceneMgr final
{
	DECLARE_SINGLETON(SceneMgr);

public:
	void DeleteScene();
	void FlipCurrentScene();

	bool IsGotoNextScene() const
	{
		return (m_bGotoNextScene == true);
	}

	Scene* getCurrentScene() const
	{
		CHECK_NULLPTR(m_pCurrentScene);
		return m_pCurrentScene;
	}

	template <typename TScene>
	void CreateScene(const std::string_view& szSceneName, ESceneType sceneType)
	{
		if (sceneType == ESceneType::CURRENT)
		{
			if (m_pCurrentScene != nullptr)
			{
				DEBUG_LOG_CATEGORY(SceneMgr, "%s 씬이 이미 존재합니다!", m_pCurrentScene->getNameTag().data());
				return;
			}

			m_pCurrentScene = new TScene(szSceneName);

			if (m_pCurrentScene->OnInitialize() == EErrorType::INIT_FAILED)
			{
				ErrorHandler::ShowError(EErrorType::INIT_FAILED);
			}
		}
		else
		{
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = new TScene(szSceneName);

			// 전환될 예정인 씬은 초기화가 완료된 상태로 전환되어야 해요!
			if (m_pNextScene->OnInitialize() == EErrorType::INIT_FAILED)
			{
				ErrorHandler::ShowError(EErrorType::INIT_FAILED);
			}

			m_bGotoNextScene = true;
		}
	}

	template <typename TScene>
	void CreateScene(ESceneType sceneType)
	{
		CreateScene<TScene>(TO_STRING(TScene), sceneType);
	}

private:
	Scene* m_pCurrentScene = nullptr;
	Scene* m_pNextScene = nullptr;
	bool m_bGotoNextScene = false;
};

#endif