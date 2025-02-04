// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 플레이어의 인벤토리입니다.
// 지금은 상점 아이템만 저장할 수 있습니다.
// ItemDB와는 다르게 vector를 이용합니다. (인벤토리 개수는 정해져있으므로!)
// =====================================================================================

#ifndef PLAYER_INVEN_H__
#define PLAYER_INVEN_H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"

class ItemBase;
using ItemBasePtr = std::shared_ptr<ItemBase>;

struct InvenItemInfo
{
	ItemBasePtr spItem = nullptr;
	Int32 cnt = 0;
};

using InvenItemInfoPtr = std::shared_ptr<InvenItemInfo>;

class Inven final
{
public:
#pragma region 생성자 및 소멸자
	Inven();
	~Inven() = default;
#pragma endregion

	void AddInvenItemInfo(ItemBasePtr spItem);
	void DeleteInvenItemInfo(Int32 invenIdx);
	void Draw(Int32 x, Int32 y) const;
	void DrawForSell(Int32 x, Int32 y) const;
	void Arrange();
	bool IsFull() const;

	InvenItemInfoPtr FindInvenItemInfo(Int32 invenIdx) const;
	InvenItemInfoPtr FindInvenItemInfo(const std::string& strItemNameTag) const;

	Int32 getMaxInvenSize() const
	{
		return m_maxInvenSize;
	}

private:
	Int32 m_currentIdx = 0;
	Int32 m_maxInvenSize = 5; // 인벤에 담을 수 있는 개수는 5개
	std::vector<InvenItemInfoPtr> m_vecInvenItemInfo;
};

#endif