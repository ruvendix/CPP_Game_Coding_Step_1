// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창을 다룰 때 사용됩니다.
// =====================================================================================
#include "EnginePCH.h"
#include "ConsoleHandler.h"

class ConsoleHandlerInside final
{
public:
	ConsoleHandlerInside() = default;
	~ConsoleHandlerInside() = default;

	void StartUp();
	void MovePosition(Int32 x, Int32 y);
	void AdjustSize(Uint32 width, Uint32 height);
	void ChangeTitle(const Char* szTitle);
	void ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType);
	void ShowCursor(bool bShow);
	void ClearScreen();
	void FlushInputBuffer();
	void ResetRenderingColor();

	COORD QueryCurrentPosition();
	Bool CheckValidCurrentOutputBuffer();

private:
	Uint32 m_defaultOutputAttr = 0; // 기본 출력 속성입니다.
	HWND m_hConsole = nullptr; // 콘솔창의 핸들입니다.
	HANDLE m_hStdInput = nullptr; // 표준 입력 버퍼의 핸들입니다.
	HANDLE m_hStdOutput = nullptr; // 표준 출력 버퍼의 핸들입니다.
	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo; // 출력 버퍼 정보입니다.
};

void ConsoleHandlerInside::StartUp()
{
	m_hConsole = ::GetConsoleWindow();
	if (m_hConsole == nullptr)
	{
		return;
	}

	m_hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
	if (m_hStdInput == nullptr)
	{
		return;
	}

	m_hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_hStdOutput == nullptr)
	{
		return;
	}

	::GetConsoleScreenBufferInfo(m_hStdOutput, &m_outputScreenBufferInfo);
	m_defaultOutputAttr = m_outputScreenBufferInfo.wAttributes;

	ChangeTitle("Default");
	AdjustSize(60, 30);
}

void ConsoleHandlerInside::MovePosition(Int32 x, Int32 y)
{
	COORD pos;
	pos.X = static_cast<Int16>(x);
	pos.Y = static_cast<Int16>(y);

	::SetConsoleCursorPosition(m_hStdOutput, pos);
}

void ConsoleHandlerInside::AdjustSize(Uint32 width, Uint32 height)
{
	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);

	sprintf_s(buffer, DEFAULT_CHAR_BUFFER_SIZE, "mode con cols=%d lines=%d", width, height);
	std::system(buffer);

	m_outputScreenBufferInfo.dwSize.X = static_cast<Uint16>(width);
	m_outputScreenBufferInfo.dwSize.Y = static_cast<Uint16>(height);
}

void ConsoleHandlerInside::ChangeTitle(const Char* szTitle)
{
	::SetWindowText(m_hConsole, szTitle);
}

void ConsoleHandlerInside::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	if ((renderingColor < EConsoleRenderingColor::BLACK) ||
		(renderingColor > EConsoleRenderingColor::BRIGHT_WHITE))
	{
		RX_ERROR2(LogConsoleHandler, EErrorCode::INVALID_SCREEN_COLOR);
	}

	// CONSOLE_SCREEN_BUFFER_INFO의 wAttributes에 색상 정보가 있어요!
	// wAttributes는 2바이트로서, 하위 바이트에 색상 정보가 있습니다.
	// 거기에서도 상위 4비트는 배경색, 하위 4비트는 글자색을 의미해요.
	// 이 정보와 비트 연산을 이용하면 배경색과 글자색을 따로 알아낼 수 있습니다!	
	Uint16 attr = m_outputScreenBufferInfo.wAttributes;
	if (renderingType == EConsoleRenderingType::TEXT)
	{
		attr &= 0xFFF0; // 하위 4비트값만 가져옵니다.
		attr |= static_cast<Uint16>(renderingColor);
	}
	else if (renderingType == EConsoleRenderingType::BACKGROUND)
	{
		attr &= 0xFF0F; // 상위 4비트값만 가져옵니다.
		attr |= (static_cast<Uint16>(renderingColor) << 4); // 상위 4비트만큼 이동해야 해요!
	}
	else
	{
		RX_ERROR2(LogConsoleHandler, EErrorCode::UNKNOWN);
	}

	m_outputScreenBufferInfo.wAttributes = attr;
	if (::SetConsoleTextAttribute(m_hStdOutput, m_outputScreenBufferInfo.wAttributes) == FALSE)
	{
		RX_ERROR2(LogConsoleHandler, EErrorCode::UNKNOWN);
	}
}

void ConsoleHandlerInside::ShowCursor(bool bShow)
{
	CONSOLE_CURSOR_INFO consoleCursorInfo; // 커서 정보는 CONSOLE_CURSOR_INFO에 있습니다.
	::GetConsoleCursorInfo(m_hStdOutput, &consoleCursorInfo);

	consoleCursorInfo.bVisible = bShow;
	::SetConsoleCursorInfo(m_hStdOutput, &consoleCursorInfo);
}

