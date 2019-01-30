#include "LogicGate1x.hpp"

bool LogicGate1x::GetA(void) const { return m_A; }
void LogicGate1x::SetA(const bool value) { m_A = value; }

LogicGate1x::LogicGate1x(const bool a, const bool autoID) : Component(autoID)
{
    SetA(a);
}
