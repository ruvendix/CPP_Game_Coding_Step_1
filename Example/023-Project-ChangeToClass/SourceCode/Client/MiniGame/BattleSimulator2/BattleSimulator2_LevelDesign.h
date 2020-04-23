// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ����ϴ� ���� �������Դϴ�.
// �����ͷ� �������� ����� �����ϰų� �ҷ��� �� �ֽ��ϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_LEVEL_DESIGN__H__
#define BATTLE_SIMULATOR2_LEVEL_DESIGN__H__

#include "Element\LevelDesign.h"

class BattleSimulator2_LevelDesign final : public LevelDesign
{
	DECLARE_RTTI(BattleSimulator2_LevelDesign, LevelDesign);

public:
#pragma region ������ �� �Ҹ���
	using LevelDesign::LevelDesign;
	virtual ~BattleSimulator2_LevelDesign() = default;
#pragma endregion

	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
};

#endif