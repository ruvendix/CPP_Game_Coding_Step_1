// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 마지막에 발생된 에러에 해당되는 내용을 알려줍니다.
// 에러가 발생되자마자 에러 핸들러가 작동됩니다.
// =====================================================================================
#pragma once

#include "IErrorHandler.h"

class ErrorHandler final : public IErrorHandler
{
	ONLY_SUBSYSTEM(ErrorHandler);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual const Char* FindErrorContent(EErrorCode errorCode) const override;

	virtual EErrorCode ObtainLastError() const override
	{
		return m_lastError;
	}

	virtual void ModifyLastError(EErrorCode errorCode) override
	{
		m_lastError = errorCode;
	}

private:
	EErrorCode m_lastError = EErrorCode::UNKNOWN;
	std::unordered_map<EErrorCode, std::string> m_mapError;
};