// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ Ÿ�� �Ŵ����� ���Ǵ� �ܺ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"
#include "Subsystem/SubsystemData.h"

class FrameManagerData final : public SubsystemData
{
public:
	FrameManagerData() = default;
	~FrameManagerData() = default;

	Int32 GetFrameRate() const { return m_frameRate; }
	void SetFrameRate(Int32 frameCount) { m_frameRate = frameCount; }

	Float GetDeltaTime() const { return m_deltaTime; }
	void SetDeltaTime(Float deltaTime) { m_deltaTime = deltaTime; }

	// ���� ����ϴ� ���� �����ϴ�.
	DECLSPEC_DEPRECATED Float GetTimeScale() const { return m_timeScale; }
	DECLSPEC_DEPRECATED void SetTimeScale(Float timeScale) { m_timeScale = timeScale; }

private:
	Int32 m_frameRate = 0; // Frame Count�� �����ϴ�.
	Float m_deltaTime = 0.0f;
	Float m_timeScale = 1.0f;
};