// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 아이템 묶음입니다. 이런 걸 데이터베이스, DB라고 하죠.
// 하나에 모아도 되지만 일반적으로 DB는 여러 개로 분리되어있어요.
// =====================================================================================

#include "PCH.h"
#include "ItemDB.h"

#include "ItemBase.h"

ItemBasePtr ItemDB::FindItem(const std::string& strNameTag) const
{
	return m_mapItemDB.Find(strNameTag);
}

void ItemDB::CopyToVector(_Out_ std::vector<ItemBasePtr>& vecItem) const
{
	const MapItemDB::MapType& mapItem = m_mapItemDB.getMap();
	std::transform(mapItem.cbegin(), mapItem.cend(), std::back_inserter(vecItem), common_func::GetSecond(mapItem));
}
