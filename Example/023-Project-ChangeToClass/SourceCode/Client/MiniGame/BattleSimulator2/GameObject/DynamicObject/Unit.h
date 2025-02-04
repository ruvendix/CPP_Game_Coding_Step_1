// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 유닛입니다.
// =====================================================================================

#ifndef UNIT_H__
#define UNIT_H__

#include "Common\CommonType.h"
#include "Element\GameObject\DynamicObject.h"
#include "..\ObjectID.h"
#include "..\ObjectState.h"

class Unit;
using UnitPtr = std::shared_ptr<Unit>;

class Unit : public DynamicObj
{
	DECLARE_RTTI(Unit, DynamicObj);

public:
#pragma region 생성자 및 소멸자
	using DynamicObj::DynamicObj;

	Unit() = default;
	virtual ~Unit() = default;
	
	Unit(const Unit& src);
	Unit(const std::string_view& szName, EObjID objID, const std::string_view& szShape);
#pragma endregion

	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnFinalize() override;

	void Attack(UnitPtr spTargetUnit);
	void Damage(Int32 damage);
	void FilterUnitInRange(const std::vector<UnitPtr>& vecUnit, const SizeInfo& worldSize);
	void ClearUnitInRange();
	void AdjustMoveAxisDir(UnitPtr spUnit);
	void ChangeLockOnTargetUnit(UnitPtr spTarget);

	EErrorType Copy(const Unit& src);

	UnitPtr Clone();
	UnitPtr SearchShortestPathEnemyInRange(_Out_ SizeInfo& distance) const;

	bool IsSameState(EUnitState state) const
	{
		return (m_state == state);
	}

#pragma region 접근자 Getter
	Int32 getHP() const
	{
		return m_HP;
	}

	Int32 getMaxHP() const
	{
		return m_maxHP;
	}

	Int32 getAttackDamage() const
	{
		return m_attackDamage;
	}

	Real32 getAttackSuccessRate() const
	{
		return m_attackSuccessRate;
	}

	EUnitState getState() const
	{
		return m_state;
	}

	Int32 getRange() const
	{
		return m_range;
	}

	UnitPtr getLockOnTargetUnit() const
	{
		return m_spLockOnTargetUnit;
	}

	const std::list<UnitPtr>& getListUnitInRange() const
	{
		return m_listUnitInRange;
	}
#pragma endregion

#pragma region 접근자 Setter
	void setHP(Int32 HP)
	{
		m_HP = HP;
	}

	void setMaxHP(Int32 MaxHP)
	{
		m_maxHP = MaxHP;
	}

	void setAttackDamage(Int32 attackDamage)
	{
		m_attackDamage = attackDamage;
	}

	void setAttackSuccessRate(Real32 attackSuccessRate)
	{
		m_attackSuccessRate = attackSuccessRate;
	}

	void setState(EUnitState state)
	{
		//DEBUG_LOG("이전 상태(%d) -> 현재 상태(%d)",
		//	common_func::ToUnderlyingType(m_state), common_func::ToUnderlyingType(state));
		m_state = state;
	}

	void setRange(Int32 range)
	{
		m_range = range;
	}
#pragma endregion

private:
	Int32 m_HP = 0;
	Int32 m_maxHP = 0;
	Int32 m_range = 0;
	Int32 m_attackDamage = 0;
	Real32 m_attackSuccessRate = 0.0f;
	EUnitState m_state = EUnitState::IDLE;

	UnitPtr m_spLockOnTargetUnit = nullptr; // 공격할 타겟 유닛
	std::list<UnitPtr> m_listUnitInRange; // 시야 범위 안에 들어온 유닛들 (자기 자신 제외)
};

#endif