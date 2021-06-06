// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�̸��Դϴ�.
// ��ǥ �ð������� ��� �ð��� ��Ȯ�� ����� �ϹǷ� ��ŸŸ���� �̿��մϴ�.
// ��ŸŸ���� Time Ŭ������ �ֽ��ϴ�. (�̸��� ����ϴϱ� ����!)
// =====================================================================================
#include "EnginePCH.h"
#include "Timer.h"

#include "Subsystem/FrameManager/IFrameManager.h"

/*
	��ŸŸ���� �����ϸ鼭 ��ǥ �ð����� �޼��ߴ��� Ȯ���մϴ�.
	��ǥ �ð����� �޼������� true��, �ƴ϶�� false�� ��ȯ�մϴ�.
*/
Bool Timer::UpdateTime()
{
	if (m_bEnable == false)
	{
		return false;
	}

	IFrameManager::DataPtr spData = FIND_SUBSYSTEM(IFrameManager)->Data();
	m_localTime += spData->GetDeltaTime();
	FIND_SUBSYSTEM(IConsoleHandler)->RenderString(0, 1, MakeFormatString("localTime: %f", m_localTime).c_str());

	if (m_targetTime > m_localTime)
	{
		return false;
	}

	m_localTime = 0.0f;

	if (m_bLoop == false)
	{
		m_bEnable = false;
	}

	return true;
}