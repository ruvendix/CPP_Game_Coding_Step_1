// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 상점 아이템으로 사용하는 회복약입니다.
// =====================================================================================

#ifndef SHOP_ITEM_POTION_H__
#define SHOP_ITEM_POTION_H__

#include "ShopItem.h"

class ShopItem_Potion final : public ShopItem
{
	DECLARE_RTTI(ShopItem_Potion, ShopItem);

public:
#pragma region 생성자 및 소멸자
	using ShopItem::ShopItem;
	virtual ~ShopItem_Potion() = default;
#pragma endregion
};

#endif