// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 컴포넌트 인터페이스입니다.
// 멤버함수가 구현되어있고 멤버변수도 갖고 있는 추상 클래스입니다.
// C++에서는 인터페이스와 추상 클래스의 구분이 없으므로 둘 다 접두사 I를 사용합니다.
// =====================================================================================
#pragma once

#include "Core/RClass/RClass.h"

// 상호 참조 관계!
class Actor;

class IComponent : public RClass
{
    GENERATE_HIERARCHY(IComponent, RClass);

public:
    IComponent() = default;
    IComponent(Actor* pOwner);
    virtual ~IComponent() = default;

    Actor* GetOwner() { return m_pOwner; }
    const Actor* GetOwner() const { return m_pOwner; }

private:
    Actor* m_pOwner = nullptr;
};