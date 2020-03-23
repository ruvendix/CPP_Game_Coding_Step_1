// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� ���� �������� ������ �� �ֽ��ϴ�.
// =====================================================================================

#ifndef BUY_PHASE_H__
#define BUY_PHASE_H__

#include "PhaseBase.h"
#include "..\Item\ItemDBEnum.h"

class ItemBase;

class BuyPhase : public PhaseBase
{
	FRIEND_WITH_HELPER(BuyPhaseHelper);
	FRAME_UPDATE_LIMITED(3);

public:
#pragma region ������ �� �Ҹ���
	using PhaseBase::PhaseBase;
	virtual ~BuyPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	EItemDBType m_itemDBType = EItemDBType::POTION;
	std::vector<ItemBase*> m_vecDisplayItem;
	bool m_bSelectedProductFamily = false;
	COORD m_selectedProductFamilyPos{ 0, 0 };
};

#endif