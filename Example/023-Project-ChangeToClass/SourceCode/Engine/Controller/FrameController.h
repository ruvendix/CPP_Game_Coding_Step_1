// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �������� �����ϴ� ��Ʈ�ѷ��Դϴ�.
// ������ ������ FPS�� ���� �����̸� �����ϴ� ����� �ֽ��ϴ�.
// ������ �������� ���ػ� ���� �Լ��� ����߽��ϴ�.
// ������ ����� (���� ������ + ������ ��Ű��)�� ����߽��ϴ�.
// =====================================================================================

#ifndef FRAME_CONTROLLER__H__
#define FRAME_CONTROLLER__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

DECLARE_LOG_CATEGORY(FrameController);

class FrameController final
{
	DECLARE_SINGLETON(FrameController);
	FRIEND_WITH_HELPER(FrameControllerHelper);

public:
	void Initialize();
	void UpdateFPSAndDeltatime();
	void ModifyLimitedFrame(Int32 limitedFrame);

	void ResetTimeScale()
	{
		m_timeScale = 1.0f;
	}

	// "�Ͻ� ����, �ð� ���� ȿ��" ��� Ȱ���ϱ� ���ƿ�!
	void ZeroTimeScale()
	{
		m_timeScale = 0.0f;
	}

	Real32 getDeltaTime() const
	{
		return m_deltaTime;
	}

	Real32 getTimeScale() const
	{
		return m_timeScale;
	}

	void setTimeScale(Real32 timeScale)
	{
		m_timeScale = timeScale;
	}

	EFrameRateType getFrameRateType() const
	{
		return m_frameRateType;
	}

	void setFrameRateType(EFrameRateType frameRateType)
	{
		m_frameRateType = frameRateType;
	}

private:
	std::list<Int32> m_listFPS; // ��� �����Ӱ��� ���ϱ� ���� ����մϴ�.

	Int32 m_frameCnt = 0; // ���� ������ ������ �ϳ��Դϴ�.
	Int32 m_FPS = 0; // �ʴ� ������ �����Դϴ�. (Frame Per Second)
	Int32 m_limitedFrame = 60;

	Real32 m_accumulationFrameTime = 0.0f;
	Real32 m_timeScale = 1.0f; // ���� ũ�� ��������, ������ �������ϴ�.
	Real32 m_deltaTime = 0.0f; // ���� �����Ӱ� ���� �������� �����Դϴ�. (����, ���� �� �� ����)

	LARGE_INTEGER m_CPUFrequency;
	LARGE_INTEGER m_prevTick;

	EFrameRateType m_frameRateType = EFrameRateType::CONSTANT;
};

#endif