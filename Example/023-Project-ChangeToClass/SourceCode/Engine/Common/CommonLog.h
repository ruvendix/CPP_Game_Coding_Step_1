// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �α� �������θ� ���˴ϴ�.
// =====================================================================================

#ifndef COMMON_LOG__H__
#define COMMON_LOG__H__

#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

DECLARE_LOG_CATEGORY(Common);

class CommonLog final : public NameTag
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(CommonLog);
};

#endif