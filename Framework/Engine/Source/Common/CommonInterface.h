// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공통적으로 사용되는 인터페이스 모음입니다.
// =====================================================================================
#pragma once

#include "CommonMacro.h"
#include "CommonEnum.h"

class ICommon
{
public:
	ICommon() = default;
	virtual ~ICommon() = default;

	virtual void StartUp() PURE_FUNC;
	virtual void CleanUp() PURE_FUNC;
};

class IGameObject : public ICommon
{
public:
	IGameObject() = default;
	virtual ~IGameObject() = default;

	virtual void Update() PURE_FUNC;
	virtual void Render() PURE_FUNC;
};