// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 유닛입니다.
// =====================================================================================

#include "PCH.h"
#include "Unit.h"

#include "Math\Random.h"

Unit::Unit(const std::string_view& szName, EDynamicObjID objID, const std::string_view& szShape) :
	DynamicObj(szName)
{
	setID(CommonFunc::ToUnderlyingType(objID));
	setShape(szShape);
}

void Unit::Attack(std::shared_ptr<Unit> spTargetUnit)
{
	if (m_attackSuccessRate > math::RandomUtil::GenerateRandom(0.0f, 1.0f))
	{
		spTargetUnit->Damage(m_attackDamage);
	}
}

void Unit::Damage(Int32 damage)
{
	m_HP -= damage;
}

void Unit::Copy(std::shared_ptr<Unit> spUnit)
{
	setID(spUnit->getID());
	setShape(spUnit->getShape());
	setPos(spUnit->getPos());
}
