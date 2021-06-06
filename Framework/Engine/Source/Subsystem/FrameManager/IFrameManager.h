// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ Ÿ�� �Ŵ����� �������̽��Դϴ�.
// �ܺ� �����Ϳ� �Լ��� ���� ������ �߻� Ŭ�����̱⵵ �մϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "FrameManagerData.h"

class IFrameManager : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::FRAME_TIME_MANAGER);
	GENERATE_SUBSYSTEM_DATA(FrameManagerData);

public:
	static Float ConvertFPS_ToFixedDeltaTime(Int32 FPS)
	{
		return (1.0f / static_cast<Float>(FPS));
	}

	IFrameManager() = default;
	virtual ~IFrameManager() = default;

	virtual void SetUp() override EMPTY_FUNC;
	virtual void CleanUp() override EMPTY_FUNC;

	virtual void UpdateFrameTime() PURE_FUNC;
};