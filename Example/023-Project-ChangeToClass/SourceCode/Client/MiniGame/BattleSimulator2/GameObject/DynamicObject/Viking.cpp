// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ŷ�Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "Viking.h"

VikingPtr Viking::Clone()
{
	return std::make_shared<Viking>(*this);
}