void ConsoleHandlerInside::ClearScreen()
{
	// 가로 X 세로 = 사각형 넓이
	Uint32 size = m_outputScreenBufferInfo.dwSize.X * m_outputScreenBufferInfo.dwSize.Y;

	// 콘솔창의 버퍼를 공백으로 채웁니다.
	DWORD dwWrittenCnt = 0;
	COORD beginPos = { 0, 0 };
	if (::FillConsoleOutputCharacter(m_hStdOutput, ' ', size, beginPos, &dwWrittenCnt) == FALSE)
	{
		RX_ERROR2(LogConsoleHandler, EErrorCode::CLEAR_SCREEN_FAIL);
	}

	// 콘솔창 출력 버퍼 속성이 적용된 부분을 지웁니다.
	if (::FillConsoleOutputAttribute(m_hStdOutput,
		static_cast<WORD>(m_defaultOutputAttr), size, beginPos, &dwWrittenCnt) == FALSE)
	{
		RX_ERROR2(LogConsoleHandler, EErrorCode::CLEAR_SCREEN_FAIL);
	}

	MovePosition(beginPos.X, beginPos.Y); // 커서 위치를 처음으로 이동시킵니다.	
}

void ConsoleHandlerInside::FlushInputBuffer()
{
	::FlushConsoleInputBuffer(m_hStdInput);
}

void ConsoleHandlerInside::ResetRenderingColor()
{
	m_outputScreenBufferInfo.wAttributes = static_cast<WORD>(m_defaultOutputAttr);
	::SetConsoleTextAttribute(m_hStdOutput, m_outputScreenBufferInfo.wAttributes);
}

COORD ConsoleHandlerInside::QueryCurrentPosition()
{
	::GetConsoleScreenBufferInfo(m_hStdOutput, &m_outputScreenBufferInfo);
	return m_outputScreenBufferInfo.dwCursorPosition;
}

Bool ConsoleHandlerInside::CheckValidCurrentOutputBuffer()
{
	return (m_hStdOutput != nullptr);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleHandler::ConsoleHandler()
{
	m_spInside = std::make_unique<ConsoleHandlerInside>();
}

/*
	콘솔창을 초기화합니다.
	콘솔창 이름과 사이즈 설정이 가능해요.
	핸들도 여기에서 저장합니다.
*/
void ConsoleHandler::StartUp()
{
	m_spInside->StartUp();
}

/*
	콘솔창을 정리합니다.
	아직은 추가할 내용이 없어요.
*/
void ConsoleHandler::CleanUp()
{
	
}

/*
	콘솔창 커서의 좌표를 옮깁니다.
*/
void ConsoleHandler::MovePosition(Int32 x, Int32 y)
{
	m_spInside->MovePosition(x, y);
}

/*
	콘솔창 사이즈를 조정합니다.
*/
void ConsoleHandler::AdjustSize(Uint32 width, Uint32 height)
{
	m_spInside->AdjustSize(width, height);
}

/*
	콘솔창 타이틀을 변경합니다.
*/
void ConsoleHandler::ChangeTitle(const Char* szTitle)
{
	m_spInside->ChangeTitle(szTitle);
}

/*
	콘솔창 렌더링 색깔을 변경합니다.
	글자색과 배경색 중에서 선택할 수 있어요.
*/
void ConsoleHandler::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	m_spInside->ChangeRenderingColor(renderingColor, renderingType);
}

/*
	콘솔창 커서 출력 여부를 설정합니다.
	마우스 커서가 아니라 키보드 커서를 의미해요.
*/
void ConsoleHandler::ShowCursor(bool bShow)
{
	m_spInside->ShowCursor(bShow);
}

/*
	콘솔창에 글자들을 출력합니다.
*/
void ConsoleHandler::RenderString(Int32 x, Int32 y, const Char* szText)
{
	MovePosition(x, y);
	printf("%s", szText);
}

/*
	콘솔창에 출력된 모든 것들을 지웁니다.
	출력 버퍼의 색상 정보는 그대로 유지합니다.
*/
void ConsoleHandler::ClearScreen()
{
	m_spInside->ClearScreen();
}

/*
	콘솔창 입력 버퍼를 비웁니다.
	콘솔창에서는 일부 문자가 입력 버퍼에 남을 수 있으니까 주의하세요!
*/
void ConsoleHandler::FlushInputBuffer()
{
	m_spInside->FlushInputBuffer();
}

/*
	콘솔창 출력 색상을 원래대로 돌립니다.
*/
void ConsoleHandler::ResetRenderingColor()
{
	m_spInside->ResetRenderingColor();
}

void ConsoleHandler::Pause() const
{
	std::system("pause");
}

/*
	정수를 입력받습니다.
*/
Int32 ConsoleHandler::InputInteger()
{
	Int32 value = 0;
	scanf_s("%d", &value);
	FlushInputBuffer();
	return value;
}

/*
	실수를 입력받습니다.
*/
Float ConsoleHandler::InputFloat()
{
	Float value = 0.0f;
	scanf_s("%f", &value);
	FlushInputBuffer();
	return value;
}

/*
	문자열을 입력받습니다.
*/
void ConsoleHandler::InputString(OUT std::string& str)
{
	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);
	scanf_s("%[^\n]s", buffer, DEFAULT_CHAR_BUFFER_SIZE);
	FlushInputBuffer();
	str.assign(buffer);
}

/*
	콘솔창 커서의 현재 좌표를 알려줍니다.
*/
COORD ConsoleHandler::QueryCurrentPosition()
{
	return m_spInside->QueryCurrentPosition();
}

/*
	현재 출력 버퍼가 유효한지 확인합니다.
*/
Bool ConsoleHandler::CheckValidCurrentOutputBuffer()
{
	return (m_spInside->CheckValidCurrentOutputBuffer());
}