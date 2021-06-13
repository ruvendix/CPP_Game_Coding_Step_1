// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프로그램의 진입점입니다.
// =====================================================================================

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

#include <EnginePCH.h>
#include <Scene/GameObject/GameObject.h>

#include <Utility/Time/Stopwatch.h>

Int32 main()
{
	FrameworkPathfinder::SetUp();
	SubsystemLocator::I().SetUp();

	GameObject* pGameObject = new GameObject;
	pGameObject->SetUp();
	FIND_SUBSYSTEM(IGameObjectManager)->AddGameObject(pGameObject);

	Int32 callCount = 60 * 50000; // 5초
	while (callCount != 0)
	{
		FIND_SUBSYSTEM(IGameObjectManager)->UpdateAllGameObject();
		FIND_SUBSYSTEM(IConsoleHandler)->ClearScreen();
		FIND_SUBSYSTEM(IGameObjectManager)->RenderAllGameObject();
		FIND_SUBSYSTEM(IFrameManager)->UpdateFrameTime();
		FIND_SUBSYSTEM(IConsoleHandler)->FlipOutputBuffer();

		--callCount;
	}

	SubsystemLocator::I().CleanUp();
	return 0;
}