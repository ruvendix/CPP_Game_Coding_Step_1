// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 로거가 필요한 매크로 함수 모음입니다.
// =====================================================================================
#pragma once

// BaseLogCategory를 상속받는 새로운 로그 카테고리 클래스를 선언합니다.
#define DECLARE_LOG_CATEGORY(CategoryName)\
	class CategoryName##Type : public BaseLogCategory\
	{\
	public:\
		CategoryName##Type() : BaseLogCategory(#CategoryName) { }\
	};\
	\
	extern CategoryName##Type g_##CategoryName

// DECLARE_LOG_CATEGORY()에서 선언한 클래스를 객체로 만듭니다.
// 실제로 객체를 만들 때는 매크로에 전달한 이름과 동일하게 만듭니다.
#define DEFINE_LOG_CATEGORY(CategoryName) CategoryName##Type g_##CategoryName

#define ACTIVATE_LOG_CATEGORY(CategoryName) g_##CategoryName.Activate()
#define DEACTIVATE_LOG_CATEGORY(CategoryName) g_##CategoryName.Deactivate()

#pragma region 로그 카테고리가 없는 버전입니다.
#ifdef _DEBUG
#define RX_TRACE(szFormat, ...)\
    Logger::I().Trace(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ASSERT(expression)\
    if (!(expression))\
    {\
        Logger::I().Assert(nullptr, #expression, __FILE__, __LINE__);\
    }
#else
#define RX_TRACE(szFormat, ...) __noop
#define RX_ASSERT(expression) __noop
#endif

#define RX_INFO(szFormat, ...)\
    Logger::I().Info(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_WARNING(szFormat, ...)\
    Logger::I().Warning(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ERROR(errorCode, ...)\
    ErrorTracer::I().SetLastErrorCode(errorCode);\
    Logger::I().Error(nullptr,\
        MakeFormatString(ErrorTracer::I().LastErrorString(), __VA_ARGS__), __FILE__, __LINE__)

#define RX_FATAL(szFormat, ...)\
    Logger::I().Fatal(nullptr, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)
#pragma endregion

#pragma region 로그 카테고리가 있는 버전입니다.
#ifdef _DEBUG
#define RX_TRACE2(logCategory, szFormat, ...)\
    Logger::I().Trace(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ASSERT2(logCategory, expression)\
    if (!(expression))\
    {\
        Logger::I().Assert(&g_##logCategory, #expression, __FILE__, __LINE__);\
    }
#else
#define RX_TRACE2(logCategory, szFormat, ...) __noop
#define RX_ASSERT2(logCategory, expression) __noop
#endif

#define RX_INFO2(logCategory, szFormat, ...)\
    Logger::I().Info(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_WARNING2(logCategory, szFormat, ...)\
    Logger::I().Warning(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)

#define RX_ERROR2(logCategory, errorCode, ...)\
    ErrorTracer::I().SetLastErrorCode(errorCode);\
    Logger::I().Error(&g_##logCategory,\
        MakeFormatString(ErrorTracer::I().LastErrorString(), __VA_ARGS__), __FILE__, __LINE__)

#define RX_FATAL2(logCategory, szFormat, ...)\
    Logger::I().Fatal(&g_##logCategory, MakeFormatString(szFormat, __VA_ARGS__), __FILE__, __LINE__)
#pragma endregion