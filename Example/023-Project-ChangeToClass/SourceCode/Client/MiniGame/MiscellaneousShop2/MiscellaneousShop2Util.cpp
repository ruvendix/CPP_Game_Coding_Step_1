// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ����2�� ��ƿ �Լ� �����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "MiscellaneousShop2Util.h"

#include "Controller\ConsoleController.h"
#include "Item\ItemDBContext.h"
#include "Item\ItemDB.h"
#include "Item\ItemBase.h"
#include "PlayerContext.h"

void MiscellanouseShop2Util::DrawItemTable(Int32 x, Int32 y, EItemDBType itemDBType)
{
	ItemDB* pItemDB = ItemDBCtx::I()->QueryItemDB(itemDBType);	
	if (pItemDB == nullptr)
	{
		PRINTF(0, 0, "�� �� ���� ������ DB����!");
		return;
	}

	Int32 drawPosY = y - 1;
	PRINTF(x, ++drawPosY, "������������������������������������������������������������������������������������������������");
	PRINTF(x, ++drawPosY, "��    �̸�                            ��     ���ݦ�");
	PRINTF(x, ++drawPosY, "������������������������������������������������������������������������������������������������");

	const ItemDB::MapItemDB& mapItemDB = pItemDB->getMapItemDB();
	for (const auto& iter : mapItemDB)
	{
		ItemBase* pItem = iter.second;
		if (pItem == nullptr)
		{
			continue;
		}

		PRINTF(x, ++drawPosY, "��    %-32s�� %8d��", pItem->getNameTag().c_str(), pItem->getPrice());
	}

	PRINTF(x, ++drawPosY, "������������������������������������������������������������������������������������������������");
}